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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  tm_isdst; scalar_t__ tm_yday; scalar_t__ tm_wday; scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checknumber ; 
 int /*<<< orphan*/  luaL_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setboolfield (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfield (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int os_date (lua_State *L) {
  const char *s = luaL_optstring(L, 1, "%c");
  time_t t = luaL_opt(L, (time_t)luaL_checknumber, 2, time(NULL));
  struct tm *stm;
  if (*s == '!') {  /* UTC? */
    stm = gmtime(&t);
    s++;  /* skip `!' */
  }
  else
    stm = localtime(&t);
  if (stm == NULL)  /* invalid date? */
    lua_pushnil(L);
  else if (strcmp(s, "*t") == 0) {
    lua_createtable(L, 0, 9);  /* 9 = number of fields */
    setfield(L, "sec", stm->tm_sec);
    setfield(L, "min", stm->tm_min);
    setfield(L, "hour", stm->tm_hour);
    setfield(L, "day", stm->tm_mday);
    setfield(L, "month", stm->tm_mon+1);
    setfield(L, "year", stm->tm_year+1900);
    setfield(L, "wday", stm->tm_wday+1);
    setfield(L, "yday", stm->tm_yday+1);
    setboolfield(L, "isdst", stm->tm_isdst);
  }
  else {
    char cc[3];
    luaL_Buffer b;
    cc[0] = '%'; cc[2] = '\0';
    luaL_buffinit(L, &b);
    for (; *s; s++) {
      if (*s != '%' || *(s + 1) == '\0')  /* no conversion specifier? */
        luaL_addchar(&b, *s);
      else {
        size_t reslen;
        char buff[200];  /* should be big enough for any conversion result */
        cc[1] = *(++s);
        reslen = strftime(buff, sizeof(buff), cc, stm);
        luaL_addlstring(&b, buff, reslen);
      }
    }
    luaL_pushresult(&b);
  }
  return 1;
}