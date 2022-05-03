using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class SettingsMenu : MonoBehaviour
{
    public GameObject mainMenu;
    public Slider musicVolumeSlider;
    public Slider effectsVolumeSlider;
    public List<GameObject> interactables;
    public Color sliderSelectedColor;
    public Color sliderNotSelecteColor;
    private int i = 0;
    // Start is called before the first frame update
    void Start()
    {
        // Cherche la valeur pref du joueur sur son pc si elle existe, sinon met à 75%
        // le volume de la musique et des percussions
        musicVolumeSlider.value = PlayerPrefs.GetFloat("MusicVolume", 0.75f);
        effectsVolumeSlider.value = PlayerPrefs.GetFloat("EffectsVolume", 0.75f);

        // Sélectionne le premier objet de la liste "interactables"
        EventSystem.current.SetSelectedGameObject(interactables[0]);
        Debug.Log("Setting: " + i);
        Debug.Log(interactables.Count);
    }

    public void Update()
    {
        GameObject currentlySelected = EventSystem.current.currentSelectedGameObject; // declaration de currentlySelected pour raccourcir le code
        
        // Si currentlySelected comporte un composant Slider
        // Alors
        //      Si currentlySelected est MusicVolumeSlider
        //      Alors affiche la outline sur celui ci et cache celle de effectsVolumeSlider
        //      Sinon l'inverse
        //Sinon desactive la outline des deux sliders
        if(currentlySelected.GetComponent<Slider>() != null)
        {
            if(currentlySelected.name == "MusicVolumeSlider")
            {
                musicVolumeSlider.transform.Find("Background").GetComponent<Outline>().enabled = true;
                effectsVolumeSlider.transform.Find("Background").GetComponent<Outline>().enabled = false;
            }
            else
            {
                effectsVolumeSlider.transform.Find("Background").GetComponent<Outline>().enabled = true;
                musicVolumeSlider.transform.Find("Background").GetComponent<Outline>().enabled = false;
            }
        }
        else
        {
            musicVolumeSlider.transform.Find("Background").GetComponent<Outline>().enabled = false;
            effectsVolumeSlider.transform.Find("Background").GetComponent<Outline>().enabled = false;
        }

        // Si la touche fleche du haut est appuyee
        // Alors
        //      Si i = 0
        //      Alors on retourne au début de la liste
        //      Sinon on remonte de 1 dans le table interactables
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            if (i == 0)
            {
                i = interactables.Count-1;
            }
            else
            {
                i--;
            }
            Debug.Log("Setting: "+i);

            EventSystem.current.SetSelectedGameObject(interactables[i]);
        }

        // Si la touche fleche du bas est appuyee
        // Alors
        //      Si i = le nombre  d'objets-1 de la liste
        //      Alors on retourne a la fin de la liste
        //      Sinon on descend de 1 dans le table interactables
        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            if (i == interactables.Count-1)
            {
                i = 0;
            }
            else
            {
                i++;
            }
            Debug.Log("Setting: " + i);

            EventSystem.current.SetSelectedGameObject(interactables[i]);
        }

        // Si la fleche de droite est appuyee et currentlySelected comporte un composant Slider
        // Alors on appelle incrementSlider() sur le slider de currentlySelected
        // Sinon Si la fleche de droite est appuyee et currentlySelected comporte un composant Button
        // Alors on appelle back()
        if (Input.GetKeyDown(KeyCode.RightArrow) &&
            currentlySelected.GetComponent<Slider>() != null )
        {
            incrementSlider(currentlySelected.GetComponent<Slider>());
        }else if (
            Input.GetKeyDown(KeyCode.RightArrow) &&
            currentlySelected.GetComponent<Button>() != null
            )
        {
            back();
        }


        // Si la fleche de gauche est appuyee et currentlySelected comporte un composant Slider
        // Alors on appelle decrementSlider() sur le slider de currentlySelected
        if (Input.GetKeyDown(KeyCode.LeftArrow) &&
            currentlySelected.GetComponent<Slider>() != null)
        {
            Debug.Log("Setting: " + i);

            decrementSlider(currentlySelected.GetComponent<Slider>());
        }
    }

    /**
     * Augmente la valeur de slider de 10%
     */
    void incrementSlider(Slider slider)
    {
        slider.SetValueWithoutNotify(slider.value + 0.005f);

    }

    /**
     * Diminue la valeur de slider de 10%
     */
    void decrementSlider(Slider slider)
    {
        slider.SetValueWithoutNotify(slider.value - 0.005f);
    }

    /**
     * Change la valeur de MusicVolume dans les PlayerPrefs sur le PC
     */
    public void updateMusicVolume()
    {
        PlayerPrefs.SetFloat("MusicVolume", musicVolumeSlider.value);
    }

    /**
     * Change la valeur de EffectsVolume dans les PlayerPrefs sur le PC
     */
    public void updateEffetcsVolume()
    {
        PlayerPrefs.SetFloat("EffectsVolume", effectsVolumeSlider.value);
    }

    /**
     * Cache le menu des settings et reaffiche le menu principal
     */
    public void back()
    {
        mainMenu.SetActive(true);
        gameObject.SetActive(false);
    }
}
