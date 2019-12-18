#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;
typedef  TYPE_1__ GCupval ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* uvnext (TYPE_1__*) ; 
 TYPE_1__* uvprev (TYPE_1__*) ; 

__attribute__((used)) static void unlinkuv(GCupval *uv)
{
  lua_assert(uvprev(uvnext(uv)) == uv && uvnext(uvprev(uv)) == uv);
  setgcrefr(uvnext(uv)->prev, uv->prev);
  setgcrefr(uvprev(uv)->next, uv->next);
}