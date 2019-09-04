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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  setobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setobj2s (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setobjs2s (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void reverse (lua_State *L, StkId from, StkId to) {
  for (; from < to; from++, to--) {
    TValue temp;
    setobj(L, &temp, from);
    setobjs2s(L, from, to);
    setobj2s(L, to, &temp);
  }
}