using UnityEngine;
using UnityEngine.Video;

public class MouvementCercle : MonoBehaviour
{
    public int speed = 7;
    public string couleur;

    public float songBpm;
    public float secPerBeat;
    public float songPosition;
    public float songPositionInBeat;
    public float dspSongTime;
    public float firstBeatOffset;
    public float previousDspTime;
    public AudioSource musicSource;
    // Setup video
    public GameObject videoPlayer;

    private void Awake()
    {
        Application.targetFrameRate = 60;
        videoPlayer = GameObject.FindGameObjectWithTag("Video");

        musicSource.GetComponent<AudioSource>();
        secPerBeat = 60f / songBpm;
        dspSongTime = (float)AudioSettings.dspTime;
        previousDspTime = (float)AudioSettings.dspTime;

        musicSource.Play();
    }

    void Update()
    {
        float avancementMusique = (float)AudioSettings.dspTime - previousDspTime;
        // Si la video est prête alors
        if (videoPlayer.GetComponent<VideoPlayer>().waitForFirstFrame)
        {
            transform.Translate(Vector3.left * avancementMusique * speed);
        }

        songPosition = (float)(AudioSettings.dspTime - dspSongTime - firstBeatOffset);

        songPositionInBeat = songPosition / secPerBeat;
        Debug.Log("song position in beats : " + songPositionInBeat);
        Debug.Log(dspSongTime);
        Debug.Log(AudioSettings.dspTime);

        previousDspTime = (float)AudioSettings.dspTime;
    }
}

