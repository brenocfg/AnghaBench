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
typedef  int /*<<< orphan*/  TTree ;

/* Variables and functions */
 int /*<<< orphan*/ * auxemptycap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newtree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static TTree *newemptycap (lua_State *L, int cap) {
  return auxemptycap(newtree(L, 2), cap);
}