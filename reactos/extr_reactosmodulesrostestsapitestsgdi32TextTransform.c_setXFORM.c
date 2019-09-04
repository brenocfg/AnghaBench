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
struct TYPE_3__ {void* eDy; void* eDx; void* eM22; void* eM21; void* eM12; void* eM11; } ;
typedef  TYPE_1__ XFORM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  void* FLOAT ;

/* Variables and functions */

__attribute__((used)) static VOID
setXFORM(XFORM *pxform,
         FLOAT eM11, FLOAT eM12,
         FLOAT eM21, FLOAT eM22,
         FLOAT eDx, FLOAT eDy)
{
    pxform->eM11 = eM11;
    pxform->eM12 = eM12;
    pxform->eM21 = eM21;
    pxform->eM22 = eM22;
    pxform->eDx = eDx;
    pxform->eDy = eDy;
}