#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ varno; scalar_t__ varattno; scalar_t__ vartype; } ;
typedef  TYPE_1__ Var ;

/* Variables and functions */

__attribute__((used)) static bool
var_equal(Var *v1, Var *v2)
{
	return v1->varno == v2->varno && v1->varattno == v2->varattno && v1->vartype == v2->vartype;
}