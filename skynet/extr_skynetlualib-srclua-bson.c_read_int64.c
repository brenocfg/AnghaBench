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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct bson_reader {int* ptr; int size; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_reader (int /*<<< orphan*/ *,struct bson_reader*,int) ; 

__attribute__((used)) static inline int64_t
read_int64(lua_State *L, struct bson_reader *br) {
	check_reader(L, br, 8);
	const uint8_t * b = br->ptr;
	uint32_t lo = b[0] | b[1]<<8 | b[2]<<16 | b[3]<<24;
	uint32_t hi = b[4] | b[5]<<8 | b[6]<<16 | b[7]<<24;
	uint64_t v = (uint64_t)lo | (uint64_t)hi<<32;
	br->ptr+=8;
	br->size-=8;
	return (int64_t)v;
}