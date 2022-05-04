using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text.RegularExpressions;
using TMPro;

public class HighscoreTable : MonoBehaviour
{
    [SerializeField]
    private Transform entryContainer;
    
    [SerializeField]
    private Transform entryTemplate;

    [SerializeField]
    private List<Transform> highscoreEntryTransformList;

    [SerializeField]
    private List<HighscoreEntry> highscoreEntryList;

    [SerializeField]
    private Transform nameInputField;

    [SerializeField]
    private string playerName;
    
    // Start is called before the first frame update
    void Start()
    {
        entryContainer = transform.Find("HighScoreEntryContainer");
        entryTemplate = entryContainer.Find("HighScoreEntryTemplate");
        nameInputField = transform.Find("NameInputField");

        //=======================================//
        //             Add an entry              //
        //AddHighscoreEntry(10, "AAA");
        //                                       //
        //=======================================//

        //=======================================//
        //             Del an entry              //
        //DelHighscoreEntry("AAA");
        //                                       //
        //=======================================//

        //!!DON'T WORK!!//
        //=======================================//
        //             Del all entry             //
        //DelAllHighscoreEntry();
        //                                       //
        //=======================================//

        Refresh();
    }

    void Update()
    {
        string playerName = "";
        if (Input.GetKeyDown(KeyCode.Return))
        {
            
            playerName = nameInputField.GetComponent<InputField>().text;
            if (Regex.IsMatch(playerName, @"^[a-zA-Z]+$") && playerName.Length == 3)
            {
                Debug.Log("Valid name");
                AddHighscoreEntry(PlayerPrefs.GetInt("Score"), playerName);
                Refresh();
                transform.Find("NameInput").gameObject.SetActive(false);
            }
            else
            {
                Debug.Log("Invalid name");
                playerName = "";
            }
        }
    }

    private void CreateHighscoreEntryTransform(HighscoreEntry highscoreEntry, Transform container, List<Transform> transformList, bool isTheLast)
    {
        Transform entryTransform = Instantiate(entryTemplate, container);
        entryTransform.gameObject.SetActive(true);
        
        int rank = transformList.Count + 1;
        string rankString;
        if (isTheLast == true)
        {
            rankString = "---";
        }
        else
        {
            switch (rank)
            {
                default:
                    rankString = rank + "TH";
                    break;
                case 1:
                    rankString = "1ST";
                    break;
                case 2:
                    rankString = "2ND";
                    break;
                case 3:
                    rankString = "3RD";
                    break;
            }
        }
        entryTransform.GetChild(0).GetComponent<Text>().text = rankString;
        int score = highscoreEntry.score;
        entryTransform.GetChild(1).GetComponent<Text>().text = score.ToString();
        string name = highscoreEntry.name;
        entryTransform.GetChild(2).GetComponent<Text>().text = name;

        transformList.Add(entryTransform);
    }

    private void AddHighscoreEntry(int score, string name)
    {
        // Create HighscoreEntry
        HighscoreEntry highscoreEntry = new HighscoreEntry { score = score, name = name };
        
        // Load saved Highscores
        string jsonString = PlayerPrefs.GetString("HighscoreTable");
        Highscores highscores = JsonUtility.FromJson<Highscores>(jsonString);

        // Add new entry to Highscores
        highscores.highscoreEntryList.Add(highscoreEntry);

        // Save updated Highscores
        string json = JsonUtility.ToJson(highscores);
        PlayerPrefs.SetString("HighscoreTable", json);
        PlayerPrefs.Save();
    }

    private void DelHighscoreEntry(string name)
    {
        if (name != "---")
        {    
            // Load saved Highscores
            string jsonString = PlayerPrefs.GetString("HighscoreTable");
            Highscores highscores = JsonUtility.FromJson<Highscores>(jsonString);
            // Find entry to delete
            for (int i = 0; i < highscores.highscoreEntryList.Count; i++)
            {
                if ( highscores.highscoreEntryList[i].name == name)
                {
                    highscores.highscoreEntryList.RemoveAt(i);
                    break;
                }
            }
            // Save updated Highscores
            string json = JsonUtility.ToJson(highscores);
            PlayerPrefs.SetString("HighscoreTable", json);
            PlayerPrefs.Save();
        }
    }

    private void DelAllHighscoreEntry()
    {
        // Load saved Highscores
        string jsonString = PlayerPrefs.GetString("HighscoreTable");
        Highscores highscores = JsonUtility.FromJson<Highscores>(jsonString);
        // Find entry to delete
        for (int i = 0; i < highscores.highscoreEntryList.Count; i++)
        {
            if (highscores.highscoreEntryList[i].name != "---")
            {
                highscores.highscoreEntryList.RemoveAt(i);
                break;
            }
        }
        // Save updated Highscores
        string json = JsonUtility.ToJson(highscores);
        PlayerPrefs.SetString("HighscoreTable", json);
        PlayerPrefs.Save();
    }

    private void Refresh()
    {
        string jsonString = PlayerPrefs.GetString("HighscoreTable");
        Highscores highscores = JsonUtility.FromJson<Highscores>(jsonString);

        // Sort entry list by Score
        for (int i = 0; i < highscores.highscoreEntryList.Count; i++)
        {
            for (int j = i + 1; j < highscores.highscoreEntryList.Count; j++)
            {
                if (highscores.highscoreEntryList[i].score < highscores.highscoreEntryList[j].score)
                {
                    // Swap
                    HighscoreEntry tmp = highscores.highscoreEntryList[i];
                    highscores.highscoreEntryList[i] = highscores.highscoreEntryList[j];
                    highscores.highscoreEntryList[j] = tmp;
                }
            }
        }
        // The --- entry must be at the botoom of the leaderboard
        for (int i = 0; i < highscores.highscoreEntryList.Count; i++)
        {
            if (highscores.highscoreEntryList[i].name == "---" && i != 0)
            {
                HighscoreEntry tmp = highscores.highscoreEntryList[i];
                highscores.highscoreEntryList[i] = highscores.highscoreEntryList[highscores.highscoreEntryList.Count - 1];
                highscores.highscoreEntryList[highscores.highscoreEntryList.Count - 1] = tmp;
            }
        }

        highscoreEntryTransformList = new List<Transform>();
        foreach (HighscoreEntry highscoreEntry in highscores.highscoreEntryList)
        {
            if (highscoreEntry.name == "---")
            {
                CreateHighscoreEntryTransform(highscoreEntry, entryContainer, highscoreEntryTransformList, true);
            }
            else
            {
                CreateHighscoreEntryTransform(highscoreEntry, entryContainer, highscoreEntryTransformList, false);
            }
        }
    }

    private class Highscores 
    {
        public List<HighscoreEntry> highscoreEntryList;
    }

    [System.Serializable]
    private class HighscoreEntry
    {
        public int score;
        public string name;
    }
}
