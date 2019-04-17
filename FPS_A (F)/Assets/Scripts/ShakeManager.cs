using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShakeManager : MonoBehaviour
{
    public Camera shakeCamera;

    public static ShakeManager instance;

    [HideInInspector]
    public bool isShake = false;  //쉐이크 상태 체크

    void Awake()
    {
        instance = this;
    }
   
    void LateUpdate()
    {
        //쉐이크 구동
        StartCoroutine(ShakeCamera(0.3f, 0.05f, 0.01f, 0));
    }
    
    IEnumerator ShakeCamera(float endTime, float senseX, float senseY, float senseZ)
    {
        if (isShake)
        {
            Vector3 pos = Vector3.zero;

            pos.x = Random.Range(-senseX, senseX);
            pos.y = Random.Range(-senseY, senseY);
            pos.z = Random.Range(-senseZ, senseZ);

            shakeCamera.transform.localPosition += pos;

            yield return new WaitForSeconds(endTime);  //쉐이크 종료 시간

            isShake = false;

            //선형보간 함수
            shakeCamera.transform.localPosition = Vector3.Lerp(
                            shakeCamera.transform.localPosition,   //현재 위치
                             Vector3.zero,  //목표 위치
                            Time.deltaTime * 10); //해당값만큼 접근           
        }
    }
}
