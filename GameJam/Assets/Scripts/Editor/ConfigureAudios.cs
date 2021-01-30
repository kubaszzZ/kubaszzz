//using UnityEditor;
//using UnityEngine;

//public class ConfigureAudios : Editor
//{
//    private static AudioManager m_AudioManager;
//    private static AudioManager s_AudioManager
//    {
//        get
//        {
//            if (m_AudioManager == null)
//            {
//                m_AudioManager = Resources.Load<AudioManager>("AllAudios");
//            }
//            return m_AudioManager;
//        }
//    }

//    [MenuItem("Window/Audio/ConfigureAudios %e")]
//    public static void Configure()
//    {
//        Selection.activeObject = s_AudioManager;
//    }
//}
