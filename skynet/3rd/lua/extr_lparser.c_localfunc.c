#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  info; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
struct TYPE_17__ {int /*<<< orphan*/  startpc; } ;
struct TYPE_16__ {int /*<<< orphan*/  pc; } ;
struct TYPE_15__ {int /*<<< orphan*/  linenumber; TYPE_4__* fs; } ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  adjustlocalvars (TYPE_3__*,int) ; 
 int /*<<< orphan*/  body (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* getlocvar (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_localvar (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_checkname (TYPE_3__*) ; 

__attribute__((used)) static void localfunc (LexState *ls) {
  expdesc b;
  FuncState *fs = ls->fs;
  new_localvar(ls, str_checkname(ls));  /* new local variable */
  adjustlocalvars(ls, 1);  /* enter its scope */
  body(ls, &b, 0, ls->linenumber);  /* function created in next register */
  /* debug information will only see the variable after this point! */
  getlocvar(fs, b.u.info)->startpc = fs->pc;
}