using System.Collections.Generic;
using UnityEngine;

//public enum AudioType {
//    GET_NUTRITION,
//    GET_VICTORY
//}

//[CreateAssetMenu]
//[Serializable]
public class AudioManager// : ScriptableObject
{
    //[Serializable]
    //public struct AudioElement
    //{
    //    public AudioType AudioType;
    //    public AudioClip AudioClip;
    //}

    //[SerializeField]
    //private List<AudioElement> m_AudioClips;
    //public List<AudioElement> AudioClips
    //{
    //    get
    //    {
    //        if (m_AudioClips == null)
    //        {
    //            m_AudioClips = new List<AudioElement>();
    //        }
    //        return m_AudioClips;
    //    }
    //}

    private static Dictionary<string, AudioClip> m_AudioClipsDic;
    public static Dictionary<string, AudioClip> AudioClipsDic
    {
        get
        {
            if (m_AudioClipsDic == null)
            {
                m_AudioClipsDic = new Dictionary<string, AudioClip>();
                AudioClip[] clips = Resources.LoadAll<AudioClip>("Audio");
                for (int i = 0; i < clips.Length; ++i)
                {
                    m_AudioClipsDic.Add(clips[i].name, clips[i]);
                    Debug.Log(clips[i].name);
                }
            }
            return m_AudioClipsDic;
        }
    }
}
