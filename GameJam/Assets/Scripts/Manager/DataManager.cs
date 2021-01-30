using Sirenix.OdinInspector;
using System;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu]
[Serializable]
public class DataManager : ScriptableObject
{
    [SerializeField]
    [LabelText("最大营养数")]
    private List<int> m_MaxNutrition;
    public List<int> MaxNutrition
    {
        get
        {
            if (m_MaxNutrition == null)
            {
                m_MaxNutrition = new List<int>();
            }
            return m_MaxNutrition;
        }
    }

    [SerializeField]
    [LabelText("无壳移动速度")]
    private List<float> m_NoShellSpeed;
    public List<float> NoShellSpeed
    {
        get
        {
            if (m_NoShellSpeed == null)
            {
                m_NoShellSpeed = new List<float>();
            }
            return m_NoShellSpeed;
        }
    }

    [SerializeField]
    [LabelText("跳坑获得分数")]
    private List<int> m_Score;
    public List<int> Score
    {
        get
        {
            if (m_Score == null)
            {
                m_Score = new List<int>();
            }
            return m_Score;
        }
    }

    [SerializeField]
    [LabelText("推动速度")]
    private List<float> m_HinderSpeed;
    public List<float> HinderSpeed
    {
        get
        {
            if (m_HinderSpeed == null)
            {
                m_HinderSpeed = new List<float>();
            }
            return m_HinderSpeed;
        }
    }

    private static DataManager m_Instance;
    public static DataManager Instance
    {
        get
        {
            DataManager manager = Resources.Load<DataManager>("AllDatas");
            if (manager != null)
            {
                m_Instance = manager;
            }
            return m_Instance;
        }
    }
}
