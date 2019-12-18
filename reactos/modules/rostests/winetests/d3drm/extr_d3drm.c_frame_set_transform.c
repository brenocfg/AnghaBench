#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float member_0; float member_1; float member_2; float member_3; } ;
struct TYPE_9__ {float member_0; float member_1; float member_2; float member_3; } ;
struct TYPE_8__ {float member_0; float member_1; float member_2; float member_3; } ;
struct TYPE_7__ {float member_0; float member_1; float member_2; float member_3; } ;
struct TYPE_11__ {TYPE_4__ member_3; TYPE_3__ member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  IDirect3DRMFrame ;
typedef  TYPE_5__ D3DRMMATRIX4D ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRMCOMBINE_REPLACE ; 
 int /*<<< orphan*/  IDirect3DRMFrame_AddTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__) ; 

__attribute__((used)) static void frame_set_transform(IDirect3DRMFrame *frame,
        float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    D3DRMMATRIX4D matrix =
    {
        {m11, m12, m13, m14},
        {m21, m22, m23, m24},
        {m31, m32, m33, m34},
        {m41, m42, m43, m44},
    };

    IDirect3DRMFrame_AddTransform(frame, D3DRMCOMBINE_REPLACE, matrix);
}