#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ framedepth; int /*<<< orphan*/  pc; TYPE_1__* L; int /*<<< orphan*/ * baseslot; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_7__ {int framesize; } ;
struct TYPE_5__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  int /*<<< orphan*/  BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_FR2 ; 
 int /*<<< orphan*/  SNAP_MKFTSZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNAP_MKPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_contpc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_ftsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_isc (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_iscont (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_islua (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_pc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevl (int /*<<< orphan*/ *) ; 
 TYPE_4__* funcproto (int /*<<< orphan*/ *) ; 
 scalar_t__ isluafunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static BCReg snapshot_framelinks(jit_State *J, SnapEntry *map)
{
  cTValue *frame = J->L->base - 1;
  cTValue *lim = J->L->base - J->baseslot;
  GCfunc *fn = frame_func(frame);
  cTValue *ftop = isluafunc(fn) ? (frame+funcproto(fn)->framesize) : J->L->top;
  MSize f = 0;
  lua_assert(!LJ_FR2);  /* TODO_FR2: store 64 bit PCs. */
  map[f++] = SNAP_MKPC(J->pc);  /* The current PC is always the first entry. */
  while (frame > lim) {  /* Backwards traversal of all frames above base. */
    if (frame_islua(frame)) {
      map[f++] = SNAP_MKPC(frame_pc(frame));
      frame = frame_prevl(frame);
    } else if (frame_iscont(frame)) {
      map[f++] = SNAP_MKFTSZ(frame_ftsz(frame));
      map[f++] = SNAP_MKPC(frame_contpc(frame));
      frame = frame_prevd(frame);
    } else {
      lua_assert(!frame_isc(frame));
      map[f++] = SNAP_MKFTSZ(frame_ftsz(frame));
      frame = frame_prevd(frame);
      continue;
    }
    if (frame + funcproto(frame_func(frame))->framesize > ftop)
      ftop = frame + funcproto(frame_func(frame))->framesize;
  }
  lua_assert(f == (MSize)(1 + J->framedepth));
  return (BCReg)(ftop - lim);
}