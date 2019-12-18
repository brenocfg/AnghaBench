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
struct TYPE_3__ {size_t* Domain; scalar_t__ Table; } ;
typedef  TYPE_1__ cmsInterpParams ;
typedef  double cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ floor (double) ; 

__attribute__((used)) static
void Fake1Dfloat(cmsContext ContextID, const cmsFloat32Number Value[],
                    cmsFloat32Number Output[],
                    const cmsInterpParams* p)
{
       cmsFloat32Number val2;
       int cell;
       const cmsFloat32Number* LutTable = (const cmsFloat32Number*) p ->Table;

       // Clip upper values
       if (Value[0] >= 1.0) {
           Output[0] = LutTable[p -> Domain[0]];
           return;
       }

       val2 = p -> Domain[0] * Value[0];
       cell = (int) floor(val2);
       Output[0] =  LutTable[cell] ;
}