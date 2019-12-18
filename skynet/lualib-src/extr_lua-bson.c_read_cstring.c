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
struct bson_reader {int size; char* ptr; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline const char *
read_cstring(lua_State *L, struct bson_reader *br, size_t *sz) {
	int i;
	for (i=0;;i++) {
		if (i==br->size) {
			luaL_error(L, "Invalid bson block : cstring");
		}
		if (br->ptr[i] == '\0') {
			break;
		}
	}
	*sz = i;
	const char * r = (const char *)br->ptr;
	br->ptr += i+1;
	br->size -= i+1;
	return r;
}