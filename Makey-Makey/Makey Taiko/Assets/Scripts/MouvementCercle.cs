using UnityEngine;
using UnityEngine.Video;

public class MouvementCercle : MonoBehaviour
{
    public int speed = 7;
    public string couleur;

    // Setup video
    public GameObject videoPlayer;

    private void Awake()
    {
        Application.targetFrameRate = 60;
        videoPlayer = GameObject.FindGameObjectWithTag("Video");
    }

    void Update()
    {
        // Si la video est prête alors
        if (videoPlayer.GetComponent<VideoPlayer>().waitForFirstFrame)
        {
            transform.Translate(Vector3.left * 0.016f * speed);
        }
    }
}

