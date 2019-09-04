#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct d3dx_preshader {int /*<<< orphan*/  inputs; int /*<<< orphan*/  regs; int /*<<< orphan*/  ins; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dx_free_const_tab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regstore_free_tables (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3dx_free_preshader(struct d3dx_preshader *pres)
{
    HeapFree(GetProcessHeap(), 0, pres->ins);

    regstore_free_tables(&pres->regs);
    d3dx_free_const_tab(&pres->inputs);
}