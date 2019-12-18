#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* psz_string; void* f_float; void* i_int; int /*<<< orphan*/  b_bool; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  void* lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  void* int64_t ;

/* Variables and functions */
 void* INT32_MAX ; 
 void* INT32_MIN ; 
#define  VLC_VAR_ADDRESS 133 
#define  VLC_VAR_BOOL 132 
 int VLC_VAR_CLASS ; 
#define  VLC_VAR_FLOAT 131 
#define  VLC_VAR_INTEGER 130 
#define  VLC_VAR_STRING 129 
#define  VLC_VAR_VOID 128 
 int /*<<< orphan*/  llround (void*) ; 
 int /*<<< orphan*/  luaL_checkboolean (int /*<<< orphan*/ *,int) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 void* luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_tovalue( lua_State *L, int i_type, vlc_value_t *val )
{
    switch( i_type & VLC_VAR_CLASS )
    {
        case VLC_VAR_VOID:
            break;
        case VLC_VAR_BOOL:
            val->b_bool = luaL_checkboolean( L, -1 );
            break;
        case VLC_VAR_INTEGER:
            /* Lua may only support 32-bit integers. If so, we need to
             * get the value as a float instead so we can even know if
             * there would be an overflow.
             */
            // TODO: check using LUA_MININTEGER and LUA_MAXINTEGER macros
            // if and when we require lua >= 5.3
            if( sizeof( lua_Integer ) < sizeof( val->i_int ) )
            {
                lua_Number f = luaL_checknumber( L, -1 );
                // Calling vlc.var.set() on integer object variables with
                // an out-of-range float value is not handled.
                val->i_int = (int64_t)llround( f );
                if( INT32_MIN < val->i_int && val->i_int < INT32_MAX )
                    val->i_int = luaL_checkinteger( L, -1 );
            }
            else
                val->i_int = luaL_checkinteger( L, -1 );
            break;
        case VLC_VAR_STRING:
            val->psz_string = (char*)luaL_checkstring( L, -1 ); /* XXX: Beware, this only stays valid as long as (L,-1) stays in the stack */
            break;
        case VLC_VAR_FLOAT:
            val->f_float = luaL_checknumber( L, -1 );
            break;
        case VLC_VAR_ADDRESS:
            vlclua_error( L );
            break;
        default:
            vlclua_error( L );
    }
    return 1;
}