using Sirenix.OdinInspector;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrabMono : MonoBehaviour
{
    [BoxGroup("玩家属性")]
    [LabelText("名称")]
    public string CrabName;

    [BoxGroup("玩家属性")]
    [LabelText("精灵")]
    public Sprite CrabSprite;

    [BoxGroup("玩家属性")]
    [LabelText("脱壳后移动速度")]
    public float NoShellSpeed;

    [BoxGroup("玩家属性")]
    [LabelText("带壳时移动速度")]
    public float ShellSpeed;

    //[BoxGroup("UI")]
    // [LabelText("吃分UI")]
    // private HUDText hudText;

    [HideInInspector] public int m_Score = 0; // 得分
    [HideInInspector] public int m_Level = 1; // 等级（重量）
    [HideInInspector] public bool isDead = false; // 是否死亡

    //private Collider2D m_collider;
    //private Animator m_Anim;
    private Rigidbody2D m_rigid;

    private void Start()
    {
        //m_collider = GetComponent<Collider2D>();
        //m_Anim = GetComponent<Animator>();
        m_rigid = GetComponent<Rigidbody2D>();
    }

    protected virtual void FixedUpdate()
    {
        //float x = Input.GetAxis("Horizontal");
        //float y = Input.GetAxis("Vertical");
        float speed = 50.0f;
        float x = 0, y = 0;

        if (Input.GetKey(KeyCode.W))
        {
            y = speed * Time.deltaTime;
        }
        else if (Input.GetKey(KeyCode.S))
        {
            y = -speed * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.A))
        {
            x = -speed * Time.deltaTime;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            x = speed * Time.deltaTime;
        }

        //transform.position += new Vector3(x, y, 0);
        m_rigid.velocity = new Vector3(x, y, 0);
    }

    protected void OnCollisionEnter2D(Collision2D collision)
    {
        switch (collision.gameObject.tag)
        {
            case Tag.Crab:

                break;

            case Tag.Stone:

                break;

            case Tag.Hole:

                break;

            case Tag.Nutrition:
                AudioSource.PlayClipAtPoint(AudioManager.AudioClipsDic["Coin"], transform.position);
                break;
        }
    }
}
