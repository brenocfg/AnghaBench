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
struct TYPE_5__ {int nupvalues; int /*<<< orphan*/  p; TYPE_1__** upvals; } ;
struct TYPE_4__ {int /*<<< orphan*/  const* v; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ LClosure ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 TYPE_2__* ci_func (int /*<<< orphan*/ *) ; 
 char* upvalname (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *getupvalname (CallInfo *ci, const TValue *o,
                                 const char **name) {
  LClosure *c = ci_func(ci);
  int i;
  for (i = 0; i < c->nupvalues; i++) {
    if (c->upvals[i]->v == o) {
      *name = upvalname(c->p, i);
      return "upvalue";
    }
  }
  return NULL;
}