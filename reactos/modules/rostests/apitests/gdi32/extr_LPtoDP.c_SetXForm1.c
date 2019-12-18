#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eM11; int eM22; int eDx; int eDy; scalar_t__ eM21; scalar_t__ eM12; } ;
typedef  TYPE_1__ XFORM ;

/* Variables and functions */

__attribute__((used)) static void SetXForm1(XFORM *pxform)
{
    pxform->eM11 = 1;
    pxform->eM12 = 0;
    pxform->eM21 = 0;
    pxform->eM22 = 1;
    pxform->eDx = 314;
    pxform->eDy = -99;
}