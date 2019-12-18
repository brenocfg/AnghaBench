#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {int line; } ;
struct TYPE_7__ {int linedefined; size_t pc; TYPE_3__* bcbase; } ;
struct TYPE_6__ {int firstline; int numline; int /*<<< orphan*/  lineinfo; } ;
typedef  size_t MSize ;
typedef  TYPE_1__ GCproto ;
typedef  TYPE_2__ FuncState ;
typedef  int BCLine ;
typedef  TYPE_3__ BCInsLine ;

/* Variables and functions */
 scalar_t__ LJ_LIKELY (int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void fs_fixup_line(FuncState *fs, GCproto *pt,
			  void *lineinfo, BCLine numline)
{
  BCInsLine *base = fs->bcbase + 1;
  BCLine first = fs->linedefined;
  MSize i = 0, n = fs->pc-1;
  pt->firstline = fs->linedefined;
  pt->numline = numline;
  setmref(pt->lineinfo, lineinfo);
  if (LJ_LIKELY(numline < 256)) {
    uint8_t *li = (uint8_t *)lineinfo;
    do {
      BCLine delta = base[i].line - first;
      lua_assert(delta >= 0 && delta < 256);
      li[i] = (uint8_t)delta;
    } while (++i < n);
  } else if (LJ_LIKELY(numline < 65536)) {
    uint16_t *li = (uint16_t *)lineinfo;
    do {
      BCLine delta = base[i].line - first;
      lua_assert(delta >= 0 && delta < 65536);
      li[i] = (uint16_t)delta;
    } while (++i < n);
  } else {
    uint32_t *li = (uint32_t *)lineinfo;
    do {
      BCLine delta = base[i].line - first;
      lua_assert(delta >= 0);
      li[i] = (uint32_t)delta;
    } while (++i < n);
  }
}