using Sirenix.OdinInspector;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrabMono : MonoBehaviour
{
    [BoxGroup("玩家属性")]
    [LabelText("最大饿死时间")]
    public float StraveDeadTime;

    [BoxGroup("玩家属性")]
    [LabelText("脱离壳最大时间")]
    public float GoOutDeadTime;

    //[BoxGroup("UI")]
    // [LabelText("吃分UI")]
    // private HUDText hudText;

    private float m_StarveTime = 0; // 当前饥饿时间
    private float m_GoOutTime = 0; // 当前脱壳时间

    [HideInInspector] public int Score = 0; // 得分
    [HideInInspector] public int ShellWeight; // 壳重量
    [HideInInspector] public int CrabWeight = 1; // 螃蟹重量
    public int Level = 1; // 壳等级
    [HideInInspector] public bool HasShell = false; // 是否有壳
    [HideInInspector] public bool IsChangeShell = false; // 是否改变壳
    [HideInInspector] public float ShellSpeed; // 有壳速度
    [HideInInspector] public float HinderSpeed; // 阻碍速度

    protected float SpeedScale = 15f;

    //protected Animator m_Anim;
    protected Collider2D m_collider;
    protected Rigidbody2D m_rigid;

    private void Init()
    {
        ShellSpeed = DataManager.Instance.NoShellSpeed[Level - 1];
    } 

    private void Start()
    {
        //m_Anim = GetComponent<Animator>();
        m_collider = GetComponent<Collider2D>();
        m_rigid = GetComponent<Rigidbody2D>();

        Init();
    }

    protected virtual void FixedUpdate()
    {
        if (CrabWeight / 5 > Level)
        {
            // TODO 提示胀死
            m_GoOutTime += Time.deltaTime;
            if (m_GoOutTime > 18f)
            {
                m_GoOutTime = 0;
                Revive();
            }
        }

        if (GameManager.Instance.IsStart)
        {
            // TODO 提示饿死
            m_StarveTime += Time.deltaTime;
            if (m_StarveTime > 18f)
            {
                m_StarveTime = 0;
                Revive();
            }
        }
    }

    protected virtual void OnCollisionEnter2D(Collision2D collision)
    {
        switch (collision.gameObject.tag)
        {
            case Tag.Hole:
                Score += DataManager.Instance.Score[Level - 1];
                Revive();
                break;

            case Tag.Nutrition:
                //AudioSource.PlayClipAtPoint(AudioManager.AudioClipsDic["Coin"], transform.position);
                m_StarveTime = 0;
                CrabWeight += collision.gameObject.GetComponent<Nutrition>().Nutri;
                Destroy(collision.gameObject);
                break;
        }
    }

    private void Revive()
    {
        Level = 1;
        CrabWeight = 1;
        HasShell = true;
        Init();
        transform.position = ComputeBornPoint(transform.position, 1.5f);
    }

    private Vector3 ComputeBornPoint(Vector3 original, float radius)
    {
        Vector3 randomRotation = Random.rotation.eulerAngles.normalized;
        int temp = Random.Range(-1, 1);
        if (temp < 0)
            randomRotation.x = -randomRotation.x;
        temp = Random.Range(-1, 1);
        if (temp < 0)
            randomRotation.y = -randomRotation.y;
        return new Vector3(original.x + randomRotation.x * radius, original.y + randomRotation.y * radius, 0);
    }
}
