using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleManager : MonoBehaviour
{
    public static TitleManager instance;

    //스테이지 레벨
    int currrentStage;
    int clearStage;
    int titlePlayStage;  
    
    public UILabel stageSelect;

    private void Awake()
    {
        instance = this;

        //데이터 생성
        CryptoPlayerPrefs_HasKeyIntFind("currentStage", currrentStage = 1);
        CryptoPlayerPrefs_HasKeyIntFind("clearStage", clearStage = 0);

        CryptoPlayerPrefs_HasKeyStringFind("TitleOnlyStage", "On");
        CryptoPlayerPrefs_HasKeyIntFind("TitlePlayStage", titlePlayStage = 1);

        CryptoPlayerPrefs_HasKeyStringFind("TitleGo", "Off");   //타이틀인지 인게임인지 여부

        //데이터 로드
        currrentStage = CryptoPlayerPrefs.GetInt("currentStage");
        clearStage = CryptoPlayerPrefs.GetInt("clearStage");
        titlePlayStage = CryptoPlayerPrefs.GetInt("titlePlayStage");
        SceneManager.LoadScene("StartStage", LoadSceneMode.Additive);
    }

    // Use this for initialization
    void Start()
    {
        CryptoPlayerPrefs.SetString("TitleGo", "Off");       
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void StartGame()
    {
        if (stageSelect.text == "Lock!") return;

        SceneManager.LoadScene("Loading");  //로딩씬
    }

    //-------------------------------------------------
    // CryptoPlayerPrefs 의 해시키를 찾는 메소드로
    // 해당키가 있으면 불러오고 없으면 새로 생성 (정수값)
    //---------------------------------------------------
    public void CryptoPlayerPrefs_HasKeyIntFind(string key, int value)
    {
        if (!CryptoPlayerPrefs.HasKey(key))
        {
            CryptoPlayerPrefs.SetInt(key, value);
        }

        else
        {
            CryptoPlayerPrefs.GetInt(key, 0);
        }
    }

    //-------------------------------------------------
    // CryptoPlayerPrefs 의 해시키를 찾는 메소드로
    // 해당키가 있으면 불러오고 없으면 새로 생성 (실수값)
    //---------------------------------------------------
    public void CryptoPlayerPrefs_HasKeyFloatFind(string key, float value)
    {
        if (!CryptoPlayerPrefs.HasKey(key))
        {
            CryptoPlayerPrefs.SetFloat(key, value);
        }

        else
        {
            CryptoPlayerPrefs.GetFloat(key, 0);
        }
    }

    //-------------------------------------------------
    // CryptoPlayerPrefs 의 해시키를 찾는 메소드로
    // 해당키가 있으면 불러오고 없으면 새로 생성 (문자열값)
    //---------------------------------------------------
    public void CryptoPlayerPrefs_HasKeyStringFind(string key, string value)
    {
        if (!CryptoPlayerPrefs.HasKey(key))
        {
            CryptoPlayerPrefs.SetString(key, value);
        }

        else
        {
            CryptoPlayerPrefs.GetString(key, "0");
        }
    }
}
