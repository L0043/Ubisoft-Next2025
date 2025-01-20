#pragma once
#include "stdafx.h"
#include "App/app.h"
namespace 
{
    // take in start, end, colour, and thickness - thickness broken
    // created so I could add line thickness to the draw function but I realised I dont need this and have very limited time. :(
    void Draw(Vector2 start, Vector2 end, Vector4 colour)
    {
        // draw a line from start to end

        App::DrawLine(start.x, start.y, end.x, end.y, colour.x, colour.y, colour.z);
        // in this state, this will only work for left to right lines, I will try to fix this if I have time later.
        //if(thickness > 0)
        //{
        //    for (int i = 0; i < thickness / 2; i++)
        //    {
        //        App::DrawLine(start.x, start.y - i, end.x, end.y - i, colour.x, colour.y, colour.z);
        //    }
        //    for (int i = 0; i < thickness / 2; i++)
        //    {
        //        App::DrawLine(start.x, start.y + i, end.x, end.y + i, colour.x, colour.y, colour.z);
        //    }
        //}

    }
}