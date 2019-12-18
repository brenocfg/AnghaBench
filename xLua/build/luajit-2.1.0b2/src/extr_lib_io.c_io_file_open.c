#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ IOFileUD ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 TYPE_1__* io_file_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_lib_checkstr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_strfmt_pushf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* strdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IOFileUD *io_file_open(lua_State *L, const char *mode)
{
  const char *fname = strdata(lj_lib_checkstr(L, 1));
  IOFileUD *iof = io_file_new(L);
  iof->fp = fopen(fname, mode);
  if (iof->fp == NULL)
    luaL_argerror(L, 1, lj_strfmt_pushf(L, "%s: %s", fname, strerror(errno)));
  return iof;
}