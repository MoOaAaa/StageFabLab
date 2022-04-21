#define CAMERA_MODEL_AI_THINKER // Has PSRAM

#include "eloquent.h"
#include "eloquent/vision/motion/naive.h"
#include "eloquent/vision/camera/esp32/aithinker/gray/qvga.h"
#include "eloquent/vision/camera/BaseCamera.h"
#include "esp_http_server.h"
#include <Arduino.h>
#include <WiFi.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>

#define FRAME_SIZE FRAMESIZE_QVGA
#define DEST_WIDTH 64
#define DEST_HEIGHT 48
#define INTENSITY_VARIATION_THRESHOLD 15
#define MOTION_THRESHOLD 0.1

using namespace Eloquent::Vision;
using namespace Eloquent::Vision::Cam;

Eloquent::Vision::Motion::Naive<DEST_WIDTH, DEST_HEIGHT> detector;

const char* ssid = "ssid";
const char* password = "password";

#define PART_BOUNDARY "123456789000000000000987654321"

static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

httpd_handle_t stream_httpd = NULL;


void setup(){
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera.setHighFreq();

  if (!camera.begin()) {
    while (true)  {
        Serial.println(camera.getErrorMessage());
        delay(1000);
    }
  }
  else {
    Serial.println("Camera init OK");
  }


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  //wait for n frames to be processed before starting to detect motion.
  // and then if motion is detected, don't scan for the next n frames
  detector.throttle(10);

  //trigger detector when MOTION_THRESHOLD% pixels or more change intensity
  //by at least INTENSITY_VARIATION_THRESHOLD out of 255
  detector.setPixelChangesThreshold(MOTION_THRESHOLD);
  detector.setIntensityChangeThreshold(INTENSITY_VARIATION_THRESHOLD);

}

void loop(){
    if (!camera.capture()) {
        Serial.println(camera.getErrorMessage());
        delay(1000);
        return;
    }

    //resize the image for the detector to process faster
    //print image data on Serial monitor
    camera.image.resize<DEST_WIDTH, DEST_HEIGHT>();
    camera.image.printAsJsonTo(Serial);
    detector.update(camera.image);


    if (detector.isMotionDetected()) {
        Serial.print("Motion detected");
        // start the streaming server when motion is detected
        // shutdown after 20 seconds if no one connects
        delay(2000);
        Serial.print("Camera Server ready! Use 'http://");
        Serial.print(WiFi.localIP());
        startCameraServer();
        delay(20000);
        stopCameraServer();
        delay(2000);
    }

    // probably we don't need 30 fps, save some power
    delay(300);
}

//webstream part
static esp_err_t stream_handler(httpd_req_t *req){
  camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    size_t _jpg_buf_len;
    uint8_t * _jpg_buf;
    char * part_buf[64];
    static int64_t last_frame = 0;
    if(!last_frame) {
        last_frame = esp_timer_get_time();
    }

    res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
    if(res != ESP_OK){
        return res;
    }

    while(true){
        fb = esp_camera_fb_get();
        if (!fb) {
            ESP_LOGE(TAG, "Camera capture failed");
            res = ESP_FAIL;
            break;
        }
        if(fb->format != PIXFORMAT_JPEG){
            bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
            if(!jpeg_converted){
                ESP_LOGE(TAG, "JPEG compression failed");
                esp_camera_fb_return(fb);
                res = ESP_FAIL;
            }
        } else {
            _jpg_buf_len = fb->len;
            _jpg_buf = fb->buf;
        }

        if(res == ESP_OK){
            res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
        }
        if(res == ESP_OK){
            size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);

            res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
        }
        if(res == ESP_OK){
            res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
        }
        if(fb->format != PIXFORMAT_JPEG){
            free(_jpg_buf);
        }
        esp_camera_fb_return(fb);
        if(res != ESP_OK){
            break;
        }
        int64_t fr_end = esp_timer_get_time();
        int64_t frame_time = fr_end - last_frame;
        last_frame = fr_end;
        frame_time /= 1000;
        ESP_LOGI(TAG, "MJPG: %uKB %ums (%.1ffps)",
            (uint32_t)(_jpg_buf_len/1024),
            (uint32_t)frame_time, 1000.0 / (uint32_t)frame_time);
    }

    last_frame = 0;
    return res;
}

void startCameraServer(){
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 80;
    
    httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = stream_handler,
        .user_ctx = NULL
    };

    if(httpd_start(&stream_httpd, &config) == ESP_OK){
        httpd_register_uri_handler(stream_httpd, &index_uri);
    }
}

void stopCameraServer() {
    httpd_unregister_uri(stream_httpd, "/");
    httpd_stop(stream_httpd);
}


