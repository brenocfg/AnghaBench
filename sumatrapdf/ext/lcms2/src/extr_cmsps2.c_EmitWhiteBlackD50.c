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
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_4__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ cmsCIEXYZ ;
struct TYPE_5__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cmsD50_XYZ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void EmitWhiteBlackD50(cmsContext ContextID, cmsIOHANDLER* m, cmsCIEXYZ* BlackPoint)
{

    _cmsIOPrintf(ContextID, m, "/BlackPoint [%f %f %f]\n", BlackPoint -> X,
                                          BlackPoint -> Y,
                                          BlackPoint -> Z);

    _cmsIOPrintf(ContextID, m, "/WhitePoint [%f %f %f]\n", cmsD50_XYZ(ContextID)->X,
                                          cmsD50_XYZ(ContextID)->Y,
                                          cmsD50_XYZ(ContextID)->Z);
}