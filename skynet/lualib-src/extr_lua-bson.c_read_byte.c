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
typedef  int uint8_t ;
struct bson_reader {int* ptr; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  check_reader (int /*<<< orphan*/ *,struct bson_reader*,int) ; 

__attribute__((used)) static inline int
read_byte(lua_State *L, struct bson_reader *br) {
	check_reader(L, br, 1);
	const uint8_t * b = br->ptr;
	int r =  b[0];
	++br->ptr;
	--br->size;

	return r;
}