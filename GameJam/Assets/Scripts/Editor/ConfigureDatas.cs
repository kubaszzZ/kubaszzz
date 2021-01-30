using UnityEditor;
using UnityEngine;

public class ConfigureDatas : Editor
{
    [MenuItem("Window/DataManager %e")]
    public static void Configure()
    {
        Selection.activeObject = DataManager.Instance;
    }
}
