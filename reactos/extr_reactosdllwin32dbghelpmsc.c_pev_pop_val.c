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
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int BOOL ;

/* Variables and functions */
 int PEV_MAX_LEN ; 
 scalar_t__ pev_get_val (struct pevaluator*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ pev_pop (struct pevaluator*,char*) ; 

__attribute__((used)) static BOOL  pev_pop_val(struct pevaluator* pev, DWORD_PTR* val)
{
    char        p[PEV_MAX_LEN];

    return pev_pop(pev, p) && pev_get_val(pev, p, val);
}