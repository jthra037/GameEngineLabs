using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DialogueUI : BaseUI {
    public Anchor anchor;
    public Rect shape;
    public Rect button1Shape;
    public Rect button2Shape;
    public bool isVisible;
    private Rect oldShape;
    private Anchor oldAnchor;

    private string text = "Hello Dolly";

    private GameObject buttonObject1;
    private GameObject buttonObject2;
    private ButtonUI button1;
    private ButtonUI button2;

    // Use this for initialization
    void Start()
    {
        oldAnchor = anchor;
        oldShape = shape;
        SetPosition(shape.x, shape.y);
        SetSize(shape.width, shape.height);
        SetAnchor(anchor);

        InitButtons();
    }

    void InitButtons()
    {
        buttonObject1 = new GameObject();
        buttonObject2 = new GameObject();

        buttonObject1.transform.parent = transform;
        buttonObject2.transform.parent = transform;

        buttonObject1.AddComponent<SpriteRenderer>();
        buttonObject1.AddComponent<ButtonUI>();
        buttonObject2.AddComponent<SpriteRenderer>();
        buttonObject2.AddComponent<ButtonUI>();

        button1 = buttonObject1.GetComponent<ButtonUI>();
        button2 = buttonObject2.GetComponent<ButtonUI>();

        button1.isVisible = true;
        button2.isVisible = true;

        button1.VSetZOrder(1);
        button2.VSetZOrder(1);

        SetRelButtonPos();

        button1.text = "Fuck you";
        button2.text = "Marks kneecap";
    }

    public void ReDraw()
    {
        oldAnchor = anchor;
        oldShape = shape;
        SetPosition(shape.x, shape.y);
        SetSize(shape.width, shape.height);
        SetAnchor(anchor);
    }

    private void OnGUI()
    {
        if (VIsVisible())
        {
            //GUI.Button(new Rect(GetPosX(), GetPosY(), GetWidth(), GetHeight()), "");
            GUI.Box(new Rect(GetPosX(), GetPosY(), GetWidth(), GetHeight()), text);
        }
    }

    private void SetRelButtonPos()
    {
        button1.shape.Set(m_PosX + button1Shape.x, m_PosY + button1Shape.y,
            button1Shape.width, button1Shape.height);

        button2.shape.Set(m_PosX + button2Shape.x, m_PosY + button2Shape.y,
            button2Shape.width, button2Shape.height);
    }

    // Update is called once per frame
    void Update()
    {
        if (oldAnchor != anchor || oldShape != shape)
        {
            ReDraw();
            SetRelButtonPos();
            button1.ReDraw();
            button2.ReDraw();
        }
        else
        {
            oldAnchor = anchor;
            oldShape = shape;
        }

        // If screen resolution changes
        if (Screen.height != screenSize.y ||
            Screen.width != screenSize.x)
        {
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
