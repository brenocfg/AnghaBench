#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
struct TYPE_6__ {scalar_t__ Type; } ;
typedef  TYPE_1__ cmsGDBPoint ;
struct TYPE_7__ {TYPE_1__** Gamut; } ;
typedef  TYPE_2__ cmsGDB ;
struct TYPE_8__ {int AdvX; int AdvY; } ;

/* Variables and functions */
 scalar_t__ GP_EMPTY ; 
 size_t NSTEPS ; 
 int SECTORS ; 
 TYPE_3__* Spiral ; 

__attribute__((used)) static
int FindNearSectors(cmsGDB* gbd, int alpha, int theta, cmsGDBPoint* Close[])
{
    int nSectors = 0;
    int a, t;
    cmsUInt32Number i;
    cmsGDBPoint* pt;

    for (i=0; i < NSTEPS; i++) {

        a = alpha + Spiral[i].AdvX;
        t = theta + Spiral[i].AdvY;

        // Cycle at the end
        a %= SECTORS;
        t %= SECTORS;

        // Cycle at the begin
        if (a < 0) a = SECTORS + a;
        if (t < 0) t = SECTORS + t;

        pt = &gbd ->Gamut[t][a];

        if (pt -> Type != GP_EMPTY) {

            Close[nSectors++] = pt;
        }
    }

    return nSectors;
}