using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class GameManager : MonoBehaviour
{
    public static GameManager instance;

    public bool Clear = false;
    public int ZoomNum = 0;
    public int playerHp;
    public int playerMaxHp;
    public int Gun_Num = 0;
    public float Gun_BoundAndFirespeed = 0.2f;   

    //플레이어 레벨 관련 변수
    public int playerLevel;
    public float[] playerLimitExp;  //목표경험치
    public float playerCurrentExp;  //현재 경험치
    public float playerMaxExp;      //현재 최대 경험치

    //체력뷰, 레벨뷰, 경험치바 뷰
    public GameObject playerEnergyBar;
    public GameObject playerLevelView;
    public GameObject playerExpBar;
  
    //라이트 환경 구성
    public Light lightShiny;
    public Light lightNight;
    public Light lightSpot;

    //밤낮
    float DayTime = 0;
    [HideInInspector]
    public bool isShiny = false;
    [HideInInspector]
    public bool isNight = false;

    //스테이지 정보
    int currentStage;
    int clearStage;   

    //골드 정보
    public int coin = 0;
    public Text coinText;  

    //공격력 셋팅
    public int playerPower = 1;
    public int[] playerPowerTable;
    public int playerPowerLevel = 1;
    public int playerAllpower;
    public int playerNumpower;

    //최대 체력 셋팅
    public int playerMaxHpLevel = 1;
    public int[] playerMaxHpTable;
    
    public GameObject guncollection;
    public GameObject Zoom_UI;  
    public GameObject ZoomButton;
    
    public GameObject ZoomCamGO;
    public GameObject Nortouch;
    public GameObject Zoomtouch;   
    public GameObject ChangeGunButton;
    public GameObject ChangeGrButton;
    public GameObject TitleButton;
    public GameObject AttButton;      
    
    //카메라관련
    public Camera MainCam;
    public Camera ZoomCamera;
    public Camera shakerCamera;
    public Vector3 originMainCamPos = Vector3.zero;
    public Vector3 originSpawnPos = Vector3.zero;

    Vector3 oriGuncolPos;

    //수류탄
    public GameObject GrGageBar;
    public float grTime;
    public GameObject GRM;
    public GameObject TempGrenade;
    int grNum = 3;
    public float tempgrTime;
    bool SplintState = false;

    //승리, 패배문구
    public GameObject victoryCan;
    public Text victorytext;
    public GameObject dieCan;
    public Text youdietext;
    public GameObject ingameCan;
    public GameObject contCan;
    float textTime = 0;

    //main >> 타이틀씬
    public GameObject titleYesorNo;

    public Image touchpad;
    public Image touchzoom;
    public GameObject aimCan;

    //플레이어 이동관련
    public float playerMoveSpeed = 4.0f;

    private void Awake()
    {
        originSpawnPos = GameController.instance.spawnPoint.localPosition;
        originMainCamPos = GameController.instance.mainCam.localPosition;
        instance = this;
        oriGuncolPos = guncollection.transform.localPosition;
        Zoomtouch.SetActive(false);
                
        //스테이지 데이터 로드       
        playerMaxExp = CryptoPlayerPrefs.GetFloat("playerMaxExp"); //최대 경험치
        currentStage = CryptoPlayerPrefs.GetInt("currentStage");   //현재 스테이지
        clearStage = CryptoPlayerPrefs.GetInt("clearStage");       //클리어한 스테이지

        //레벨,코인 초기화
        playerLevel = 1;
        coin = 0;
        playerLevelView.GetComponentInChildren<Text>().text = playerLevel.ToString();
        coinText.text = coin.ToString();

        //경험치 초기화
        playerMaxExp = playerLimitExp[0];  
        playerCurrentExp = 0;
        playerExpBar.GetComponent<EnergyBar>().SetValueCurrent((int)playerCurrentExp);
        playerExpBar.GetComponent<EnergyBar>().SetValueMax((int)playerMaxExp);     

        SceneManager.LoadScene("Stage", LoadSceneMode.Additive);              
    }
   
    // Use this for initialization
    void Start ()
    {
        playerEnergyBar.GetComponent<EnergyBar>().SetValueMin(0);
        playerEnergyBar.GetComponent<EnergyBar>().SetValueMax(playerMaxHp);
        playerEnergyBar.GetComponent<EnergyBar>().SetValueCurrent(playerMaxHp);
        GrGageBar.GetComponent<EnergyBar>().SetValueMin(0);
        
        playerAllpower = 3;
        
        SoundManager.instance.PlayBGM(SoundManager.instance.mainBgm, 0, true);
      
        isShiny = true;      

        playerLevel = 1;  //레벨 초기화
        playerMaxExp = playerLimitExp[0];  //첫번째가 기준값
        
    }

    // Update is called once per frame
    void Update ()
    {
        playerEnergyBar.GetComponent<EnergyBar>().SetValueCurrent(playerHp);

        coinText.text = coin.ToString();

        //Change_Player_Power();

        DayTime += Time.deltaTime;

        Shiny_And_Night(30.0f);       

        Victory_FontSize();

        //게임 종료
        if (Application.platform == RuntimePlatform.Android)
        {
            if (Input.GetKeyDown(KeyCode.Escape))
            {
                //메세지 박스
                Title_Yes_Or_No();
            }
        }
    }

    void Shiny_And_Night(float sec)
    {
        if (DayTime <= sec)
        {
            isShiny = true;
            isNight = false;

            lightShiny.gameObject.SetActive(true);
            lightNight.gameObject.SetActive(false);
            lightSpot.gameObject.SetActive(false);
            HealItem.instance.healLight.gameObject.SetActive(false);
        }

        if (DayTime > sec)
        {
            isShiny = false;
            isNight = true;

            lightShiny.gameObject.SetActive(false);
            lightNight.gameObject.SetActive(true);
            lightSpot.gameObject.SetActive(true);
            HealItem.instance.healLight.gameObject.SetActive(true); ;
        }

        if (DayTime >= (sec*2))
        {
            DayTime = 0;
        }
    }

    public void Change_Gun(int GunNum)
    {      
        GameController.instance.useGun.SetActive(true);            
        GrGageBar.GetComponent<EnergyBar>().SetValueCurrent(0);
        AttButton.SetActive(true);
        GRM.SetActive(false);

        if (ZoomNum != 1)
        {
            ChangeGrButton.SetActive(true);
        }

        ZoomButton.SetActive(true);
        
        for (int ChangeNum = 0; ChangeNum < GameController.instance.Gun_.Length; ChangeNum++)
        {
            if (ChangeNum == GunNum)
            {
                GameController.instance.Gun_[ChangeNum].SetActive(true);
                if (GunNum == 0) { Gun_BoundAndFirespeed = 0.3f; playerNumpower = 2; }
                else if (GunNum == 1) { Gun_BoundAndFirespeed = 0.6f; playerNumpower = 3; }
                else if (GunNum == 2) { Gun_BoundAndFirespeed = 0.2f; playerNumpower = 1; }
                else if (GunNum == 3) { Gun_BoundAndFirespeed = 1.0f; playerNumpower = 6; }
            }

            Change_Player_Power();

            if (ChangeNum != GunNum)
            {
                GameController.instance.Gun_[ChangeNum].SetActive(false);
            }

        }                
    }   

    public void Change_Gr()
    {        
        GameController.instance.useGun.SetActive(false);
        ZoomButton.SetActive(false);
        AttButton.SetActive(false);

        GRM.SetActive(true);

        if (grTime >= 1.0f && grNum >= 1)
        {           
            grTime = 0;
            --grNum;
        }
    }

    public void Press_Gr()
    {
        grTime += Time.deltaTime;

        GrGageBar.GetComponent<EnergyBar>().SetValueCurrent((int)grTime);

        if (grTime >= 1.0f)
        {
            tempgrTime = grTime;

            if (grTime >= 3.0f || tempgrTime >= 3.0f)
            {
                grTime = 3.0f; tempgrTime = 3.0f;
            }

            GrenadeMode.instance.GrenadeMsplint.SetActive(false);

            if (SplintState == false)
            {
                Instantiate(GrenadeMode.instance.TempSplint, GRM.transform.position, GRM.transform.rotation);
                SplintState = true;
            }

        }
    }

    public void Throw_Gr()
    {
        if (tempgrTime >= 1.0f)
        {
            SplintState = false;
            
            Instantiate(TempGrenade, GRM.transform.position, GRM.transform.rotation);
            GRM.SetActive(false);
            Grenade.instance.grPower = Grenade.instance.grPower * tempgrTime;
            GrGageBar.GetComponent<EnergyBar>().SetValueCurrent(0);
        }

        grTime = 0; tempgrTime = 0;
    }

    public void Zoom_Camera()
    {
        ZoomNum++;

        if (ZoomNum >= 2) ZoomNum = 0;

        if (ZoomNum == 1)
        {
            guncollection.transform.localPosition = Vector3.Lerp(guncollection.transform.localPosition, new Vector3(-2.17f, -1.5f, 20.5f), 1.0f);
          
            GameController.instance.spawnPoint.position = ZoomCamera.transform.position;
            GameController.instance.spawnPoint.localPosition = new Vector3(GameController.instance.spawnPoint.localPosition.x, 1.3f, -19.7f);           

            Zoom_UI.SetActive(true);
            ZoomCamGO.SetActive(true);
            Zoomtouch.SetActive(true);

            touchzoom.color = new Color(1, 1, 1, 0);
            
            ChangeGrButton.SetActive(false);
            ChangeGunButton.SetActive(false);
            Nortouch.SetActive(false);            

            ZoomCamera.fieldOfView = 30.0f;
            shakerCamera.fieldOfView = 30.0f;

            for (int i = 0; i < GameController.instance.Aim_.Length; i++)
            {
                GameController.instance.Aim_[i].SetActive(false);
            }          
        }

        else
        {           
            guncollection.transform.localPosition = Vector3.Lerp(guncollection.transform.localPosition, oriGuncolPos, 1.0f);

            GameController.instance.spawnPoint.localPosition = originSpawnPos;          

            Zoom_UI.SetActive(false);            
            ZoomCamGO.SetActive(false);
            Zoomtouch.SetActive(false);

            ChangeGrButton.SetActive(true);
            ChangeGunButton.SetActive(true);
            Nortouch.SetActive(true);
            touchpad.color = new Color(1, 1, 1, 0);

            ZoomCamera.fieldOfView = 60.0f;
            shakerCamera.fieldOfView = 60.0f;

            for (int i = 0; i < GameController.instance.Aim_.Length; i++)
            {
                GameController.instance.Aim_[i].SetActive(true);
            }
        }
    }

    public void Move_AimBound()
    {
        GameController.instance.Aim_Bound(10.0f);       
    }

    //게임 종료 메세지 박스
    public void LogOut_Yes()
    {
        Application.Quit();
    }
    
    public void LogOut_No()
    {
        Time.timeScale = 1;

        contCan.SetActive(true);
        ingameCan.SetActive(true);
        aimCan.SetActive(true);

        titleYesorNo.SetActive(false);
        touchpad.color = new Color(1, 1, 1, 0);     
    }

    //경험치 계산 함수
    public float Exp_Cal(float exp)
    {
        playerCurrentExp += exp;  //현재 경험치 계산

        if (playerLevel < playerLimitExp.Length)
        {
            //현재경험치가 목표경험치보다 높거나 같다면
            if (playerCurrentExp >= playerLimitExp[playerLevel - 1])
            {
                playerLevel += 1;  //레벨1단계 상승
                Level_Up();

                playerCurrentExp = Mathf.Abs(playerLimitExp[playerLevel - 2] - playerCurrentExp);

                playerMaxExp = playerLimitExp[playerLevel - 1];

            }
        }

        else if(playerCurrentExp >=  playerLimitExp[playerLimitExp.Length-1]     )
        {
            playerLevel += 1;  //레벨1단계 상승
            Level_Up();
            playerCurrentExp = Mathf.Abs(playerLimitExp[playerLimitExp.Length - 1] - playerCurrentExp);

            playerMaxExp = playerLimitExp[playerLimitExp.Length - 1];  //마지막 목표경험치를 지속적으로 사용

        }
      
        //데이터 업데이트      
        CryptoPlayerPrefs.SetInt("playerLevel", playerLevel); //레벨
        CryptoPlayerPrefs.SetFloat("playerCurrentExp", playerCurrentExp); //현재 경험치
        CryptoPlayerPrefs.SetFloat("playerMaxExp", playerMaxExp); //최대 경험치

        //View관련
        playerLevelView.GetComponentInChildren<Text>().text = playerLevel.ToString();  //현재 레벨 표시
        playerExpBar.GetComponent<EnergyBar>().SetValueMax( (int) playerMaxExp); //경험치 최대값 변경
        playerExpBar.GetComponent<EnergyBar>().SetValueCurrent((int)playerCurrentExp);  //현재 경험치값
        
        return exp;  //경험치 반환
    }

    void Level_Up()
    {
        float lvuptime = Time.deltaTime;
        SoundManager.instance.PlaySfx(transform.position,
                SoundManager.instance.levelUp, 0,
                SoundManager.instance.sfxVolum);

        playerMaxHp = playerMaxHp + 10;
        
        playerEnergyBar.GetComponent<EnergyBar>().SetValueMax(playerMaxHp);
        playerEnergyBar.GetComponent<EnergyBar>().SetValueCurrent(playerMaxHp);      
    }

    public void Title_Yes_Or_No()
    {
        ingameCan.SetActive(false);
        contCan.SetActive(false);
        aimCan.SetActive(false);

        titleYesorNo.SetActive(true);
        Time.timeScale = 0;
    }

    //타이틀로 돌아가기 버튼
    public void Title_Go()
    {     
        Time.timeScale = 1;
        CryptoPlayerPrefs.SetString("TitleGo", "On");
        SceneManager.LoadScene("Loading");
    }

    //코인 획득 정보
    public void Coin_Add()
    {                              
        coin = coin + EnemyManager.instance.enemyCoinAmount[Random.Range(0, EnemyManager.instance.enemyCoinAmount.Length)];
        coinText.text = coin.ToString();      
    }

    public void FirePress()
    {      
        GameController.instance.isShoot = true;        
    }

    public void FireUp()
    {
        GameController.instance.isShoot = false;
    }

    public void Change_Player_Power()
    {
        playerAllpower = playerNumpower + playerPowerLevel;
    }
   
    void Victory_FontSize()
    {    
        textTime += Time.deltaTime;
        float tempTime = 0.3f;

        if (textTime >= tempTime)
        {
            textTime = 0.0f;

            if (victorytext.fontSize <= 90)
            {
                victorytext.fontSize = victorytext.fontSize + 5;
                victorytext.color = new Color(victorytext.color.r, victorytext.color.g, victorytext.color.b, victorytext.color.a + 0.5f);               
            }

            else if (victorytext.fontSize > 90)
            {
                victorytext.fontSize = victorytext.fontSize - 5;
                victorytext.color = new Color(victorytext.color.r, victorytext.color.g, victorytext.color.b, 0.5f);
            }

            if (youdietext.fontSize <= 80)
            {
                youdietext.fontSize = youdietext.fontSize + 5;
                youdietext.color = new Color(youdietext.color.r, youdietext.color.g, youdietext.color.b, youdietext.color.a + 0.5f);
            }

            else if (youdietext.fontSize > 80)
            {
                youdietext.fontSize = youdietext.fontSize - 5;
                youdietext.color = new Color(youdietext.color.r, youdietext.color.g, youdietext.color.b, 0.5f);
            }
        }
    }

    //-------------------------------------------------
    //CryptoPlayerPrefs 의 해시키를 찾는 메소드로
    // 해당키가 있으면 불러오고 없으면 새로 생성 (정수값)
    //---------------------------------------------------
    public void CryptoPlayerPrefs_HasKeyIntFind(string key, int value)
    {
        if ( ! CryptoPlayerPrefs.HasKey(key)  )
        {
            CryptoPlayerPrefs.SetInt(key, value);
        }

        else
        {
            CryptoPlayerPrefs.GetInt(key, 0);
        }
    }

    //-------------------------------------------------
    //CryptoPlayerPrefs 의 해시키를 찾는 메소드로
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
    //CryptoPlayerPrefs 의 해시키를 찾는 메소드로
    // 해당키가 있으면 불러오고 없으면 새로 생성 (문자열값)
    //---------------------------------------------------
    public void CryptoPlayerPrefs_HasKeyStringFind(string key,  string value)
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
