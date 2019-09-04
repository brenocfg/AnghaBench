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
 int UCHAR_MAX ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/ * newcharset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setchar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  treebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void createcat (lua_State *L, const char *catname, int (catf) (int)) {
  TTree *t = newcharset(L);
  int i;
  for (i = 0; i <= UCHAR_MAX; i++)
    if (catf(i)) setchar(treebuffer(t), i);
  lua_setfield(L, -2, catname);
}