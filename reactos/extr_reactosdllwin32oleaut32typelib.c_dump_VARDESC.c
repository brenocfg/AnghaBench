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
struct TYPE_4__ {int /*<<< orphan*/  oInst; } ;
struct TYPE_5__ {int /*<<< orphan*/  varkind; int /*<<< orphan*/  wVarFlags; int /*<<< orphan*/  elemdescVar; TYPE_1__ u; int /*<<< orphan*/  lpstrSchema; int /*<<< orphan*/  memid; } ;
typedef  TYPE_2__ VARDESC ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ELEMDESC (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dump_VARDESC(const VARDESC *v)
{
    MESSAGE("memid %d\n",v->memid);
    MESSAGE("lpstrSchema %s\n",debugstr_w(v->lpstrSchema));
    MESSAGE("oInst %d\n",v->u.oInst);
    dump_ELEMDESC(&(v->elemdescVar));
    MESSAGE("wVarFlags %x\n",v->wVarFlags);
    MESSAGE("varkind %d\n",v->varkind);
}