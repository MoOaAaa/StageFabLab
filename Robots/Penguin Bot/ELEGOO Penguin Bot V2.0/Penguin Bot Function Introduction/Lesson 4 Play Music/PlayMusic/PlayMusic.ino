#include "Arduino.h"
#include "Oscillator.h"
#include <Servo.h>

#include "NeoSWSerial.h"

/*
         ---------------
        |     O   O     |
        |---------------|
YR 2<== |               | <== YL 3
         ---------------
            ||     ||
            ||     ||
RR 0==^   -----   ------  v== RL 1
         |-----   ------|
*/
/* Hardware interface mapping*/
#define MY1690_PIN 8
#define HT6871_PIN 7
#define SOFTWARE_RXD A2 
#define SOFTWARE_TXD A3


bool delays(unsigned long ms)
{
    for (unsigned long i = 0; i < ms; i++)
    {
        delay(1);
    }
    return false;
}

NeoSWSerial mp3Serial(SOFTWARE_RXD, SOFTWARE_TXD);

/*
    MP3:Implementation of MP3 Driver
*/
class MY1690_16S
{
public:
    int volume;
    String playStatus[5] = {"0", "1", "2", "3", "4"}; // STOP PLAYING PAUSE FF FR
    void playSong(unsigned char num, unsigned char vol)
    {
        setVolume(vol);
        setPlayMode(4);
        CMD_SongSelet[4] = num;
        checkCode(CMD_SongSelet);
        mp3Serial.write(CMD_SongSelet, 7);
        delay(50);
    }
    String getPlayStatus()
    {
        mp3Serial.write(CMD_getPlayStatus, 5);
        delay(50);
        return getStatus();
    }
    String getStatus()
    {
        String statusMp3 = "";
        while (mp3Serial.available())
        {
            statusMp3 += (char)mp3Serial.read();
        }
        return statusMp3;
    }
    void stopPlay()
    {
        setPlayMode(4);
        mp3Serial.write(CMD_MusicStop, 5);
        delay(50);
    }
    void setVolume(unsigned char vol)
    {
        CMD_VolumeSet[3] = vol;
        checkCode(CMD_VolumeSet);
        mp3Serial.write(CMD_VolumeSet, 6);
        delay(50);
    }
    void volumePlus()
    {
        mp3Serial.write(CMD_VolumePlus, 5);
        delay(50);
    }
    void volumeDown()
    {
        mp3Serial.write(CMD_VolumeDown, 5);
        delay(50);
    }
    void setPlayMode(unsigned char mode)
    {
        CMD_PlayMode[3] = mode;
        checkCode(CMD_PlayMode);
        mp3Serial.write(CMD_PlayMode, 6);
        delay(50);
    }
    void checkCode(unsigned char *vs)
    {
        int val = vs[1];
        int i;
        for (i = 2; i < vs[1]; i++)
        {
            val = val ^ vs[i];
        }
        vs[i] = val;
    }
    void ampMode(int p, bool m)
    {
        pinMode(p, OUTPUT);
        if (m)
        {
            digitalWrite(p, HIGH);
        }
        else
        {
            digitalWrite(p, LOW);
        }
    }
    void init()
    {
        ampMode(HT6871_PIN, HIGH);
        stopPlay();
        volume = 15;
    }
private:
    byte CMD_MusicPlay[5] = {0x7E, 0x03, 0x11, 0x12, 0xEF};
    byte CMD_MusicStop[5] = {0x7E, 0x03, 0x1E, 0x1D, 0xEF};
    byte CMD_MusicNext[5] = {0x7E, 0x03, 0x13, 0x10, 0xEF};
    byte CMD_MusicPrev[5] = {0x7E, 0x03, 0x14, 0x17, 0xEF};
    byte CMD_VolumePlus[5] = {0x7E, 0x03, 0x15, 0x16, 0xEF};
    byte CMD_VolumeDown[5] = {0x7E, 0x03, 0x16, 0x15, 0xEF};
    byte CMD_VolumeSet[6] = {0x7E, 0x04, 0x31, 0x00, 0x00, 0xEF};
    byte CMD_PlayMode[6] = {0x7E, 0x04, 0x33, 0x00, 0x00, 0xEF};
    byte CMD_SongSelet[7] = {0x7E, 0x05, 0x41, 0x00, 0x00, 0x00, 0xEF};
    byte CMD_getPlayStatus[5] = {0x7E, 0x03, 0x20, 0x23, 0xEF};
} mp3;

void setup()
{
    mp3Serial.begin(9600);
    mp3.init();
    mp3.playSong(1, 20); // play song 0001, set volume 20
}
void loop(){}
