#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  nactvar; TYPE_2__* f; } ;
struct TYPE_14__ {char token; } ;
struct TYPE_17__ {TYPE_1__ t; TYPE_5__* fs; } ;
struct TYPE_16__ {int is_vararg; int /*<<< orphan*/  numparams; } ;
struct TYPE_15__ {TYPE_3__* sp; } ;
typedef  TYPE_3__ SharedProto ;
typedef  TYPE_4__ LexState ;
typedef  TYPE_5__ FuncState ;

/* Variables and functions */
#define  TK_DOTS 129 
#define  TK_NAME 128 
 int /*<<< orphan*/  adjustlocalvars (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cast_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_next (TYPE_4__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  new_localvar (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_checkname (TYPE_4__*) ; 
 scalar_t__ testnext (TYPE_4__*,char) ; 

__attribute__((used)) static void parlist (LexState *ls) {
  /* parlist -> [ param { ',' param } ] */
  FuncState *fs = ls->fs;
  SharedProto *f = fs->f->sp;
  int nparams = 0;
  f->is_vararg = 0;
  if (ls->t.token != ')') {  /* is 'parlist' not empty? */
    do {
      switch (ls->t.token) {
        case TK_NAME: {  /* param -> NAME */
          new_localvar(ls, str_checkname(ls));
          nparams++;
          break;
        }
        case TK_DOTS: {  /* param -> '...' */
          luaX_next(ls);
          f->is_vararg = 1;  /* declared vararg */
          break;
        }
        default: luaX_syntaxerror(ls, "<name> or '...' expected");
      }
    } while (!f->is_vararg && testnext(ls, ','));
  }
  adjustlocalvars(ls, nparams);
  f->numparams = cast_byte(fs->nactvar);
  luaK_reserveregs(fs, fs->nactvar);  /* reserve register for parameters */
}