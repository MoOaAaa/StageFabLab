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
        musicVolumeSlider.value = PlayerPrefs.GetFloat("MusicVolume", 0.75f);
        effectsVolumeSlider.value = PlayerPrefs.GetFloat("EffectsVolume", 0.75f);
        EventSystem.current.SetSelectedGameObject(interactables[0]);
        Debug.Log("Setting: " + i);
        Debug.Log(interactables.Count);
    }

    public void Update()
    {
        GameObject currentlySelected = EventSystem.current.currentSelectedGameObject;
        

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

        if (Input.GetKeyDown(KeyCode.LeftArrow) &&
            currentlySelected.GetComponent<Slider>() != null)
        {
            Debug.Log("Setting: " + i);

            decrementSlider(currentlySelected.GetComponent<Slider>());
        }
    }

    void incrementSlider(Slider slider)
    {
        slider.SetValueWithoutNotify(slider.value + 0.005f);

    }

    void decrementSlider(Slider slider)
    {
        slider.SetValueWithoutNotify(slider.value - 0.005f);
    }

    public void updateMusicVolume()
    {
        PlayerPrefs.SetFloat("MusicVolume", musicVolumeSlider.value);
    }

    public void updateEffetcsVolume()
    {
        PlayerPrefs.SetFloat("EffectsVolume", effectsVolumeSlider.value);
    }
    public void back()
    {
        mainMenu.SetActive(true);
        gameObject.SetActive(false);
    }
}
