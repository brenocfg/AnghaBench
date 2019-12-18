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
struct TYPE_3__ {scalar_t__* FunctionTypes; scalar_t__ nFunctions; } ;
typedef  TYPE_1__ _cmsParametricCurvesCollection ;

/* Variables and functions */
 scalar_t__ abs (int) ; 

__attribute__((used)) static
int IsInSet(int Type, _cmsParametricCurvesCollection* c)
{
    int i;

    for (i=0; i < (int) c ->nFunctions; i++)
        if (abs(Type) == c ->FunctionTypes[i]) return i;

    return -1;
}