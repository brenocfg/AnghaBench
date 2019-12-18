#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 TYPE_1__* threadV (scalar_t__) ; 
 scalar_t__ tvisthread (scalar_t__) ; 

__attribute__((used)) static lua_State *getthread(lua_State *L, int *arg)
{
  if (L->base < L->top && tvisthread(L->base)) {
    *arg = 1;
    return threadV(L->base);
  } else {
    *arg = 0;
    return L;
  }
}