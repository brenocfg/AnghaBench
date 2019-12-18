#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_17__ {size_t* uvmap; int /*<<< orphan*/  kt; TYPE_1__* bcbase; } ;
struct TYPE_16__ {int len; } ;
struct TYPE_15__ {int /*<<< orphan*/  L; TYPE_2__* vstack; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ GCstr ;
typedef  TYPE_5__ FuncState ;
typedef  size_t BCPos ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
#define  BC_GGET 130 
#define  BC_MOV 129 
#define  BC_UGET 128 
 size_t bc_d (int /*<<< orphan*/ ) ; 
 int bc_op (int /*<<< orphan*/ ) ; 
 TYPE_4__* gco2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_str_newlit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdata (TYPE_4__*) ; 
 int /*<<< orphan*/  tvhaskslot (int /*<<< orphan*/ *) ; 
 size_t tvkslot (int /*<<< orphan*/ *) ; 
 TYPE_6__ var_get (TYPE_3__*,TYPE_5__*,size_t) ; 

__attribute__((used)) static int predict_next(LexState *ls, FuncState *fs, BCPos pc)
{
  BCIns ins = fs->bcbase[pc].ins;
  GCstr *name;
  cTValue *o;
  switch (bc_op(ins)) {
  case BC_MOV:
    name = gco2str(gcref(var_get(ls, fs, bc_d(ins)).name));
    break;
  case BC_UGET:
    name = gco2str(gcref(ls->vstack[fs->uvmap[bc_d(ins)]].name));
    break;
  case BC_GGET:
    /* There's no inverse index (yet), so lookup the strings. */
    o = lj_tab_getstr(fs->kt, lj_str_newlit(ls->L, "pairs"));
    if (o && tvhaskslot(o) && tvkslot(o) == bc_d(ins))
      return 1;
    o = lj_tab_getstr(fs->kt, lj_str_newlit(ls->L, "next"));
    if (o && tvhaskslot(o) && tvkslot(o) == bc_d(ins))
      return 1;
    return 0;
  default:
    return 0;
  }
  return (name->len == 5 && !strcmp(strdata(name), "pairs")) ||
	 (name->len == 4 && !strcmp(strdata(name), "next"));
}