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
struct TYPE_3__ {scalar_t__ Eval16Fn; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  int cmsBool ;

/* Variables and functions */
 scalar_t__ FastIdentity16 ; 

cmsBool _cmsLutIsIdentity(cmsPipeline *PtrLut)
{
    return !PtrLut || PtrLut->Eval16Fn == FastIdentity16;
}