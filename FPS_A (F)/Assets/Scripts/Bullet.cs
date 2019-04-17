using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{   
    public static Bullet instance;

    Transform tr;
    Rigidbody rbody;

    float bulletSpeed = 4000.0f;    
    int num = 0;

    private void Awake()
    {
        instance = this;
    }

    // Use this for initialization
    void Start ()
    {     
        tr = transform;  //직접적인 참조캐싱
        rbody = GetComponent<Rigidbody>();
        rbody.AddForce(tr.forward * bulletSpeed);
        Destroy(tr.gameObject, 3.0f);      
    }

    private void Update()
    {               
        float distance = Vector3.Distance(GameController.instance.spPos, this.tr.position);

        if (distance >= 4.0f)
        {
            Bullet_Rotation(GameController.instance.bulletAngle);
        }
    }

    //총알 회전 함수
    public void Bullet_Rotation(float rotationAngle)
    {
        if (num == 0)
        {
            tr.rotation = new Quaternion(tr.rotation.x - (0.01f * rotationAngle), tr.rotation.y, tr.rotation.z, tr.rotation.w);
            num = 1;
        }
    }

    //총알 충돌시 이펙트생성/ 데미지부여
    void OnCollisionEnter(Collision coll)
    {      
        Vector3 rndRot = Vector3.forward * Random.Range(200, 320);

        int collisionLayer = coll.gameObject.layer;

        if (collisionLayer == LayerMask.NameToLayer("Ground"))
        {
            Destroy(tr.gameObject);  //자기 자신

            GameObject obj = Instantiate(ParticleManager.instance.sandImpact, tr.position, tr.rotation);
            obj.transform.localRotation = Quaternion.Euler(rndRot);
        }

        else if (collisionLayer == LayerMask.NameToLayer("Stage"))
        {
            Destroy(tr.gameObject);  //자기 자신

            GameObject obj = Instantiate(ParticleManager.instance.concImpact, tr.position, tr.rotation);
            obj.transform.localRotation = Quaternion.Euler(rndRot);
        }

        else if (collisionLayer == LayerMask.NameToLayer("Enemy"))
        {
            Destroy(tr.gameObject);  //자기 자신

            GameObject obj = Instantiate(ParticleManager.instance.bloodImpact, tr.position, tr.rotation);
            obj.transform.localRotation = Quaternion.Euler(rndRot);

            coll.gameObject.SendMessage("EnemyDamage", SendMessageOptions.DontRequireReceiver);
        }            
    }
}
