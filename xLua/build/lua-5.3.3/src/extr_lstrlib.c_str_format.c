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
typedef  int /*<<< orphan*/  lua_State ;
typedef  char const* lua_Integer ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_INTEGER_FRMLEN ; 
 int /*<<< orphan*/  LUA_NUMBER_FRMLEN ; 
 char const L_ESC ; 
 int MAX_FORMAT ; 
 int MAX_ITEM ; 
 int /*<<< orphan*/  addlenmod (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int l_sprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_addvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 char const* luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const) ; 
 char* luaL_prepbuffsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 char* luaL_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_number2strx (int /*<<< orphan*/ *,char*,int,char*,char const*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* scanformat (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int str_format (lua_State *L) {
  int top = lua_gettop(L);
  int arg = 1;
  size_t sfl;
  const char *strfrmt = luaL_checklstring(L, arg, &sfl);
  const char *strfrmt_end = strfrmt+sfl;
  luaL_Buffer b;
  luaL_buffinit(L, &b);
  while (strfrmt < strfrmt_end) {
    if (*strfrmt != L_ESC)
      luaL_addchar(&b, *strfrmt++);
    else if (*++strfrmt == L_ESC)
      luaL_addchar(&b, *strfrmt++);  /* %% */
    else { /* format item */
      char form[MAX_FORMAT];  /* to store the format ('%...') */
      char *buff = luaL_prepbuffsize(&b, MAX_ITEM);  /* to put formatted item */
      int nb = 0;  /* number of bytes in added item */
      if (++arg > top)
        luaL_argerror(L, arg, "no value");
      strfrmt = scanformat(L, strfrmt, form);
      switch (*strfrmt++) {
        case 'c': {
          nb = l_sprintf(buff, MAX_ITEM, form, (int)luaL_checkinteger(L, arg));
          break;
        }
        case 'd': case 'i':
        case 'o': case 'u': case 'x': case 'X': {
          lua_Integer n = luaL_checkinteger(L, arg);
          addlenmod(form, LUA_INTEGER_FRMLEN);
          nb = l_sprintf(buff, MAX_ITEM, form, n);
          break;
        }
        case 'a': case 'A':
          addlenmod(form, LUA_NUMBER_FRMLEN);
          nb = lua_number2strx(L, buff, MAX_ITEM, form,
                                  luaL_checknumber(L, arg));
          break;
        case 'e': case 'E': case 'f':
        case 'g': case 'G': {
          addlenmod(form, LUA_NUMBER_FRMLEN);
          nb = l_sprintf(buff, MAX_ITEM, form, luaL_checknumber(L, arg));
          break;
        }
        case 'q': {
          addliteral(L, &b, arg);
          break;
        }
        case 's': {
          size_t l;
          const char *s = luaL_tolstring(L, arg, &l);
          if (form[2] == '\0')  /* no modifiers? */
            luaL_addvalue(&b);  /* keep entire string */
          else {
            luaL_argcheck(L, l == strlen(s), arg, "string contains zeros");
            if (!strchr(form, '.') && l >= 100) {
              /* no precision and string is too long to be formatted */
              luaL_addvalue(&b);  /* keep entire string */
            }
            else {  /* format the string into 'buff' */
              nb = l_sprintf(buff, MAX_ITEM, form, s);
              lua_pop(L, 1);  /* remove result from 'luaL_tolstring' */
            }
          }
          break;
        }
        default: {  /* also treat cases 'pnLlh' */
          return luaL_error(L, "invalid option '%%%c' to 'format'",
                               *(strfrmt - 1));
        }
      }
      lua_assert(nb < MAX_ITEM);
      luaL_addsize(&b, nb);
    }
  }
  luaL_pushresult(&b);
  return 1;
}