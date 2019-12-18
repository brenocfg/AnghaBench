#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsFloat64Number ;
struct TYPE_4__ {int* XYZ; } ;
struct TYPE_5__ {int Yb; TYPE_1__ adoptedWhite; } ;
typedef  TYPE_2__ cmsCIECAM02 ;

/* Variables and functions */

__attribute__((used)) static
cmsFloat64Number compute_n(cmsCIECAM02* pMod)
{
    return (pMod -> Yb / pMod -> adoptedWhite.XYZ[1]);
}