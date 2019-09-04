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
typedef  int time_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int ATOM_FINC (int /*<<< orphan*/ *) ; 
 int BSON_OBJECTID ; 
 int hextoint (char const) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_counter ; 
 int /*<<< orphan*/  oid_header ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lobjectid(lua_State *L) {
	uint8_t oid[14] = { 0, BSON_OBJECTID };
	if (lua_isstring(L,1)) {
		size_t len;
		const char * str = lua_tolstring(L,1,&len);
		if (len != 24) {
			return luaL_error(L, "Invalid objectid %s", str);
		}
		int i;
		for (i=0;i<12;i++) {
			oid[i+2] = hextoint(str[i*2]) << 4 | hextoint(str[i*2+1]);
		}
	} else {
		time_t ti = time(NULL);
		// old_counter is a static var, use atom inc.
		uint32_t id = ATOM_FINC(&oid_counter);

		oid[2] = (ti>>24) & 0xff;
		oid[3] = (ti>>16) & 0xff;
		oid[4] = (ti>>8) & 0xff;
		oid[5] = ti & 0xff;
		memcpy(oid+6 , oid_header, 5);
		oid[11] = (id>>16) & 0xff; 
		oid[12] = (id>>8) & 0xff; 
		oid[13] = id & 0xff;
	}
	lua_pushlstring( L, (const char *)oid, 14);

	return 1;
}