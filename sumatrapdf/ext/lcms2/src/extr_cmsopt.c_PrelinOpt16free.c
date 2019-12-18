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
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {struct TYPE_3__* ParamsCurveOut16; struct TYPE_3__* EvalCurveOut16; } ;
typedef  TYPE_1__ Prelin16Data ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
void PrelinOpt16free(cmsContext ContextID, void* ptr)
{
    Prelin16Data* p16 = (Prelin16Data*) ptr;

    _cmsFree(ContextID, p16 ->EvalCurveOut16);
    _cmsFree(ContextID, p16 ->ParamsCurveOut16);

    _cmsFree(ContextID, p16);
}