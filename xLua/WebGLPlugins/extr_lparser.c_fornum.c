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
struct TYPE_14__ {int freereg; } ;
struct TYPE_13__ {TYPE_2__* fs; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  checknext (TYPE_1__*,char) ; 
 int /*<<< orphan*/  exp1 (TYPE_1__*) ; 
 int /*<<< orphan*/  forbody (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  luaK_codek (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_intK (TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_2__*,int) ; 
 int /*<<< orphan*/  new_localvar (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_localvarliteral (TYPE_1__*,char*) ; 
 scalar_t__ testnext (TYPE_1__*,char) ; 

__attribute__((used)) static void fornum (LexState *ls, TString *varname, int line) {
  /* fornum -> NAME = exp1,exp1[,exp1] forbody */
  FuncState *fs = ls->fs;
  int base = fs->freereg;
  new_localvarliteral(ls, "(for index)");
  new_localvarliteral(ls, "(for limit)");
  new_localvarliteral(ls, "(for step)");
  new_localvar(ls, varname);
  checknext(ls, '=');
  exp1(ls);  /* initial value */
  checknext(ls, ',');
  exp1(ls);  /* limit */
  if (testnext(ls, ','))
    exp1(ls);  /* optional step */
  else {  /* default step = 1 */
    luaK_codek(fs, fs->freereg, luaK_intK(fs, 1));
    luaK_reserveregs(fs, 1);
  }
  forbody(ls, base, line, 1, 1);
}