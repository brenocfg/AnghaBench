#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsVEC3 ;
struct TYPE_7__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_1__ cmsMAT3 ;
typedef  int cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_8__ {int X; int Y; int Z; } ;
typedef  TYPE_2__ cmsCIEXYZ ;
struct TYPE_9__ {int X; int Y; int Z; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsVEC3init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 TYPE_3__* cmsD50_XYZ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void ComputeBlackPointCompensation(cmsContext ContextID, const cmsCIEXYZ* BlackPointIn,
                                   const cmsCIEXYZ* BlackPointOut,
                                   cmsMAT3* m, cmsVEC3* off)
{
  cmsFloat64Number ax, ay, az, bx, by, bz, tx, ty, tz;

   // Now we need to compute a matrix plus an offset m and of such of
   // [m]*bpin + off = bpout
   // [m]*D50  + off = D50
   //
   // This is a linear scaling in the form ax+b, where
   // a = (bpout - D50) / (bpin - D50)
   // b = - D50* (bpout - bpin) / (bpin - D50)

   tx = BlackPointIn->X - cmsD50_XYZ(ContextID)->X;
   ty = BlackPointIn->Y - cmsD50_XYZ(ContextID)->Y;
   tz = BlackPointIn->Z - cmsD50_XYZ(ContextID)->Z;

   ax = (BlackPointOut->X - cmsD50_XYZ(ContextID)->X) / tx;
   ay = (BlackPointOut->Y - cmsD50_XYZ(ContextID)->Y) / ty;
   az = (BlackPointOut->Z - cmsD50_XYZ(ContextID)->Z) / tz;

   bx = - cmsD50_XYZ(ContextID)-> X * (BlackPointOut->X - BlackPointIn->X) / tx;
   by = - cmsD50_XYZ(ContextID)-> Y * (BlackPointOut->Y - BlackPointIn->Y) / ty;
   bz = - cmsD50_XYZ(ContextID)-> Z * (BlackPointOut->Z - BlackPointIn->Z) / tz;

   _cmsVEC3init(ContextID, &m ->v[0], ax, 0,  0);
   _cmsVEC3init(ContextID, &m ->v[1], 0, ay,  0);
   _cmsVEC3init(ContextID, &m ->v[2], 0,  0,  az);
   _cmsVEC3init(ContextID, off, bx, by, bz);

}