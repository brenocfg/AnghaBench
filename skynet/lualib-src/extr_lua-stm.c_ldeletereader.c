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
struct boxreader {int /*<<< orphan*/ * lastcopy; int /*<<< orphan*/ * obj; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct boxreader* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm_releasecopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_releasereader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ldeletereader(lua_State *L) {
	struct boxreader * box = lua_touserdata(L, 1);
	stm_releasereader(box->obj);
	box->obj = NULL;
	stm_releasecopy(box->lastcopy);
	box->lastcopy = NULL;

	return 0;
}