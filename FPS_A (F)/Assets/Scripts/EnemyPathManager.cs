using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyPathManager : MonoBehaviour
{
    public static EnemyPathManager instance;

    public SWS.PathManager[] enemyPath; //패스정보가 담겨있는 객체
 
    private void Awake()
    {
        instance = this;
    }
}
