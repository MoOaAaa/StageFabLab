using UnityEngine;
using UnityEngine.UI;

public class JoueurUI : MonoBehaviour
{
    public int point;
    public int combo;
    public Text valeurPoint;
    public Text valeurCombo;

    void Start()
    {
        valeurPoint.text = "Points : " + point.ToString();
        valeurCombo.text = "Combo : " + combo.ToString();
    }

    void Update()
    {
        valeurPoint.text = "Points : " + point.ToString();
        valeurCombo.text = "Combo : " + combo.ToString();
    }
}
