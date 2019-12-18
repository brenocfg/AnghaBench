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
struct read_block {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  invalid_stream (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 char* rb_read (struct read_block*,int) ; 

__attribute__((used)) static void
get_buffer(lua_State *L, struct read_block *rb, int len) {
	char * p = rb_read(rb,len);
	if (p == NULL) {
		invalid_stream(L,rb);
	}
	lua_pushlstring(L,p,len);
}