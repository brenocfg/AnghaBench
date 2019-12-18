#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_9__ {int type; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_2__ IOFileUD ;

/* Variables and functions */
 int IOFILE_TYPE_FILE ; 
 int IOFILE_TYPE_MASK ; 
 int IOFILE_TYPE_PIPE ; 
 int IOFILE_TYPE_STDF ; 
 int _pclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int luaL_execresult (TYPE_1__*,int) ; 
 int luaL_fileresult (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_pushliteral (TYPE_1__*,char*) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_file_close(lua_State *L, IOFileUD *iof)
{
  int ok;
  if ((iof->type & IOFILE_TYPE_MASK) == IOFILE_TYPE_FILE) {
    ok = (fclose(iof->fp) == 0);
  } else if ((iof->type & IOFILE_TYPE_MASK) == IOFILE_TYPE_PIPE) {
    int stat = -1;
#if LJ_TARGET_POSIX
    stat = pclose(iof->fp);
#elif LJ_TARGET_WINDOWS && !LJ_TARGET_XBOXONE
    stat = _pclose(iof->fp);
#else
    lua_assert(0);
    return 0;
#endif
#if LJ_52
    iof->fp = NULL;
    return luaL_execresult(L, stat);
#else
    ok = (stat != -1);
#endif
  } else {
    lua_assert((iof->type & IOFILE_TYPE_MASK) == IOFILE_TYPE_STDF);
    setnilV(L->top++);
    lua_pushliteral(L, "cannot close standard file");
    return 2;
  }
  iof->fp = NULL;
  return luaL_fileresult(L, ok, NULL);
}