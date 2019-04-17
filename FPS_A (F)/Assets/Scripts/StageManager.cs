using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageManager : MonoBehaviour
{
    public static StageManager instance;

    public GameObject stage;
    public GameObject construction;

    int currentStage;
    int clearStage;

    private void Awake()
    {
        instance = this;

        //데이터 로드
        clearStage = CryptoPlayerPrefs.GetInt("clearStage");

        if (CryptoPlayerPrefs.GetString("TitleOnlyStage") == "Off")
        {
            currentStage = clearStage + 1;
        }

        else
        {
            currentStage = CryptoPlayerPrefs.GetInt("TitlePlayStage");
        }
    }

    // Use this for initialization
    void Start ()
    {        
        CryptoPlayerPrefs.SetInt("currentStage", currentStage); //현재층 업데이트      
        if (CryptoPlayerPrefs.GetString("TitleOnlyStage") == "Off")
        {          
            CryptoPlayerPrefs.SetInt("currentStage", currentStage); //현재층 업데이트          
        }

    }
}
