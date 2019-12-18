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
struct TYPE_5__ {int* n; } ;
typedef  TYPE_1__ cmsVEC3 ;
struct TYPE_6__ {int r; void* theta; void* alpha; } ;
typedef  TYPE_2__ cmsSpherical ;
typedef  int cmsFloat64Number ;

/* Variables and functions */
 size_t VX ; 
 size_t VY ; 
 size_t VZ ; 
 void* _cmsAtan2 (int,int) ; 
 int sqrt (int) ; 

__attribute__((used)) static
void ToSpherical(cmsSpherical* sp, const cmsVEC3* v)
{

    cmsFloat64Number L, a, b;

    L = v ->n[VX];
    a = v ->n[VY];
    b = v ->n[VZ];

    sp ->r = sqrt( L*L + a*a + b*b );

   if (sp ->r == 0) {
        sp ->alpha = sp ->theta = 0;
        return;
    }

    sp ->alpha = _cmsAtan2(a, b);
    sp ->theta = _cmsAtan2(sqrt(a*a + b*b), L);
}