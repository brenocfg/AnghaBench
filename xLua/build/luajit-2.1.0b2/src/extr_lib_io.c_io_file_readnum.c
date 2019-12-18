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
struct TYPE_3__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ lua_Number ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  LUA_NUMBER_SCAN ; 
 int fscanf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ lj_num2int (scalar_t__) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tvismzero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_file_readnum(lua_State *L, FILE *fp)
{
  lua_Number d;
  if (fscanf(fp, LUA_NUMBER_SCAN, &d) == 1) {
    if (LJ_DUALNUM) {
      int32_t i = lj_num2int(d);
      if (d == (lua_Number)i && !tvismzero((cTValue *)&d)) {
	setintV(L->top++, i);
	return 1;
      }
    }
    setnumV(L->top++, d);
    return 1;
  } else {
    setnilV(L->top++);
    return 0;
  }
}