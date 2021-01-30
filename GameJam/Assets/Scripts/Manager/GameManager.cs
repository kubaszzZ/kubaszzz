using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class GameManager : MonoBehaviour
{
    private float GameTime = 216; // 单局用时上限
    private float GameTimer = 0; // 游戏计时器

    public GameObject Shell;
    public List<GameObject> ShellList = new List<GameObject>();

    public bool IsStart = false; // 游戏是否开始
    private bool isRepeatStart = true; // 是否开始创建Shell

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
        if (IsStart)
        {
            GameTimer += Time.deltaTime;
            
            if (isRepeatStart)
            {
                InvokeRepeating("CreateShell", 0f, 4f);
                isRepeatStart = false;
            }

            if (GameTimer > GameTime)
            {
                // TODO 游戏结束

            }
        }
    }

    private void CreateShell()
    {
        ShellList.Clear();

        // TODO +-
        for (int i = 0; i < 5; ++i)
        {
            float x = Random.Range(4f, 6f);
            float y = Random.Range(1f, 3f);
            GameObject go = Instantiate(Shell, new Vector3(x, y, 0), Quaternion.identity);
            go.transform.parent = gameObject.transform;
            ShellList.Add(go);
        }
    }
}
