using Sirenix.OdinInspector;
using UnityEngine;

public class Shell : MonoBehaviour
{
    //[LabelText("壳等级")]
    [HideInInspector] public int Level = 1;

    public void CollisionEnter2D(Collision2D collision)
    {
        switch (collision.gameObject.tag)
        {
            case Tag.CrabA:
                if (Level >= collision.gameObject.GetComponent<CrabA>().Level)
                {
                    if (Input.GetKeyDown(KeyCode.J))
                    {
                        // TODO 判断能否拾取
                        //if ()
                        {
                            collision.gameObject.GetComponent<CrabA>().Level = Level;
                        }
                        // TODO 交换壳的动画
                        //GameObject go = collision.gameObject.transform.GetChild(0).gameObject;
                        //go.GetComponent<SpriteRenderer>().sprite = Sprite;
                        //go.transform.position = transform.parent.transform.position;
                    }
                }
                break;
            case Tag.CrabB:
                if (Level >= collision.gameObject.GetComponent<CrabB>().Level)
                {
                    if (Input.GetKeyDown(KeyCode.KeypadEnter))
                    {
                        // TODO 判断能否拾取
                        //if ()
                        {
                            collision.gameObject.GetComponent<CrabA>().Level = Level;
                        }
                        // TODO 交换壳的动画
                        //GameObject go = collision.gameObject.transform.GetChild(0).gameObject;
                        //go.GetComponent<SpriteRenderer>().sprite = Sprite;
                        //go.transform.position = transform.parent.transform.position;
                    }
                }
                break;
            case Tag.CrabC:
                if (Level >= collision.gameObject.GetComponent<CrabC>().Level)
                {
                    if (Input.GetKeyDown(KeyCode.J))
                    {
                        // 交换壳的动画
                        gameObject.GetComponent<CrabC>().Level = Level;
                    }
                }
                break;
            case Tag.CrabD:
                if (Level >= collision.gameObject.GetComponent<CrabD>().Level)
                {
                    if (Input.GetKeyDown(KeyCode.J))
                    {
                        // 交换壳的动画
                        gameObject.GetComponent<CrabD>().Level = Level;
                    }
                }
                break;
        }
    }
}
