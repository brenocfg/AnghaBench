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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct read_block {int dummy; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  TYPE_NUMBER_BYTE 132 
#define  TYPE_NUMBER_DWORD 131 
#define  TYPE_NUMBER_QWORD 130 
#define  TYPE_NUMBER_WORD 129 
#define  TYPE_NUMBER_ZERO 128 
 int /*<<< orphan*/  invalid_stream (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rb_read (struct read_block*,int) ; 

__attribute__((used)) static lua_Integer
get_integer(lua_State *L, struct read_block *rb, int cookie) {
	switch (cookie) {
	case TYPE_NUMBER_ZERO:
		return 0;
	case TYPE_NUMBER_BYTE: {
		uint8_t n;
		uint8_t * pn = rb_read(rb,sizeof(n));
		if (pn == NULL)
			invalid_stream(L,rb);
		n = *pn;
		return n;
	}
	case TYPE_NUMBER_WORD: {
		uint16_t n;
		uint16_t * pn = rb_read(rb,sizeof(n));
		if (pn == NULL)
			invalid_stream(L,rb);
		memcpy(&n, pn, sizeof(n));
		return n;
	}
	case TYPE_NUMBER_DWORD: {
		int32_t n;
		int32_t * pn = rb_read(rb,sizeof(n));
		if (pn == NULL)
			invalid_stream(L,rb);
		memcpy(&n, pn, sizeof(n));
		return n;
	}
	case TYPE_NUMBER_QWORD: {
		int64_t n;
		int64_t * pn = rb_read(rb,sizeof(n));
		if (pn == NULL)
			invalid_stream(L,rb);
		memcpy(&n, pn, sizeof(n));
		return n;
	}
	default:
		invalid_stream(L,rb);
		return 0;
	}
}