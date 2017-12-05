using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonUI : BaseUI {
    public Anchor anchor;
    public Rect shape;
    public bool isVisible;
    public string text;
    private Rect oldShape;
    private Anchor oldAnchor;

    // Use this for initialization
    void Start () {
        oldAnchor = anchor;
        oldShape = shape;
        SetPosition(shape.x, shape.y);
        SetSize(shape.width, shape.height);
        SetAnchor(anchor);
	}

    private void OnGUI()
    {
        if (VIsVisible()){
            if (GUI.Button(new Rect(GetPosX(), GetPosY(), GetWidth(), GetHeight()),text)){
                Debug.Log("Button pressed!");
            }
        }
    }

    public void ReDraw()
    {
        oldAnchor = anchor;
        oldShape = shape;
        SetPosition(shape.x, shape.y);
        SetSize(shape.width, shape.height);
        SetAnchor(anchor);
    }

    // Update is called once per frame
    void Update () {
        if (oldAnchor != anchor || oldShape != shape){
            ReDraw();
        }
        else{
            oldAnchor = anchor;
            oldShape = shape;
        }

        // If screen resolution changes
        if (Screen.height != screenSize.y ||
            Screen.width != screenSize.x)
        {
            Debug.Log("Resizing");
            // Scale the object to match
            ScaleObject(new Vector2(Screen.width / screenSize.x,
                Screen.height / screenSize.y));
            // Do that thing
            //ReDraw();
            // that I like so much
            screenSize = new Vector2(Screen.width, Screen.height);
        }

        VSetVisible(isVisible);
    }
}
