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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sproto_arg {scalar_t__ tagname; scalar_t__ mainindex; int type; int extra; size_t length; scalar_t__ value; int /*<<< orphan*/  subtype; int /*<<< orphan*/  index; struct encode_ud* ud; } ;
struct encode_ud {scalar_t__ deep; scalar_t__ array_tag; int tbl_index; int array_index; int iter_func; int iter_table; int iter_key; int /*<<< orphan*/  st; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Number ;
typedef  int lua_Integer ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ ENCODE_DEEPLEVEL ; 
 int SPROTO_CB_ERROR ; 
 int SPROTO_CB_NIL ; 
 int SPROTO_CB_NOARRAY ; 
#define  SPROTO_TBOOLEAN 131 
#define  SPROTO_TINTEGER 130 
#define  SPROTO_TSTRING 129 
#define  SPROTO_TSTRUCT 128 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ luaL_getmetafield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  lua_geti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_tointegerx (int /*<<< orphan*/ *,int,int*) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  next_list (int /*<<< orphan*/ *,struct encode_ud*) ; 
 int /*<<< orphan*/  round (int) ; 
 int sproto_encode (int /*<<< orphan*/ ,scalar_t__,size_t,int (*) (struct sproto_arg const*),struct encode_ud*) ; 

__attribute__((used)) static int
encode(const struct sproto_arg *args) {
	struct encode_ud *self = args->ud;
	lua_State *L = self->L;
	luaL_checkstack(L, 12, NULL);
	if (self->deep >= ENCODE_DEEPLEVEL)
		return luaL_error(L, "The table is too deep");
	if (args->index > 0) {
		if (args->tagname != self->array_tag) {
			// a new array
			self->array_tag = args->tagname;
			lua_getfield(L, self->tbl_index, args->tagname);
			if (lua_isnil(L, -1)) {
				if (self->array_index) {
					lua_replace(L, self->array_index);
				}
				self->array_index = 0;
				return SPROTO_CB_NOARRAY;
			}
			if (self->array_index) {
				lua_replace(L, self->array_index);
			} else {
				self->array_index = lua_gettop(L);
			}

			if (luaL_getmetafield(L, self->array_index, "__pairs")) {
				lua_pushvalue(L, self->array_index);
				lua_call(L,	1, 3);
				int top = lua_gettop(L);
				self->iter_func = top - 2;
				self->iter_table = top - 1;
				self->iter_key = top;
			} else if (!lua_istable(L,self->array_index)) {
				return luaL_error(L, ".*%s(%d) should be a table or an userdata with metamethods (Is a %s)",
					args->tagname, args->index, lua_typename(L, lua_type(L, -1)));
			} else {
				lua_pushnil(L);
				self->iter_func = 0;
				self->iter_table = 0;
				self->iter_key = lua_gettop(L);
			}
		}
		if (args->mainindex >= 0) {
			if (!next_list(L, self)) {
				// iterate end
				lua_pushnil(L);
				lua_replace(L, self->iter_key);
				return SPROTO_CB_NIL;
			}
			lua_insert(L, -2);
			lua_replace(L, self->iter_key);
		} else {
			lua_geti(L, self->array_index, args->index);
		}
	} else {
		lua_getfield(L, self->tbl_index, args->tagname);
	}
	if (lua_isnil(L, -1)) {
		lua_pop(L,1);
		return SPROTO_CB_NIL;
	}
	switch (args->type) {
	case SPROTO_TINTEGER: {
		int64_t v;
		lua_Integer vh;
		int isnum;
		if (args->extra) {
			// It's decimal.
			lua_Number vn = lua_tonumber(L, -1);
			// use 64bit integer for 32bit architecture.
			v = (int64_t)(round(vn * args->extra));
		} else {
			v = lua_tointegerx(L, -1, &isnum);
			if(!isnum) {
				return luaL_error(L, ".%s[%d] is not an integer (Is a %s)", 
					args->tagname, args->index, lua_typename(L, lua_type(L, -1)));
			}
		}
		lua_pop(L,1);
		// notice: in lua 5.2, lua_Integer maybe 52bit
		vh = v >> 31;
		if (vh == 0 || vh == -1) {
			*(uint32_t *)args->value = (uint32_t)v;
			return 4;
		}
		else {
			*(uint64_t *)args->value = (uint64_t)v;
			return 8;
		}
	}
	case SPROTO_TBOOLEAN: {
		int v = lua_toboolean(L, -1);
		if (!lua_isboolean(L,-1)) {
			return luaL_error(L, ".%s[%d] is not a boolean (Is a %s)",
				args->tagname, args->index, lua_typename(L, lua_type(L, -1)));
		}
		*(int *)args->value = v;
		lua_pop(L,1);
		return 4;
	}
	case SPROTO_TSTRING: {
		size_t sz = 0;
		const char * str;
		if (!lua_isstring(L, -1)) {
			return luaL_error(L, ".%s[%d] is not a string (Is a %s)", 
				args->tagname, args->index, lua_typename(L, lua_type(L, -1)));
		} else {
			str = lua_tolstring(L, -1, &sz);
		}
		if (sz > args->length)
			return SPROTO_CB_ERROR;
		memcpy(args->value, str, sz);
		lua_pop(L,1);
		return sz;
	}
	case SPROTO_TSTRUCT: {
		struct encode_ud sub;
		int r;
		int top = lua_gettop(L);
		sub.L = L;
		sub.st = args->subtype;
		sub.tbl_index = top;
		sub.array_tag = NULL;
		sub.array_index = 0;
		sub.deep = self->deep + 1;
		sub.iter_func = 0;
		sub.iter_table = 0;
		sub.iter_key = 0;
		r = sproto_encode(args->subtype, args->value, args->length, encode, &sub);
		lua_settop(L, top-1);	// pop the value
		if (r < 0) 
			return SPROTO_CB_ERROR;
		return r;
	}
	default:
		return luaL_error(L, "Invalid field type %d", args->type);
	}
}