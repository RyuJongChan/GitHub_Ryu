using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BloodEffect : MonoBehaviour
{
    public static Image image;

    public Sprite blood01;  //플레이어 체력 20%이상일때
    public Sprite blood02;  //플레이어 체력 20%미만일때

    public Color startColor = new Color(1, 1, 1, 0);
    public Color endColor = new Color(1, 1, 1, 1);

    void Start ()
    {
        image = GetComponent<Image>();
    }	
  
    void Update()
    {
        if (PlayerState.instance.playerState == PlayerState.PLAYERSTATE.DAMAGE)
        {           
            if (GameManager.instance.playerHp >= GameManager.instance.playerMaxHp * 0.2)
            {
                StartCoroutine(Fade_Effect());
            }
            else
            {
                image.sprite = blood02;
                image.color = Color.Lerp(endColor, startColor, Mathf.PingPong(Time.time, 1.0f));
            }
        }
    }

    //페이드 처리 코루틴함수
    IEnumerator Fade_Effect()
    {
        image.sprite = blood01;
        image.color = startColor;

        for (float i = 1f; i >= -0.1f; i -= 0.02f)
        {
            Color color = new Vector4(1, 1, 1, i);
            image.color = color;
            yield return new WaitForEndOfFrame();
        }
    }
}
