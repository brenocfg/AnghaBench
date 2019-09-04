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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int MULTI_PART ; 
 int TEMP_LENGTH ; 
 int /*<<< orphan*/  fill_header (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  fill_uint32 (int*,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 

__attribute__((used)) static int
packreq_number(lua_State *L, int session, void * msg, uint32_t sz, int is_push) {
	uint32_t addr = (uint32_t)lua_tointeger(L,1);
	uint8_t buf[TEMP_LENGTH];
	if (sz < MULTI_PART) {
		fill_header(L, buf, sz+9);
		buf[2] = 0;
		fill_uint32(buf+3, addr);
		fill_uint32(buf+7, is_push ? 0 : (uint32_t)session);
		memcpy(buf+11,msg,sz);

		lua_pushlstring(L, (const char *)buf, sz+11);
		return 0;
	} else {
		int part = (sz - 1) / MULTI_PART + 1;
		fill_header(L, buf, 13);
		buf[2] = is_push ? 0x41 : 1;	// multi push or request
		fill_uint32(buf+3, addr);
		fill_uint32(buf+7, (uint32_t)session);
		fill_uint32(buf+11, sz);
		lua_pushlstring(L, (const char *)buf, 15);
		return part;
	}
}