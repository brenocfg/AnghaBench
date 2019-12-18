#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * base; int /*<<< orphan*/ * top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GCROOT_IO_OUTPUT ; 
 int /*<<< orphan*/  IOSTDF_UD (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ LJ_52 ; 
 int /*<<< orphan*/  LUA_TSTRING ; 
 scalar_t__ fwrite (char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 char* lj_strfmt_wstrnum (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int luaL_fileresult (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setudataV (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_file_write(lua_State *L, FILE *fp, int start)
{
  cTValue *tv;
  int status = 1;
  for (tv = L->base+start; tv < L->top; tv++) {
    MSize len;
    const char *p = lj_strfmt_wstrnum(L, tv, &len);
    if (!p)
      lj_err_argt(L, (int)(tv - L->base) + 1, LUA_TSTRING);
    status = status && (fwrite(p, 1, len, fp) == len);
  }
  if (LJ_52 && status) {
    L->top = L->base+1;
    if (start == 0)
      setudataV(L, L->base, IOSTDF_UD(L, GCROOT_IO_OUTPUT));
    return 1;
  }
  return luaL_fileresult(L, status, NULL);
}