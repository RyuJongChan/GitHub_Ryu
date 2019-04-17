using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartScenePlayer : MonoBehaviour
{
    public static StartScenePlayer instance;
    public float StepDelay = 0.6f;
    public Transform player;

    SWS.splineMove SPS;

    bool IsStepstate;

    private void Awake()
    {
        instance = this;
        SPS = GetComponent<SWS.splineMove>();
    }

    // Start is called before the first frame update
    void Start()
    {
        StartSceneSound.instance.PlayBGM(StartSceneSound.instance.mainBgm, 0.0f, true);
    }

    // Update is called once per frame
    void Update()
    {
        StartCoroutine(StepRun());
        
    }

    IEnumerator StepRun()
    {
        if (!IsStepstate)
        {
            IsStepstate = true;
            yield return new WaitForSeconds(StepDelay);

            AudioClip[] rndAudio = {StartSceneSound.instance.step_A,
                     StartSceneSound.instance.step_B, StartSceneSound.instance.step_C};

            StartSceneSound.instance.PlaySfx(player.position, rndAudio[Random.Range(0, 2)],
                       0, 1.0f);
            IsStepstate = false;
        }
    }

    private void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "StartSnd")
        {
            SPS.speed = 10.0f;
        }

        else if (coll.tag == "StartFirst")
        {
            SPS.speed = 5.0f;
        }

        else if (coll.tag == "Carsnd")
        {
            StartSceneSound.instance.PlaySfx(this.transform.position, StartSceneSound.instance.carsnd, 0, StartSceneSound.instance.sfxVolum);
        }

        else if (coll.tag == "StartFirst")
        {
           StepDelay = 0.6f;
        }
    }
}
