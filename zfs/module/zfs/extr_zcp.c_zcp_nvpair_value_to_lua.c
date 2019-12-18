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
typedef  int uint_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int int64_t ;

/* Variables and functions */
#define  DATA_TYPE_BOOLEAN_VALUE 134 
#define  DATA_TYPE_INT64 133 
#define  DATA_TYPE_INT64_ARRAY 132 
#define  DATA_TYPE_NVLIST 131 
#define  DATA_TYPE_STRING 130 
#define  DATA_TYPE_STRING_ARRAY 129 
#define  DATA_TYPE_UINT64_ARRAY 128 
 int EINVAL ; 
 int /*<<< orphan*/  fnvpair_value_boolean_value (int /*<<< orphan*/ *) ; 
 int fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 char* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_int64_array (int /*<<< orphan*/ *,int**,int*) ; 
 int /*<<< orphan*/  nvpair_value_string_array (int /*<<< orphan*/ *,char***,int*) ; 
 int /*<<< orphan*/  nvpair_value_uint64_array (int /*<<< orphan*/ *,int**,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 int zcp_nvlist_to_lua (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
zcp_nvpair_value_to_lua(lua_State *state, nvpair_t *pair,
    char *errbuf, int errbuf_len)
{
	int err = 0;

	if (pair == NULL) {
		lua_pushnil(state);
		return (0);
	}

	switch (nvpair_type(pair)) {
	case DATA_TYPE_BOOLEAN_VALUE:
		(void) lua_pushboolean(state,
		    fnvpair_value_boolean_value(pair));
		break;
	case DATA_TYPE_STRING:
		(void) lua_pushstring(state, fnvpair_value_string(pair));
		break;
	case DATA_TYPE_INT64:
		(void) lua_pushinteger(state, fnvpair_value_int64(pair));
		break;
	case DATA_TYPE_NVLIST:
		err = zcp_nvlist_to_lua(state,
		    fnvpair_value_nvlist(pair), errbuf, errbuf_len);
		break;
	case DATA_TYPE_STRING_ARRAY: {
		char **strarr;
		uint_t nelem;
		(void) nvpair_value_string_array(pair, &strarr, &nelem);
		lua_newtable(state);
		for (int i = 0; i < nelem; i++) {
			(void) lua_pushinteger(state, i + 1);
			(void) lua_pushstring(state, strarr[i]);
			(void) lua_settable(state, -3);
		}
		break;
	}
	case DATA_TYPE_UINT64_ARRAY: {
		uint64_t *intarr;
		uint_t nelem;
		(void) nvpair_value_uint64_array(pair, &intarr, &nelem);
		lua_newtable(state);
		for (int i = 0; i < nelem; i++) {
			(void) lua_pushinteger(state, i + 1);
			(void) lua_pushinteger(state, intarr[i]);
			(void) lua_settable(state, -3);
		}
		break;
	}
	case DATA_TYPE_INT64_ARRAY: {
		int64_t *intarr;
		uint_t nelem;
		(void) nvpair_value_int64_array(pair, &intarr, &nelem);
		lua_newtable(state);
		for (int i = 0; i < nelem; i++) {
			(void) lua_pushinteger(state, i + 1);
			(void) lua_pushinteger(state, intarr[i]);
			(void) lua_settable(state, -3);
		}
		break;
	}
	default: {
		if (errbuf != NULL) {
			(void) snprintf(errbuf, errbuf_len,
			    "Unhandled nvpair type %d for key '%s'",
			    nvpair_type(pair), nvpair_name(pair));
		}
		return (EINVAL);
	}
	}
	return (err);
}