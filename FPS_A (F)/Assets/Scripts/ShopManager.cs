using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShopManager : MonoBehaviour
{

    public GameObject shopButton;
    public GameObject shopUI;

    //코인정보
    public UILabel coinLabel;

    //유저캐릭터 정보
    public UILabel atkLabel;
    public UILabel hpMaxLabel;

    //유저 캐릭터 기능 레벨
    public UILabel atkLevel;
    public UILabel hpMaxLevel;

    //구입 미리 보기
    int atkPreview = 1;
    int hpMaxPreview = 1;

    //변화 유무
    bool isAtkChange = false;
    bool ishpMaxChange = false;

    //가격 라벨 정보
    public UILabel atkPriceLabel;
    public UILabel hpMaxPriceLabel;

    //가격 관리자
    public int[] attackPrice;
    public int[] hpMaxPrice;

    //최고 레벨 상수 값
    const int MAXVALUE = 3;

    void Awake()
    {
        Init();
    }

    void Init()
    {
        shopButton.SetActive(true);
        shopUI.SetActive(false);
    }

    public void OpenShop()
    {
        shopUI.SetActive(true);
        shopButton.SetActive(false);      
        
        GameManager.instance.ChangeGrButton.SetActive(false);
        GameManager.instance.ZoomButton.SetActive(false);
        GameManager.instance.ChangeGunButton.SetActive(false);
        GameManager.instance.TitleButton.SetActive(false);
        GameManager.instance.contCan.SetActive(false);
        for (int i = 0; i < GameController.instance.Aim_.Length; i++)
        {
            GameController.instance.Aim_[i].SetActive(false);
        }

        //데이터 로드       
        coinLabel.text = GameManager.instance.coin.ToString();       
        atkLevel.text = GameManager.instance.playerPowerLevel.ToString();        
        hpMaxLevel.text = GameManager.instance.playerMaxHpLevel.ToString();

        //공격력 정보        
        atkLabel.text = "ATK  " + GameManager.instance.playerPowerTable[GameManager.instance.playerPowerLevel - 1].ToString();

        //공격력 가격 정보      
        atkPriceLabel.text = attackPrice[GameManager.instance.playerPowerLevel - 1].ToString();

        //최대 체력 정보     
        hpMaxLabel.text = "HP  " + GameManager.instance.playerMaxHpTable[GameManager.instance.playerMaxHpLevel - 1].ToString();

        //최대체력 가격 정보      
        hpMaxPriceLabel.text = hpMaxPrice[GameManager.instance.playerMaxHpLevel - 1].ToString();

        Time.timeScale = 0;  //일시정지
    }

    public void CloseShop()
    {       
        shopUI.SetActive(false);
        shopButton.SetActive(true);

        atkPreview = GameManager.instance.playerPowerLevel;
        hpMaxPreview = GameManager.instance.playerMaxHpLevel;

        GameManager.instance.ChangeGrButton.SetActive(true);
        GameManager.instance.ZoomButton.SetActive(true);
        GameManager.instance.ChangeGunButton.SetActive(true);
        GameManager.instance.TitleButton.SetActive(true);
        GameManager.instance.contCan.SetActive(true);
        for (int i = 0; i < GameController.instance.Aim_.Length; i++)
        {
            GameController.instance.Aim_[i].SetActive(true);
        }    
        Time.timeScale = 1;  //해지
    }

    //공격력 미리보기
    public void AttackPricePreview()
    {
        if( int.Parse(atkLevel.text) < MAXVALUE && atkPreview <= GameManager.instance.playerPowerLevel)
        {
            isAtkChange = true;
           
            atkPreview += 1;  //누적
            atkLevel.text = atkPreview.ToString();

            //Debug.Log("공격력 레벨: " + int.Parse(atkLevel.text));

            //게임 메니저를 찾을 수 있음
            if(GameObject.Find("Manager"))
            {
                atkLabel.text = "ATK = +"+ GameManager.instance.playerPowerTable[
                                    atkPreview - 1].ToString();

                atkPriceLabel.text = attackPrice[atkPreview - 1].ToString(); 
            }
        }
        else
        {
            //Debug.Log("더이상 업그레이드를 할 수 없습니다!");
            return;
        }
    }

    //공격력 구입
    public void AttackPurchase()
    {
        if (isAtkChange && int.Parse(atkLevel.text)  <= MAXVALUE  )
        {
            if((GameManager.instance.coin) >= int.Parse(atkPriceLabel.text))
            {                                             
                int currentCoin = GameManager.instance.coin - int.Parse(atkPriceLabel.text);                
                GameManager.instance.coin = currentCoin;

                isAtkChange = false;  //변화 유무 체크

                if( GameObject.Find("Manager"  ))
                {
                    //유저캐릭터 공격력 업데이트                  
                    GameManager.instance.playerPowerLevel += 1;
                    if (GameManager.instance.playerPowerLevel >= 4)
                    {
                        GameManager.instance.playerPowerLevel = 3;
                    }

                    coinLabel.text = currentCoin.ToString();  //상점 코인                
                }               
                atkLabel.text = GameManager.instance.playerPowerLevel.ToString();   //현재 레벨 업데이트
                GameManager.instance.Change_Player_Power();
            }
            else
            {
                return;
                //Debug.Log("소지금이 없습니다!");
            }
        }

        else
        {
            return;
            //Debug.Log("더이상 구입 할 수 없습니다!");
        }
    }  

    //Hp 미리보기
    public void HpMaxPricePreview()
    {
        if (int.Parse(hpMaxLevel.text) < MAXVALUE && hpMaxPreview <= GameManager.instance.playerMaxHpLevel)
        {
            ishpMaxChange = true;
            
            hpMaxPreview += 1;  //누적
            hpMaxLevel.text = hpMaxPreview.ToString();

            //게임 메니저를 찾을 수 있음
            if (GameObject.Find("Manager"))
            {
                hpMaxLabel.text = "HP = +" + GameManager.instance.playerMaxHpTable[hpMaxPreview - 1].ToString();

                hpMaxPriceLabel.text = hpMaxPrice[hpMaxPreview - 1].ToString();
            }
        }       
    }
  
    //최대체력 구입
    public void HpMaxPurchase()
    {
        if (ishpMaxChange && int.Parse(hpMaxLevel.text) <= MAXVALUE)
        {
            if (GameManager.instance.coin >= int.Parse(hpMaxPriceLabel.text))
            {               
                GameManager.instance.playerMaxHpLevel += 1;
                
                int currentCoin = GameManager.instance.coin - int.Parse(hpMaxPriceLabel.text);
                
                GameManager.instance.coin = currentCoin;

                ishpMaxChange = false;  //변화 유무 체크

                if (GameObject.Find("Manager"))
                {                    
                    GameManager.instance.playerMaxHpLevel += 1;
                    if (GameManager.instance.playerMaxHpLevel >= 4)
                    {
                        GameManager.instance.playerMaxHpLevel = 3;
                    }
                    GameManager.instance.playerMaxHp = GameManager.instance.playerMaxHp + GameManager.instance.playerMaxHpTable[GameManager.instance.playerMaxHpLevel - 1];                      
                    GameManager.instance.playerEnergyBar.GetComponent<EnergyBar>().SetValueMax(GameManager.instance.playerMaxHp);
                    GameManager.instance.playerEnergyBar.GetComponent<EnergyBar>().SetValueCurrent(GameManager.instance.playerMaxHp);

                    GameManager.instance.coinText.text = currentCoin.ToString(); //HUD 코인
                    coinLabel.text = currentCoin.ToString();  //상점 코인
                }
            }           
        }     
    }
}
