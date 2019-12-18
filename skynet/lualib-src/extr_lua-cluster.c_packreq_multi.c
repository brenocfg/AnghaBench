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
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

__attribute__((used)) static void
packreq_multi(lua_State *L, int session, void * msg, uint32_t sz) {
	uint8_t buf[TEMP_LENGTH];
	int part = (sz - 1) / MULTI_PART + 1;
	int i;
	char *ptr = msg;
	for (i=0;i<part;i++) {
		uint32_t s;
		if (sz > MULTI_PART) {
			s = MULTI_PART;
			buf[2] = 2;
		} else {
			s = sz;
			buf[2] = 3;	// the last multi part
		}
		fill_header(L, buf, s+5);
		fill_uint32(buf+3, (uint32_t)session);
		memcpy(buf+7, ptr, s);
		lua_pushlstring(L, (const char *)buf, s+7);
		lua_rawseti(L, -2, i+1);
		sz -= s;
		ptr += s;
	}
}