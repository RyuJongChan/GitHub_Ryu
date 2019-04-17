using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageIconActive : MonoBehaviour
{
    public GameObject iconActive;
    public GameObject iconLock;

	// Use this for initialization
	void Start ()
    {
        string tmpStr = gameObject.name;

        //한자리 숫자를 가지고 있고 클리어한 스테이지보다 같거나 낮을때
        if (tmpStr.Length == 7 && CryptoPlayerPrefs.GetInt("clearStage") + 1 >= int.Parse(tmpStr.Substring(6, 1)))
        {
            iconActive.SetActive(true);
            iconLock.SetActive(false);
        }

        else if (tmpStr.Length == 8 && CryptoPlayerPrefs.GetInt("clearStage") + 1 >= int.Parse(tmpStr.Substring(6, 2)))
        {
            iconActive.SetActive(true);
            iconLock.SetActive(false);
        }

        else
        {
            iconActive.SetActive(false);
            iconLock.SetActive(true);
        }
    }
	
	// Update is called once per frame
	void Update ()
    {
		
	}

    public void OnClick()
    {
        string tmpStr = gameObject.name;

        if (iconActive.activeSelf)      //iconActive가 true면
        {
            CryptoPlayerPrefs.SetString("TitleOnlyStage", "On");

            if (tmpStr.Length == 7) CryptoPlayerPrefs.SetInt("TitlePlayStage", int.Parse(tmpStr.Substring(6, 1)));
            if (tmpStr.Length == 8) CryptoPlayerPrefs.SetInt("TitlePlayStage", int.Parse(tmpStr.Substring(6, 2)));

            TitleManager.instance.stageSelect.text = "Stage " + CryptoPlayerPrefs.GetInt("TitlePlayStage");
        }

        else
        {
            TitleManager.instance.stageSelect.text = "Lock!";
        }

    }
}
