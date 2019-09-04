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
typedef  float D3DVALUE ;
typedef  float D3DCOLOR ;

/* Variables and functions */
 float D3DRMColorGetAlpha (float) ; 
 float D3DRMColorGetBlue (float) ; 
 float D3DRMColorGetGreen (float) ; 
 float D3DRMColorGetRed (float) ; 
 float D3DRMCreateColorRGB (float,float,float) ; 
 float D3DRMCreateColorRGBA (float,float,float,float) ; 
 scalar_t__ admit_error ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  ok (int,char*,float,float) ; 

__attribute__((used)) static void ColorTest(void)
{
    D3DCOLOR color, expected_color, got_color;
    D3DVALUE expected, got, red, green, blue, alpha;

/*___________D3DRMCreateColorRGB_________________________*/
    red=0.8f;
    green=0.3f;
    blue=0.55f;
    expected_color=0xffcc4c8c;
    got_color=D3DRMCreateColorRGB(red,green,blue);
    ok((expected_color==got_color),"Expected color=%x, Got color=%x\n",expected_color,got_color);

/*___________D3DRMCreateColorRGBA________________________*/
    red=0.1f;
    green=0.4f;
    blue=0.7f;
    alpha=0.58f;
    expected_color=0x931966b2;
    got_color=D3DRMCreateColorRGBA(red,green,blue,alpha);
    ok((expected_color==got_color),"Expected color=%x, Got color=%x\n",expected_color,got_color);

/* if a component is <0 then, then one considers this component as 0. The following test proves this fact (test only with the red component). */
    red=-0.88f;
    green=0.4f;
    blue=0.6f;
    alpha=0.41f;
    expected_color=0x68006699;
    got_color=D3DRMCreateColorRGBA(red,green,blue,alpha);
    ok((expected_color==got_color),"Expected color=%x, Got color=%x\n",expected_color,got_color);

/* if a component is >1 then, then one considers this component as 1. The following test proves this fact (test only with the red component). */
    red=2.37f;
    green=0.4f;
    blue=0.6f;
    alpha=0.41f;
    expected_color=0x68ff6699;
    got_color=D3DRMCreateColorRGBA(red,green,blue,alpha);
    ok((expected_color==got_color),"Expected color=%x, Got color=%x\n",expected_color,got_color);

/*___________D3DRMColorGetAlpha_________________________*/
    color=0x0e4921bf;
    expected=14.0f/255.0f;
    got=D3DRMColorGetAlpha(color);
    ok((fabs(expected-got)<admit_error),"Expected=%f, Got=%f\n",expected,got);

/*___________D3DRMColorGetBlue__________________________*/
    color=0xc82a1455;
    expected=1.0f/3.0f;
    got=D3DRMColorGetBlue(color);
    ok((fabs(expected-got)<admit_error),"Expected=%f, Got=%f\n",expected,got);

/*___________D3DRMColorGetGreen_________________________*/
    color=0xad971203;
    expected=6.0f/85.0f;
    got=D3DRMColorGetGreen(color);
    ok((fabs(expected-got)<admit_error),"Expected=%f, Got=%f\n",expected,got);

/*___________D3DRMColorGetRed__________________________*/
    color=0xb62d7a1c;
    expected=3.0f/17.0f;
    got=D3DRMColorGetRed(color);
    ok((fabs(expected-got)<admit_error),"Expected=%f, Got=%f\n",expected,got);
}