#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pc; int lasttarget; int flags; TYPE_2__* bcbase; int /*<<< orphan*/  ls; TYPE_1__* bl; } ;
struct TYPE_10__ {int /*<<< orphan*/  ins; int /*<<< orphan*/  line; } ;
struct TYPE_9__ {int flags; } ;
typedef  TYPE_3__ FuncState ;
typedef  int BCPos ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int BCBIAS_J ; 
 int /*<<< orphan*/  BCINS_AD (int,int /*<<< orphan*/ ,int) ; 
 int BCMAX_D ; 
#define  BC_CALLMT 134 
#define  BC_CALLT 133 
#define  BC_RET 132 
#define  BC_RET0 131 
#define  BC_RET1 130 
#define  BC_RETM 129 
#define  BC_UCLO 128 
 int FSCOPE_NOCLOSE ; 
 int FSCOPE_UPVAL ; 
 int /*<<< orphan*/  LJ_ERR_XFIXUP ; 
 int PROTO_FIXUP_RETURN ; 
 int bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcemit_AJ (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcemit_INS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopisret (int) ; 
 int /*<<< orphan*/  err_syntax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_fixup_ret(FuncState *fs)
{
  BCPos lastpc = fs->pc;
  if (lastpc <= fs->lasttarget || !bcopisret(bc_op(fs->bcbase[lastpc-1].ins))) {
    if ((fs->bl->flags & FSCOPE_UPVAL))
      bcemit_AJ(fs, BC_UCLO, 0, 0);
    bcemit_AD(fs, BC_RET0, 0, 1);  /* Need final return. */
  }
  fs->bl->flags |= FSCOPE_NOCLOSE;  /* Handled above. */
  fscope_end(fs);
  lua_assert(fs->bl == NULL);
  /* May need to fixup returns encoded before first function was created. */
  if (fs->flags & PROTO_FIXUP_RETURN) {
    BCPos pc;
    for (pc = 1; pc < lastpc; pc++) {
      BCIns ins = fs->bcbase[pc].ins;
      BCPos offset;
      switch (bc_op(ins)) {
      case BC_CALLMT: case BC_CALLT:
      case BC_RETM: case BC_RET: case BC_RET0: case BC_RET1:
	offset = bcemit_INS(fs, ins);  /* Copy original instruction. */
	fs->bcbase[offset].line = fs->bcbase[pc].line;
	offset = offset-(pc+1)+BCBIAS_J;
	if (offset > BCMAX_D)
	  err_syntax(fs->ls, LJ_ERR_XFIXUP);
	/* Replace with UCLO plus branch. */
	fs->bcbase[pc].ins = BCINS_AD(BC_UCLO, 0, offset);
	break;
      case BC_UCLO:
	return;  /* We're done. */
      default:
	break;
      }
    }
  }
}