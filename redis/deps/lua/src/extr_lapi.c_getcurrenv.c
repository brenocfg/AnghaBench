#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ci; scalar_t__ base_ci; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_8__ {int /*<<< orphan*/ * env; } ;
struct TYPE_10__ {TYPE_1__ c; } ;
typedef  TYPE_3__ Closure ;

/* Variables and functions */
 TYPE_3__* curr_func (TYPE_2__*) ; 
 int /*<<< orphan*/  gt (TYPE_2__*) ; 
 int /*<<< orphan*/ * hvalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Table *getcurrenv (lua_State *L) {
  if (L->ci == L->base_ci)  /* no enclosing function? */
    return hvalue(gt(L));  /* use global table as environment */
  else {
    Closure *func = curr_func(L);
    return func->c.env;
  }
}