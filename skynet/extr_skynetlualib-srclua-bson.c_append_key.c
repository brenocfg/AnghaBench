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
struct bson {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  write_byte (struct bson*,int) ; 
 int /*<<< orphan*/  write_string (struct bson*,int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static inline void
append_key(struct bson *bs, lua_State *L, int type, const char *key, size_t sz) {
	write_byte(bs, type);
	write_string(bs, L, key, sz);
}