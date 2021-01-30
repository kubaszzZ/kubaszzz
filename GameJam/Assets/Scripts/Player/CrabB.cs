using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrabB : CrabMono
{
    private bool m_IsCrabACollision = false;
    private bool m_IsCrabCCollision = false;
    private bool m_IsCrabDCollision = false;

    [HideInInspector] public int CrabID = 2;

    protected override void FixedUpdate()
    {
        float x = 0, y = 0;

        if (Input.GetKey(KeyCode.UpArrow))
        {
            y = (ShellSpeed - HinderSpeed) * SpeedScale * Time.deltaTime;
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            y = -(ShellSpeed - HinderSpeed) * SpeedScale * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.LeftArrow))
        {
            x = -(ShellSpeed - HinderSpeed) * SpeedScale * Time.deltaTime;
        }
        else if (Input.GetKey(KeyCode.RightArrow))
        {
            x = (ShellSpeed - HinderSpeed) * SpeedScale * Time.deltaTime;
        }

        m_rigid.velocity = new Vector2(x, y);
        Debug.Log(m_rigid.velocity);
    }

    protected override void OnCollisionEnter2D(Collision2D collision)
    {
        base.OnCollisionEnter2D(collision);
        switch (collision.gameObject.tag)
        {
            case Tag.CrabA:
                if (!m_IsCrabACollision)
                {
                    HinderSpeed += DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabA>().Level - 1) * 5 + Level - 1];
                    m_IsCrabACollision = true;
                }
                break;

            case Tag.CrabC:
                if (!m_IsCrabCCollision)
                {
                    HinderSpeed += DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabC>().Level - 1) * 5 + Level - 1];
                    m_IsCrabCCollision = true;
                }
                break;

            case Tag.CrabD:
                if (!m_IsCrabDCollision)
                {
                    HinderSpeed += DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabD>().Level - 1) * 5 + Level - 1];
                    m_IsCrabDCollision = true;
                }
                break;
        }
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        switch (collision.gameObject.tag)
        {
            case Tag.CrabA:
                if (m_IsCrabACollision)
                {
                    HinderSpeed -= DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabA>().Level - 1) * 5 + Level - 1];
                    m_IsCrabACollision = false;
                }
                break;

            case Tag.CrabC:
                if (m_IsCrabCCollision)
                {
                    HinderSpeed -= DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabC>().Level - 1) * 5 + Level - 1];
                    m_IsCrabCCollision = false;
                }
                break;

            case Tag.CrabD:
                if (m_IsCrabDCollision)
                {
                    HinderSpeed -= DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabD>().Level - 1) * 5 + Level - 1];
                    m_IsCrabDCollision = false;
                }
                break;
        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        switch (collision.gameObject.tag)
        {
            case Tag.CrabA:
                if (m_IsCrabACollision)
                {
                    HinderSpeed -= DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabA>().Level - 1) * 5 + Level - 1];
                    m_IsCrabACollision = false;
                }
                break;

            case Tag.CrabC:
                if (m_IsCrabCCollision)
                {
                    HinderSpeed -= DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabC>().Level - 1) * 5 + Level - 1];
                    m_IsCrabCCollision = false;
                }
                break;

            case Tag.CrabD:
                if (m_IsCrabDCollision)
                {
                    HinderSpeed -= DataManager.Instance.HinderSpeed[(collision.gameObject.GetComponent<CrabD>().Level - 1) * 5 + Level - 1];
                    m_IsCrabDCollision = false;
                }
                break;
        }
    }
}
