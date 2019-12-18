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
struct bson {char* ptr; int size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  bson_reserve (struct bson*,size_t) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int utf8_copy (char const*,char*,size_t) ; 

__attribute__((used)) static void
write_string(struct bson *b, lua_State *L, const char *key, size_t sz) {
	bson_reserve(b,sz+1);
	char *dst = (char *)(b->ptr + b->size);
	const char *src = key;
	size_t n = sz;
	while(n > 0) {
		int c = utf8_copy(src, dst, n);
		if (c == 0) {
			luaL_error(L, "Invalid utf8 string");
		}
		src += c;
		dst += c;
		n -= c;
	}
	b->ptr[b->size+sz] = '\0';
	b->size+=sz+1;
}