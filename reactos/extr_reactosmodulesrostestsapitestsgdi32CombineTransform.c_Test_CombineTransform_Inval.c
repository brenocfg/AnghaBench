#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  XFORM ;

/* Variables and functions */
 int /*<<< orphan*/  CombineTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_xform (int /*<<< orphan*/ ,float,float,float,float,double,double) ; 
 int /*<<< orphan*/  set_xform (int /*<<< orphan*/ *,double,float,float,double,double,double) ; 

void Test_CombineTransform_Inval(float eInval, float eOut)
{
    XFORM xform1, xform2, xform3;

    /* zero matrix / M11 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, 0.0, 0.0, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, 0.0, 0.0, 0.0); // -> M21
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, 0.0, 0.0, 0.0); // -> M12

    /* zero matrix / M12 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, eInval, 0.0, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, 0.0, eOut, 0.0, eOut, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, 0.0, 0.0, 0.0, 0.0);

    /* zero matrix / M21 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, 0.0, eInval, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, eOut, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, 0.0, 0.0, eOut, eOut, 0.0, 0.0);

    /* zero matrix / M22 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, 0.0, 0.0, eInval, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, 0.0, 0.0, 0.0, eOut, 0.0, 0.0); // -> M12
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, 0.0, 0.0, 0.0, eOut, 0.0, 0.0); // -> M21

    /* zero matrix / M11,M12 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, eInval, 0.0, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, 0.0, 0.0, 0.0, 0.0);

    /* zero matrix / M11,M21 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, 0.0, eInval, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, eOut, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);

    /* zero matrix / M11,M22 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, 0.0, 0.0, eInval, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, eOut, 0.0, 0.0); // -> M12, M21
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, eOut, 0.0, 0.0);

    /* zero matrix / M12,M21 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, eInval, eInval, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);
}