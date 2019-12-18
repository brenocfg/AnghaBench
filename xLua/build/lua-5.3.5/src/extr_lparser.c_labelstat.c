#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_1__* bl; } ;
struct TYPE_21__ {TYPE_12__* arr; } ;
struct TYPE_20__ {TYPE_2__* dyd; TYPE_5__* fs; } ;
struct TYPE_19__ {TYPE_4__ label; } ;
struct TYPE_18__ {int /*<<< orphan*/  nactvar; } ;
struct TYPE_17__ {int /*<<< orphan*/  nactvar; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ Labellist ;
typedef  TYPE_5__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_DBCOLON ; 
 scalar_t__ block_follow (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checknext (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkrepeated (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  findgotos (TYPE_3__*,TYPE_12__*) ; 
 int /*<<< orphan*/  luaK_getlabel (TYPE_5__*) ; 
 int newlabelentry (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skipnoopstat (TYPE_3__*) ; 

__attribute__((used)) static void labelstat (LexState *ls, TString *label, int line) {
  /* label -> '::' NAME '::' */
  FuncState *fs = ls->fs;
  Labellist *ll = &ls->dyd->label;
  int l;  /* index of new label being created */
  checkrepeated(fs, ll, label);  /* check for repeated labels */
  checknext(ls, TK_DBCOLON);  /* skip double colon */
  /* create new entry for this label */
  l = newlabelentry(ls, ll, label, line, luaK_getlabel(fs));
  skipnoopstat(ls);  /* skip other no-op statements */
  if (block_follow(ls, 0)) {  /* label is last no-op statement in the block? */
    /* assume that locals are already out of scope */
    ll->arr[l].nactvar = fs->bl->nactvar;
  }
  findgotos(ls, &ll->arr[l]);
}