using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HealItem : MonoBehaviour
{
    public static HealItem instance;

    public Light healLight;

    private void Awake()
    {
        instance = this;
    }

    private void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "Player")
        {
            GameManager.instance.playerHp = GameManager.instance.playerMaxHp;
            BloodEffect.image.color = new Color(1, 1, 1, 0);  //초기화

            GameManager.instance.playerEnergyBar.GetComponent<EnergyBar>().SetValueCurrent(GameManager.instance.playerHp);

            ParticleManager.instance.HealEffect.SetActive(true);

            //사운드 효과
            SoundManager.instance.PlaySfx(transform.position,
            SoundManager.instance.itemUse,
            0,
            SoundManager.instance.sfxVolum);
        }
    }

    private void OnTriggerExit(Collider coll)
    {
        if (coll.tag == "Player")
        {
            ParticleManager.instance.HealEffect.SetActive(false);
        }
    }
}