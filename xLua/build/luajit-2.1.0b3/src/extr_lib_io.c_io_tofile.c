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
 int /*<<< orphan*/  LJ_ERR_IOCLFL ; 
 TYPE_1__* io_tofilep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static IOFileUD *io_tofile(lua_State *L)
{
  IOFileUD *iof = io_tofilep(L);
  if (iof->fp == NULL)
    lj_err_caller(L, LJ_ERR_IOCLFL);
  return iof;
}