using Sirenix.OdinInspector;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Nutrition : MonoBehaviour
{
    [LabelText("营养值")]
    public int Nutri;

    //private void OnCollisionEnter2D(Collision2D collision)
    //{
    //    switch (collision.gameObject.tag)
    //    {
    //        case Tag.CrabA:
    //            collision.gameObject.GetComponent<CrabA>().Nutrition += Nutri;
    //            break;
    //        case Tag.CrabB:
    //            collision.gameObject.GetComponent<CrabB>().Nutrition += Nutri;
    //            break;
    //        case Tag.CrabC:
    //            collision.gameObject.GetComponent<CrabC>().Nutrition += Nutri;
    //            break;
    //        case Tag.CrabD:
    //            collision.gameObject.GetComponent<CrabD>().Nutrition += Nutri;
    //            break;
    //    }

    //    gameObject.SetActive(false);
    //    Destroy(gameObject, 0.2f);
    //}
}
