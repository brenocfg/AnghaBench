#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_12__* bl; int /*<<< orphan*/  pc; int /*<<< orphan*/  lasttarget; } ;
struct TYPE_17__ {char tok; TYPE_1__* vstack; TYPE_3__* fs; } ;
struct TYPE_16__ {int /*<<< orphan*/  slot; } ;
struct TYPE_15__ {int /*<<< orphan*/  nactvar; int /*<<< orphan*/  flags; } ;
typedef  size_t MSize ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  FSCOPE_GOLA ; 
 scalar_t__ LJ_52 ; 
 int /*<<< orphan*/  LJ_ERR_XLDUP ; 
 char TK_label ; 
 char TK_until ; 
 int /*<<< orphan*/  VSTACK_LABEL ; 
 scalar_t__ gola_findlabel (TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t gola_new (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gola_resolve (TYPE_2__*,TYPE_12__*,size_t) ; 
 int /*<<< orphan*/  lex_check (TYPE_2__*,char) ; 
 int /*<<< orphan*/ * lex_str (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_2__*) ; 
 scalar_t__ parse_isend (char) ; 
 int /*<<< orphan*/  strdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synlevel_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  synlevel_end (TYPE_2__*) ; 

__attribute__((used)) static void parse_label(LexState *ls)
{
  FuncState *fs = ls->fs;
  GCstr *name;
  MSize idx;
  fs->lasttarget = fs->pc;
  fs->bl->flags |= FSCOPE_GOLA;
  lj_lex_next(ls);  /* Skip '::'. */
  name = lex_str(ls);
  if (gola_findlabel(ls, name))
    lj_lex_error(ls, 0, LJ_ERR_XLDUP, strdata(name));
  idx = gola_new(ls, name, VSTACK_LABEL, fs->pc);
  lex_check(ls, TK_label);
  /* Recursively parse trailing statements: labels and ';' (Lua 5.2 only). */
  for (;;) {
    if (ls->tok == TK_label) {
      synlevel_begin(ls);
      parse_label(ls);
      synlevel_end(ls);
    } else if (LJ_52 && ls->tok == ';') {
      lj_lex_next(ls);
    } else {
      break;
    }
  }
  /* Trailing label is considered to be outside of scope. */
  if (parse_isend(ls->tok) && ls->tok != TK_until)
    ls->vstack[idx].slot = fs->bl->nactvar;
  gola_resolve(ls, fs->bl, idx);
}