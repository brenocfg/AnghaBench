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
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_5__ {int sizek; int sizeupvalues; int sizep; int sizelocvars; TYPE_1__* locvars; scalar_t__* p; scalar_t__* upvalues; int /*<<< orphan*/ * k; scalar_t__ source; } ;
struct TYPE_4__ {scalar_t__ varname; } ;
typedef  TYPE_2__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  markobject (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  markvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stringmark (scalar_t__) ; 

__attribute__((used)) static void traverseproto (global_State *g, Proto *f) {
  int i;
  if (f->source) stringmark(f->source);
  for (i=0; i<f->sizek; i++)  /* mark literals */
    markvalue(g, &f->k[i]);
  for (i=0; i<f->sizeupvalues; i++) {  /* mark upvalue names */
    if (f->upvalues[i])
      stringmark(f->upvalues[i]);
  }
  for (i=0; i<f->sizep; i++) {  /* mark nested protos */
    if (f->p[i])
      markobject(g, f->p[i]);
  }
  for (i=0; i<f->sizelocvars; i++) {  /* mark local-variable names */
    if (f->locvars[i].varname)
      stringmark(f->locvars[i].varname);
  }
}