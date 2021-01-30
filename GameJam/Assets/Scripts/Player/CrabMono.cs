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
    private Vector3 pos; // 出生点


    private float m_StarveTime = 0; // 当前饥饿时间
    private float m_GoOutTime = 0; // 当前脱壳时间

    [HideInInspector] public int Score = 0; // 得分
    [HideInInspector] public int ShellWeight; // 壳重量
    [HideInInspector] public int CrabWeight = 1; // 螃蟹重量
    public int Level = 1; // 壳等级
    [HideInInspector] public bool IsDead = false; // 是否死亡
    [HideInInspector] public bool HasShell = false; // 是否有壳
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
        //m_rigid.mass = CrabWeight + ShellWeight;

        //float x = Input.GetAxis("Horizontal");
        //float y = Input.GetAxis("Vertical");

        //transform.position += new Vector3(x, y, 0);
    }

    protected virtual void OnCollisionEnter2D(Collision2D collision)
    {
        switch (collision.gameObject.tag)
        {
            case Tag.Hole:
                Score += DataManager.Instance.Score[Level - 1];
                transform.position = pos;
                Revive();
                break;

            case Tag.Nutrition:
                //AudioSource.PlayClipAtPoint(AudioManager.AudioClipsDic["Coin"], transform.position);
                CrabWeight += collision.gameObject.GetComponent<Nutrition>().Nutri;
                Destroy(collision.gameObject);

                Debug.Log(CrabWeight);
                break;
        }
    }

    private void Revive()
    {
        Level = 1;
        HasShell = true;
        IsDead = false;
        Init();
        transform.position = Util.ComputeBornPoint(transform.position, 2.0f);
    }
}
