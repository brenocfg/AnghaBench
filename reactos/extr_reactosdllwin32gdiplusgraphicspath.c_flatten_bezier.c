#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double X; double Y; } ;
struct TYPE_7__ {TYPE_2__ pt; } ;
typedef  TYPE_1__ path_list_node_t ;
typedef  double REAL ;
typedef  TYPE_2__ GpPointF ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  PathPointTypeLine ; 
 void* TRUE ; 
 TYPE_1__* add_path_list_node (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 double fabs (int) ; 
 scalar_t__ powf (int,double) ; 
 double sqrtf (scalar_t__) ; 

__attribute__((used)) static BOOL flatten_bezier(path_list_node_t *start, REAL x2, REAL y2, REAL x3, REAL y3,
                           path_list_node_t *end, REAL flatness)
{
    /* this 5 middle points with start/end define to half-curves */
    GpPointF mp[5];
    GpPointF pt, pt_st;
    path_list_node_t *node;

    /* calculate bezier curve middle points == new control points */
    mp[0].X = (start->pt.X + x2) / 2.0;
    mp[0].Y = (start->pt.Y + y2) / 2.0;
    /* middle point between control points */
    pt.X = (x2 + x3) / 2.0;
    pt.Y = (y2 + y3) / 2.0;
    mp[1].X = (mp[0].X + pt.X) / 2.0;
    mp[1].Y = (mp[0].Y + pt.Y) / 2.0;
    mp[4].X = (end->pt.X + x3) / 2.0;
    mp[4].Y = (end->pt.Y + y3) / 2.0;
    mp[3].X = (mp[4].X + pt.X) / 2.0;
    mp[3].Y = (mp[4].Y + pt.Y) / 2.0;

    mp[2].X = (mp[1].X + mp[3].X) / 2.0;
    mp[2].Y = (mp[1].Y + mp[3].Y) / 2.0;

    if ((x2 == mp[0].X && y2 == mp[0].Y && x3 == mp[1].X && y3 == mp[1].Y) ||
        (x2 == mp[3].X && y2 == mp[3].Y && x3 == mp[4].X && y3 == mp[4].Y))
        return TRUE;

    pt = end->pt;
    pt_st = start->pt;
    /* check flatness as a half of distance between middle point and a linearized path */
    if(fabs(((pt.Y - pt_st.Y)*mp[2].X + (pt_st.X - pt.X)*mp[2].Y +
        (pt_st.Y*pt.X - pt_st.X*pt.Y))) <=
        (0.5 * flatness*sqrtf((powf(pt.Y - pt_st.Y, 2.0) + powf(pt_st.X - pt.X, 2.0))))){
        return TRUE;
    }
    else
        /* add a middle point */
        if(!(node = add_path_list_node(start, mp[2].X, mp[2].Y, PathPointTypeLine)))
            return FALSE;

    /* do the same with halves */
    flatten_bezier(start, mp[0].X, mp[0].Y, mp[1].X, mp[1].Y, node, flatness);
    flatten_bezier(node,  mp[3].X, mp[3].Y, mp[4].X, mp[4].Y, end,  flatness);

    return TRUE;
}