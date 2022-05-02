using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Video;
using UnityEngine.SceneManagement;

public class ListeCercle : MonoBehaviour
{
    // Création de la liste de tous les cercles
    [SerializeField] private List<Transform> allChildren;
    public Transform premierCercle;
    public string couleurPremierCercle;

    // Récupération de la valeur des points
    public JoueurUI MonJoueur;

    // Image du Socle
    public GameObject MonSocle;
    public Sprite ImageUne;
    public Sprite ImageDeux;

    // Ajout des percussions
    private AudioSource piste01;
    public float volumePercussion = 0.5f;
    public AudioClip percussionRouge;
    public AudioClip percussionBleu;
    public AudioClip percussionHaute;
    public AudioClip percussionBasse;

    // Setup video
    public GameObject videoPlayer;

    private void Awake()
    {
        // Fixer le script à 60 FPS
        Application.targetFrameRate = 60;
    }

    void Start()
    {
        foreach (Transform child in transform)
        {
            allChildren.Add(child);
        }

        piste01 = gameObject.AddComponent<AudioSource>();
        piste01.volume = volumePercussion;

        videoPlayer.GetComponent<VideoPlayer>().loopPointReached += endReached;
    }

    private void endReached(VideoPlayer source)
    {
        SceneManager.LoadScene("EndScreen");
    }

    void PremierEnfant()
    {
        if (allChildren.Count != 0)
        {
            premierCercle = allChildren[0];
            couleurPremierCercle = premierCercle.GetComponent<MouvementCercle>().couleur;
        }
    }

    private void Update()
    {
        // Si la video est prête alors
        if (videoPlayer.GetComponent<VideoPlayer>().waitForFirstFrame)
        {
            // Vérifier que la liste n'est pas vide
            if (allChildren.Count != 0)
            {
                // Si le cercle sort de l'écran alors on le détruit
                if (premierCercle.position.x <= -13)
                {
                    // Reset combo
                    MonJoueur.combo = 0;

                    Destroy(allChildren[0].gameObject);
                    allChildren.RemoveAt(0);
                    PremierEnfant();
                }

                if (Input.GetKeyDown(KeyCode.RightArrow))
                {
                    MonSocle.GetComponent<SpriteRenderer>().sprite = ImageDeux;

                    piste01.clip = percussionBleu;
                    piste01.Play();

                    if (couleurPremierCercle == "Bleu")
                    {
                        AjoutPoint();
                    }
                } else if (Input.GetKeyDown(KeyCode.LeftArrow))
                {
                    MonSocle.GetComponent<SpriteRenderer>().sprite = ImageDeux;

                    piste01.clip = percussionRouge;
                    piste01.Play();

                    if (couleurPremierCercle == "Rouge")
                    {
                        AjoutPoint();
                    }
                } else if (Input.GetKeyDown(KeyCode.UpArrow))
                {
                    piste01.clip = percussionHaute;
                    piste01.Play();
                } else if (Input.GetKeyDown(KeyCode.DownArrow))
                {
                    piste01.clip = percussionBasse;
                    piste01.Play();
                }
            }

            if (Input.GetKeyUp(KeyCode.RightArrow))
            {
                MonSocle.GetComponent<SpriteRenderer>().sprite = ImageUne;
            }

            if (Input.GetKeyUp(KeyCode.LeftArrow))
            {
                MonSocle.GetComponent<SpriteRenderer>().sprite = ImageUne;
            }
        }
    }

    private void AjoutPoint()
    {
        if (premierCercle.position.x <= -7.00 && premierCercle.position.x > -9)
        {
            MonJoueur.combo = 0;
            MonJoueur.point += 10;
            Destroy(allChildren[0].gameObject);
            allChildren.RemoveAt(0);
            PremierEnfant();

        }

        else if (premierCercle.position.x <= -9 && premierCercle.position.x > -9.50)
        {
            MonJoueur.point += 30;
            MonJoueur.point += MonJoueur.combo;
            MonJoueur.combo += 1;
            Destroy(allChildren[0].gameObject);
            allChildren.RemoveAt(0);
            PremierEnfant();
        }

        else if (premierCercle.position.x <= -9.50 && premierCercle.position.x > -10.30)
        {
            MonJoueur.point += 50;
            MonJoueur.point += MonJoueur.combo;
            MonJoueur.combo += 1;
            Destroy(allChildren[0].gameObject);
            allChildren.RemoveAt(0);
            PremierEnfant();
        }

        else if (premierCercle.position.x <= -10.30 && premierCercle.position.x > -11.80)
        {
            MonJoueur.point += 30;
            MonJoueur.point += MonJoueur.combo;
            MonJoueur.combo += 1;
            Destroy(allChildren[0].gameObject);
            allChildren.RemoveAt(0);
            PremierEnfant();
        }

        else if(premierCercle.position.x <= -11.80 && premierCercle.position.x > -13)
        {
            MonJoueur.combo = 0;
            MonJoueur.point += 10;
            Destroy(allChildren[0].gameObject);
            allChildren.RemoveAt(0);
            PremierEnfant();

        }
    }
}
