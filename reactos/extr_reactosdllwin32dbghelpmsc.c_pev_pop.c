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
struct pevaluator {int /*<<< orphan*/  stk_index; int /*<<< orphan*/  stack; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PEV_ERROR (struct pevaluator*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char** vector_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL  pev_pop(struct pevaluator* pev, char* elt)
{
    char**      at = vector_at(&pev->stack, --pev->stk_index);
    if (!at) return PEV_ERROR(pev, "pop: stack empty");
    strcpy(elt, *at);
    return TRUE;
}