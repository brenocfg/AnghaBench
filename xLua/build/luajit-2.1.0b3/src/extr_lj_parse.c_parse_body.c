#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_15__ {int flags; scalar_t__ bclim; scalar_t__ bcbase; scalar_t__ pc; scalar_t__ numparams; int /*<<< orphan*/  linedefined; } ;
struct TYPE_14__ {scalar_t__ tok; scalar_t__ sizebcstack; scalar_t__ bcstack; int /*<<< orphan*/  linenumber; int /*<<< orphan*/  lastline; TYPE_2__* fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  GCproto ;
typedef  TYPE_2__ FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  scalar_t__ BCPos ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FNEW ; 
 int /*<<< orphan*/  BC_FUNCF ; 
 int /*<<< orphan*/  LJ_TPROTO ; 
 int PROTO_CHILD ; 
 int PROTO_FFI ; 
 int PROTO_FIXUP_RETURN ; 
 int PROTO_HAS_RETURN ; 
 scalar_t__ TK_end ; 
 int /*<<< orphan*/  TK_function ; 
 int /*<<< orphan*/  VRELOCABLE ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_gc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fs_finish (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_init (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fscope_begin (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_match (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_chunk (TYPE_1__*) ; 
 scalar_t__ parse_params (TYPE_1__*,int) ; 

__attribute__((used)) static void parse_body(LexState *ls, ExpDesc *e, int needself, BCLine line)
{
  FuncState fs, *pfs = ls->fs;
  FuncScope bl;
  GCproto *pt;
  ptrdiff_t oldbase = pfs->bcbase - ls->bcstack;
  fs_init(ls, &fs);
  fscope_begin(&fs, &bl, 0);
  fs.linedefined = line;
  fs.numparams = (uint8_t)parse_params(ls, needself);
  fs.bcbase = pfs->bcbase + pfs->pc;
  fs.bclim = pfs->bclim - pfs->pc;
  bcemit_AD(&fs, BC_FUNCF, 0, 0);  /* Placeholder. */
  parse_chunk(ls);
  if (ls->tok != TK_end) lex_match(ls, TK_end, TK_function, line);
  pt = fs_finish(ls, (ls->lastline = ls->linenumber));
  pfs->bcbase = ls->bcstack + oldbase;  /* May have been reallocated. */
  pfs->bclim = (BCPos)(ls->sizebcstack - oldbase);
  /* Store new prototype in the constant array of the parent. */
  expr_init(e, VRELOCABLE,
	    bcemit_AD(pfs, BC_FNEW, 0, const_gc(pfs, obj2gco(pt), LJ_TPROTO)));
#if LJ_HASFFI
  pfs->flags |= (fs.flags & PROTO_FFI);
#endif
  if (!(pfs->flags & PROTO_CHILD)) {
    if (pfs->flags & PROTO_HAS_RETURN)
      pfs->flags |= PROTO_FIXUP_RETURN;
    pfs->flags |= PROTO_CHILD;
  }
  lj_lex_next(ls);
}