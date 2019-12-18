#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_14__ {int freereg; } ;
struct TYPE_13__ {int linenumber; TYPE_2__* fs; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_IN ; 
 int /*<<< orphan*/  adjust_assign (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checknext (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forbody (TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_checkstack (TYPE_2__*,int) ; 
 int /*<<< orphan*/  new_localvar (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_localvarliteral (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * str_checkname (TYPE_1__*) ; 
 scalar_t__ testnext (TYPE_1__*,char) ; 

__attribute__((used)) static void forlist (LexState *ls, TString *indexname) {
  /* forlist -> NAME {,NAME} IN explist forbody */
  FuncState *fs = ls->fs;
  expdesc e;
  int nvars = 4;  /* gen, state, control, plus at least one declared var */
  int line;
  int base = fs->freereg;
  /* create control variables */
  new_localvarliteral(ls, "(for generator)");
  new_localvarliteral(ls, "(for state)");
  new_localvarliteral(ls, "(for control)");
  /* create declared variables */
  new_localvar(ls, indexname);
  while (testnext(ls, ',')) {
    new_localvar(ls, str_checkname(ls));
    nvars++;
  }
  checknext(ls, TK_IN);
  line = ls->linenumber;
  adjust_assign(ls, 3, explist(ls, &e), &e);
  luaK_checkstack(fs, 3);  /* extra space to call generator */
  forbody(ls, base, line, nvars - 3, 0);
}