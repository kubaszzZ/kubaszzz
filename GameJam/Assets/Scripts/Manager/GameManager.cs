using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class GameManager : MonoBehaviour
{
    //private string m_Copyright = "PandadaStudio";

    public static GameManager Instance
    {
        get;
        private set;
    }

    private void Awake()
    {
        Instance = this;
    }

    private void Update()
    {
        // 全局控制
        //foreach (KeyCode kcode in System.Enum.GetValues(typeof(KeyCode)))
        //{
        //    if (Input.GetKeyDown(kcode))
        //    {
        //        Debug.Log(kcode);
        //    }
        //}
        //float x = Input.GetAxis("Horizontal_Left");
        //if (x != 0)
        //{
        //    Debug.Log(x);
        //}
    }

    private void OnGUI()
    {
        foreach (KeyCode kcode in System.Enum.GetValues(typeof(KeyCode)))
        {
            if (Input.GetKeyDown(kcode))
            {
                GUI.Label(new Rect(10, 10, 100, 100), kcode.ToString());
            }
        }
    }
}
