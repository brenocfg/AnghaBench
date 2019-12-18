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
struct socket_sendbuffer {size_t sz; void* buffer; void* type; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TLIGHTUSERDATA 130 
#define  LUA_TTABLE 129 
#define  LUA_TUSERDATA 128 
 void* SOCKET_BUFFER_MEMORY ; 
 void* SOCKET_BUFFER_OBJECT ; 
 void* SOCKET_BUFFER_RAWPOINTER ; 
 int /*<<< orphan*/  concat_table (int /*<<< orphan*/ *,int,void*,size_t) ; 
 size_t count_size (int /*<<< orphan*/ *,int) ; 
 void* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 size_t lua_rawlen (int /*<<< orphan*/ *,int) ; 
 void* lua_tointeger (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 void* skynet_malloc (size_t) ; 

__attribute__((used)) static void
get_buffer(lua_State *L, int index, struct socket_sendbuffer *buf) {
	void *buffer;
	switch(lua_type(L, index)) {
		size_t len;
	case LUA_TUSERDATA:
		// lua full useobject must be a raw pointer, it can't be a socket object or a memory object.
		buf->type = SOCKET_BUFFER_RAWPOINTER;
		buf->buffer = lua_touserdata(L, index);
		if (lua_isinteger(L, index+1)) {
			buf->sz = lua_tointeger(L, index+1);
		} else {
			buf->sz = lua_rawlen(L, index);
		}
		break;
	case LUA_TLIGHTUSERDATA: {
		int sz = -1;
		if (lua_isinteger(L, index+1)) {
			sz = lua_tointeger(L,index+1);
		}
		if (sz < 0) {
			buf->type = SOCKET_BUFFER_OBJECT;
		} else {
			buf->type = SOCKET_BUFFER_MEMORY;
		}
		buf->buffer = lua_touserdata(L,index);
		buf->sz = (size_t)sz;
		break;
		}
	case LUA_TTABLE:
		// concat the table as a string
		len = count_size(L, index);
		buffer = skynet_malloc(len);
		concat_table(L, index, buffer, len);
		buf->type = SOCKET_BUFFER_MEMORY;
		buf->buffer = buffer;
		buf->sz = len;
		break;
	default:
		buf->type = SOCKET_BUFFER_RAWPOINTER;
		buf->buffer = luaL_checklstring(L, index, &buf->sz);
		break;
	}
}