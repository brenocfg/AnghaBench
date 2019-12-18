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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ IOFileUD ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* IOSTDF_IOF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LJ_ERR_IOSTDCL ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *io_stdfile(lua_State *L, ptrdiff_t id)
{
  IOFileUD *iof = IOSTDF_IOF(L, id);
  if (iof->fp == NULL)
    lj_err_caller(L, LJ_ERR_IOSTDCL);
  return iof->fp;
}