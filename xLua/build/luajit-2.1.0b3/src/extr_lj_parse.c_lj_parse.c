#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_23__ {int /*<<< orphan*/ * prev; int /*<<< orphan*/  flags; scalar_t__ bclim; int /*<<< orphan*/ * bcbase; scalar_t__ numparams; scalar_t__ linedefined; } ;
struct TYPE_22__ {scalar_t__ sizeuv; } ;
struct TYPE_21__ {scalar_t__ tok; int /*<<< orphan*/ * fs; int /*<<< orphan*/  linenumber; scalar_t__ level; int /*<<< orphan*/  chunkname; int /*<<< orphan*/  chunkarg; TYPE_1__* L; } ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ GCproto ;
typedef  TYPE_4__ FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FUNCV ; 
 int /*<<< orphan*/  PROTO_VARARG ; 
 scalar_t__ TK_eof ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_token (TYPE_2__*,scalar_t__) ; 
 TYPE_3__* fs_finish (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_init (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fscope_begin (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_str_newlit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  lj_str_newz (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  parse_chunk (TYPE_2__*) ; 
 int /*<<< orphan*/  setstrV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GCproto *lj_parse(LexState *ls)
{
  FuncState fs;
  FuncScope bl;
  GCproto *pt;
  lua_State *L = ls->L;
#ifdef LUAJIT_DISABLE_DEBUGINFO
  ls->chunkname = lj_str_newlit(L, "=");
#else
  ls->chunkname = lj_str_newz(L, ls->chunkarg);
#endif
  setstrV(L, L->top, ls->chunkname);  /* Anchor chunkname string. */
  incr_top(L);
  ls->level = 0;
  fs_init(ls, &fs);
  fs.linedefined = 0;
  fs.numparams = 0;
  fs.bcbase = NULL;
  fs.bclim = 0;
  fs.flags |= PROTO_VARARG;  /* Main chunk is always a vararg func. */
  fscope_begin(&fs, &bl, 0);
  bcemit_AD(&fs, BC_FUNCV, 0, 0);  /* Placeholder. */
  lj_lex_next(ls);  /* Read-ahead first token. */
  parse_chunk(ls);
  if (ls->tok != TK_eof)
    err_token(ls, TK_eof);
  pt = fs_finish(ls, ls->linenumber);
  L->top--;  /* Drop chunkname. */
  lua_assert(fs.prev == NULL);
  lua_assert(ls->fs == NULL);
  lua_assert(pt->sizeuv == 0);
  return pt;
}