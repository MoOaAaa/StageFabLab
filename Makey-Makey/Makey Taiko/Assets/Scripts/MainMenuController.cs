using System.Collections;
using System.Collections.Generic;
using UnityEngine.EventSystems;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MainMenuController : MonoBehaviour
{
    public GameObject mainMenu;
    public GameObject settingsMenu;
    public List<GameObject> buttons;
    private int i;

    public void Start()
    {
        i = 0;
        EventSystem.current.SetSelectedGameObject(buttons[0]); //Selectionne le premier bouton du menu
        Debug.Log("Menu: " + i);
        Debug.Log(buttons.Count);
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow)) //Change de bouton vers le haut
        {
            // Si on est sur le bouton le plus en haut, reprend depuis le plus en bas
            if(i == 0)
            {
                i = buttons.Count-1;
            }
            else
            {
                i--;
            }
            Debug.Log("Menu: " + i);
            EventSystem.current.SetSelectedGameObject(buttons[i]);
        }

        if (Input.GetKeyDown(KeyCode.DownArrow)) //Change de bouton vers le bas
        {
            // Si on est sur le bouton le plus en bas, reprend depuis le plus en haut
            if (i == buttons.Count-1)
            {
                i = 0;
            }
            else
            {
                i++;
            }
            Debug.Log("Menu: " + i);
            EventSystem.current.SetSelectedGameObject(buttons[i]);
        }

        if (Input.GetKeyDown(KeyCode.RightArrow)) // Fleche de droite pour activer le bouton
        {
            Debug.Log(i);
            // Switch en fonction du bouton sur lequel on est
            switch (i)
            {
                case 0:                  
                    startGame();
                    break;
                case 1: settings();
                    break;
                case 2: exitGame();
                    break;
                default:;break;
            }
        }
    }

    /**
     * 
     */
    public void startGame()
    {
        SceneManager.LoadScene("SampleScene");
    }

    public void settings()
    {
        mainMenu.SetActive(false);
        settingsMenu.SetActive(true);
    }


    public void exitGame()
    {
        Application.Quit();
    }
}
