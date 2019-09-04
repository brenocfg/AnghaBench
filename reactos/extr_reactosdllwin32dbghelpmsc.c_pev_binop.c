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
struct pevaluator {int dummy; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PEV_ERROR1 (struct pevaluator*,char*,char) ; 
 int PEV_MAX_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pev_pop_val (struct pevaluator*,int*) ; 
 int /*<<< orphan*/  pev_push (struct pevaluator*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static BOOL  pev_binop(struct pevaluator* pev, char op)
{
    char        res[PEV_MAX_LEN];
    DWORD_PTR   v1, v2, c;

    if (!pev_pop_val(pev, &v1) || !pev_pop_val(pev, &v2)) return FALSE;
    switch (op)
    {
    case '+': c = v1 + v2; break;
    case '-': c = v1 - v2; break;
    case '*': c = v1 * v2; break;
    case '/': c = v1 / v2; break;
    case '%': c = v1 % v2; break;
    default: return PEV_ERROR1(pev, "binop: unknown op (%c)", op);
    }
    snprintf(res, sizeof(res), "%ld", c);
    pev_push(pev, res);
    return TRUE;
}