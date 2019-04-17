using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Loading : MonoBehaviour
{
    AsyncOperation async;  //비동기 씬
    AsyncOperation async2;  
    AsyncOperation async3; 

    public GameObject loadingBar; //로딩객체

    float progress;

    private void Awake()
    {
        loadingBar.GetComponent<EnergyBar>().SetValueMax(100);
        loadingBar.GetComponent<EnergyBar>().SetValueMin(0);
    }

    // Use this for initialization
    void Start ()
    {
        if (CryptoPlayerPrefs.GetString("TitleGo") == "On")
        {
            async = SceneManager.LoadSceneAsync("Title", LoadSceneMode.Single);
        }

        else
        {
            async = SceneManager.LoadSceneAsync("Main", LoadSceneMode.Single);
            async2 = SceneManager.LoadSceneAsync("Shop", LoadSceneMode.Additive);
            async3 = SceneManager.LoadSceneAsync("Stage", LoadSceneMode.Additive);

            DontDestroyOnLoad(this.gameObject);
        }
    }

    // Update is called once per frame
    void Update ()
    {
        if (CryptoPlayerPrefs.GetString("TitleGo") == "Off")
        {
            if (!async3.isDone)
            {
                progress = async.progress * 100.0f;
                loadingBar.GetComponent<EnergyBar>().valueCurrent = (int)progress;
            }

            if (async3.isDone)
            {
                Destroy(this.gameObject);
            }
        }

        else
        {
            //메인에서 타이틀로 가는 경우만 해당
            if (!async.isDone)
            {
                progress = async.progress * 100.0f;
                loadingBar.GetComponent<EnergyBar>().valueCurrent = (int)progress;
                
            }
        }
	}
}
