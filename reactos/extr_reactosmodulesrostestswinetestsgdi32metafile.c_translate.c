#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int eM11; int eM21; int eM12; int eM22; scalar_t__ eDy; scalar_t__ eDx; } ;
typedef  TYPE_1__ XFORM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {void* y; void* x; } ;
typedef  TYPE_2__ POINT ;
typedef  void* LONG ;
typedef  int FLOAT ;

/* Variables and functions */
 scalar_t__ floor (scalar_t__) ; 

__attribute__((used)) static void translate( POINT *pt, UINT count, const XFORM *xform )
{
    while (count--)
    {
        FLOAT x = (FLOAT)pt->x;
        FLOAT y = (FLOAT)pt->y;
        pt->x = (LONG)floor( x * xform->eM11 + y * xform->eM21 + xform->eDx + 0.5 );
        pt->y = (LONG)floor( x * xform->eM12 + y * xform->eM22 + xform->eDy + 0.5 );
        pt++;
    }
}