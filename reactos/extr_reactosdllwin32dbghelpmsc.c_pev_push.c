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
struct pevaluator {scalar_t__ stk_index; int /*<<< orphan*/  pool; int /*<<< orphan*/  stack; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PEV_ERROR (struct pevaluator*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 char* pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 char** vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** vector_at (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vector_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL  pev_push(struct pevaluator* pev, const char* elt)
{
    char**      at;
    if (pev->stk_index < vector_length(&pev->stack))
        at = vector_at(&pev->stack, pev->stk_index);
    else
        at = vector_add(&pev->stack, &pev->pool);
    if (!at) return PEV_ERROR(pev, "push: out of memory");
    *at = pool_strdup(&pev->pool, elt);
    pev->stk_index++;
    return TRUE;
}