using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Util
{
    public static Vector3 ComputeBornPoint(Vector3 original, float radius)
    {
        // TODO +-
        Vector3 randomRotation = Random.rotation.eulerAngles.normalized;
        Debug.Log(randomRotation);
        return new Vector3(original.x + randomRotation.x * radius, original.y + randomRotation.y * radius, 0);
    }
}
