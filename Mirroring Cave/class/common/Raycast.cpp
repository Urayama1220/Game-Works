#include "Raycast.h"
#include <DxLib.h>
#include "../../_debug/_DebugDispOut.h"
bool Raycast::CheckCollision(Ray ray, Collision col)
{
    bool result = false;
    Line    points[4] =
    {
        {
        col.first,
        col.first + Vector2Dbl{col.second.x,0},//ã
        },
        {

         col.first + Vector2Dbl{col.second.x,0},
        col.first + col.second,//‰E
        },

         
        {
        col.first + col.second,
        col.first + Vector2Dbl{0,col.second.y},//‰E
        },

        {
        col.first + Vector2Dbl{0,col.second.y} ,
        col.first//¶
        }

       
    };
    for (auto point : points)
    {
        //_dbgDrawLine(point.p.x, point.p.y, point.end.x, point.end.y,0x00ffff);
        result |= CheckRay(ray, point);
    }
    
    return result;
}

bool Raycast::CheckRay(Ray ray, Line line)
{
    //ray‚ğL‚Î‚µ‹——£ Œğ·”»’è
    auto checkcross = [](Vector2Dbl& vac1, Vector2Dbl& vac2) {
        return((vac1.x *vac2.y) - (vac2.x * vac1.y));
    };

    Vector2Dbl& vecRay = ray.vec;
  /*  Vector2 pv = Vector2{ line.p.x - ray.p.x,line.p.y - ray.p.y };
    Vector2 ev = Vector2{ line.end.x - ray.p.x,line.end.y - ray.p.y };*/
    Vector2Dbl&& vecLine = line.end - line.p;
   /* Vector2 plv = Vector2{ ray.p.x - line.p.x, ray.p.y -line.p.y };
    Vector2 plv = Vector2{ ray.p.x - line.p.x, ray.p.y - line.p.y };*/

    auto cross_RayLine = checkcross(vecRay, vecLine);
    if (cross_RayLine == 0.0f)
    {
        return false;
    }
    Vector2Dbl v = line.p - ray.p;
    auto cros_ray = checkcross(v, vecRay);
    auto cros_line = checkcross(v, vecLine);
  /*  auto cros_ray = checkcross(pv, vecRay);
    auto cros_line = checkcross(ev, vecLine);*/

    auto ans1 = cros_ray / cross_RayLine;
    auto ans2 = cros_line / cross_RayLine;

    if (ans1 > 0.0f && ans1 <= 1.0f &&
        ans2 > 0.0f && ans2 <= 1.0f)
    {
        return true;
    }

    //const float eps = 0.00001f;
    //if (ans1 + eps < 0 || ans1- eps > 1 || ans2+ eps < 0 || ans2- eps > 1) {
    //    // Œğ·‚µ‚Ä‚¢‚È‚¢
    //    return false;
    //}


   /* auto chk1 = (ray.vec.x) * (line.p.y - ray.p.y) + (ray.vec.y) * (ray.p.x-line.p.x);
    auto chk2 = (ray.vec.x) * (line.end.y - ray.p.y) + (ray.vec.y) * (ray.p.x - line.end.x);*/

   
   /* if (chk1 * chk2<0|| chk1 ==0|| chk2 ==0)
    {
        return true;
    }*/
    return false;
}
