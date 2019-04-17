using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    public static SoundManager instance;

    public float sfxVolum = 0.1f;  //효과음 볼륨
    public float gunVolum = 0.1f;
    public float bgmVolum = 0.1f;  //배경음 볼륨
    public float VolumUp = 1.0f;

    bool isSfxMute = false;

    AudioSource bgmSource; // BGM용 오디오 소스  
    public AudioClip mainBgm;

    //좀비 사운드
    public AudioClip zombieAtk;
    public AudioClip bloodStabHit;
    public AudioClip handAtk;
    public AudioClip bloodDeath; 

    //플레이어 사운드
    public AudioClip itemUse;
    public AudioClip levelUp;
    public AudioClip step_A;
    public AudioClip step_B;
    public AudioClip step_C;
    public AudioClip fireSnd;
    public AudioClip grSnd;
    public AudioClip lbossSnd;

    private void Awake()
    {
        instance = this;
    }

    public void PlaySfx(Vector3 pos, AudioClip sfx, float delayed, float volm)
    {
        if (isSfxMute) return; //음소거 옵션

        StartCoroutine(PlaySfxDelayed(pos, sfx, delayed, volm));
    }

    public void PlaySfx2(Vector3 pos, AudioClip sfx, float delayed, float volm)
    {
        if (isSfxMute) return; //음소거 옵션

        StartCoroutine(PlaySfxDelayed2(pos, sfx, delayed, volm));
    }

    IEnumerator PlaySfxDelayed(Vector3 pos, AudioClip sfx, float delayed, float volm)
    {
        yield return new WaitForSeconds(delayed);

        //동적 생성
        GameObject sfxObj = new GameObject("Sfx");
        sfxObj.transform.position = pos;  //사운드 발생위치

        //동적 생성한 오브젝트 자체에 AudioSource콤포넌트 추가
        AudioSource _aud = sfxObj.AddComponent<AudioSource>();

        _aud.clip = sfx;

        //거리에 의한 소리 높낮이
        _aud.minDistance = 1.0f;
        _aud.maxDistance = 5.0f;
        
        _aud.volume = volm;

        _aud.Play();  //효과음 재생

        Destroy(sfxObj, sfx.length);  //효과음이 종료되면 삭제
    }

    IEnumerator PlaySfxDelayed2(Vector3 pos, AudioClip sfx, float delayed, float volm)
    {
        yield return new WaitForSeconds(delayed);

        //동적 생성
        GameObject sfxObj = new GameObject("Sfx");
        sfxObj.transform.position = pos;  //사운드 발생위치

        //동적 생성한 오브젝트 자체에 AudioSource콤포넌트 추가
        AudioSource _aud = sfxObj.AddComponent<AudioSource>();

        _aud.clip = sfx;

        //거리에 의한 소리 높낮이
        _aud.minDistance = 5.0f;
        _aud.maxDistance = 10.0f;

        _aud.volume = volm;
        
        _aud.Play();  //효과음 재생      

        Destroy(sfxObj, 3.0f);  //효과음이 종료되면 삭제
    }

    public void PlayBGM(AudioClip bgm, float delayed, bool loop) 
    {
        StartCoroutine(PlayBGM_Delayed(bgm, delayed, loop));
    }

    IEnumerator PlayBGM_Delayed(AudioClip bgm, float delayed, bool loop)
    {
        yield return new WaitForSeconds(delayed);

        GameObject bgmObj = new GameObject("BGM");

        if (!bgmSource) bgmSource = bgmObj.AddComponent<AudioSource>();
        bgmSource.clip = bgm;
        
        bgmSource.volume = bgmVolum;
        bgmSource.loop = loop;

        bgmSource.Play();
    }
} 
