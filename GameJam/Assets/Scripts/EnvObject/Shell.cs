using Sirenix.OdinInspector;
using UnityEngine;

public class Shell : MonoBehaviour
{
    [LabelText("壳等级")]
    public string Level;

    [LabelText("移动速度")]
    public string MoveSpeed;

    [LabelText("最大养分值")]
    public int Nutrition;

    [LabelText("跳坑获得分数")]
    public int Score;
}
