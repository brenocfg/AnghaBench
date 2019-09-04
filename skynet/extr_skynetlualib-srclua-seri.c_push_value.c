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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct read_block {int dummy; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  TYPE_BOOLEAN 134 
#define  TYPE_LONG_STRING 133 
#define  TYPE_NIL 132 
#define  TYPE_NUMBER 131 
 int TYPE_NUMBER_REAL ; 
#define  TYPE_SHORT_STRING 130 
#define  TYPE_TABLE 129 
#define  TYPE_USERDATA 128 
 int /*<<< orphan*/  get_buffer (int /*<<< orphan*/ *,struct read_block*,int) ; 
 int /*<<< orphan*/  get_integer (int /*<<< orphan*/ *,struct read_block*,int) ; 
 int /*<<< orphan*/  get_pointer (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  get_real (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  invalid_stream (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* rb_read (struct read_block*,int) ; 
 int /*<<< orphan*/  unpack_table (int /*<<< orphan*/ *,struct read_block*,int) ; 

__attribute__((used)) static void
push_value(lua_State *L, struct read_block *rb, int type, int cookie) {
	switch(type) {
	case TYPE_NIL:
		lua_pushnil(L);
		break;
	case TYPE_BOOLEAN:
		lua_pushboolean(L,cookie);
		break;
	case TYPE_NUMBER:
		if (cookie == TYPE_NUMBER_REAL) {
			lua_pushnumber(L,get_real(L,rb));
		} else {
			lua_pushinteger(L, get_integer(L, rb, cookie));
		}
		break;
	case TYPE_USERDATA:
		lua_pushlightuserdata(L,get_pointer(L,rb));
		break;
	case TYPE_SHORT_STRING:
		get_buffer(L,rb,cookie);
		break;
	case TYPE_LONG_STRING: {
		if (cookie == 2) {
			uint16_t *plen = rb_read(rb, 2);
			if (plen == NULL) {
				invalid_stream(L,rb);
			}
			uint16_t n;
			memcpy(&n, plen, sizeof(n));
			get_buffer(L,rb,n);
		} else {
			if (cookie != 4) {
				invalid_stream(L,rb);
			}
			uint32_t *plen = rb_read(rb, 4);
			if (plen == NULL) {
				invalid_stream(L,rb);
			}
			uint32_t n;
			memcpy(&n, plen, sizeof(n));
			get_buffer(L,rb,n);
		}
		break;
	}
	case TYPE_TABLE: {
		unpack_table(L,rb,cookie);
		break;
	}
	default: {
		invalid_stream(L,rb);
		break;
	}
	}
}