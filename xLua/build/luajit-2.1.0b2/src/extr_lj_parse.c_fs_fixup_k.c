#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ptrdiff_t ;
typedef  scalar_t__ lua_Number ;
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  L; TYPE_2__* kt; int /*<<< orphan*/  nkgc; int /*<<< orphan*/  nkn; } ;
struct TYPE_13__ {int /*<<< orphan*/  sizekgc; int /*<<< orphan*/  sizekn; int /*<<< orphan*/  k; } ;
struct TYPE_12__ {size_t asize; size_t hmask; int /*<<< orphan*/  node; int /*<<< orphan*/  array; } ;
struct TYPE_11__ {int /*<<< orphan*/  key; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Node ;
typedef  size_t MSize ;
typedef  TYPE_2__ GCtab ;
typedef  TYPE_3__ GCproto ;
typedef  int /*<<< orphan*/  GCobj ;
typedef  int /*<<< orphan*/  GCRef ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 scalar_t__ BCMAX_D ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  checklimitgt (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  fs_fixup_uv2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2pt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_gc_objbarrier (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lj_num2int (scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_1__* noderef (int /*<<< orphan*/ ) ; 
 scalar_t__ numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ tvhaskslot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvismzero (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisproto (int /*<<< orphan*/ *) ; 
 size_t tvkslot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_fixup_k(FuncState *fs, GCproto *pt, void *kptr)
{
  GCtab *kt;
  TValue *array;
  Node *node;
  MSize i, hmask;
  checklimitgt(fs, fs->nkn, BCMAX_D+1, "constants");
  checklimitgt(fs, fs->nkgc, BCMAX_D+1, "constants");
  setmref(pt->k, kptr);
  pt->sizekn = fs->nkn;
  pt->sizekgc = fs->nkgc;
  kt = fs->kt;
  array = tvref(kt->array);
  for (i = 0; i < kt->asize; i++)
    if (tvhaskslot(&array[i])) {
      TValue *tv = &((TValue *)kptr)[tvkslot(&array[i])];
      if (LJ_DUALNUM)
	setintV(tv, (int32_t)i);
      else
	setnumV(tv, (lua_Number)i);
    }
  node = noderef(kt->node);
  hmask = kt->hmask;
  for (i = 0; i <= hmask; i++) {
    Node *n = &node[i];
    if (tvhaskslot(&n->val)) {
      ptrdiff_t kidx = (ptrdiff_t)tvkslot(&n->val);
      lua_assert(!tvisint(&n->key));
      if (tvisnum(&n->key)) {
	TValue *tv = &((TValue *)kptr)[kidx];
	if (LJ_DUALNUM) {
	  lua_Number nn = numV(&n->key);
	  int32_t k = lj_num2int(nn);
	  lua_assert(!tvismzero(&n->key));
	  if ((lua_Number)k == nn)
	    setintV(tv, k);
	  else
	    *tv = n->key;
	} else {
	  *tv = n->key;
	}
      } else {
	GCobj *o = gcV(&n->key);
	setgcref(((GCRef *)kptr)[~kidx], o);
	lj_gc_objbarrier(fs->L, pt, o);
	if (tvisproto(&n->key))
	  fs_fixup_uv2(fs, gco2pt(o));
      }
    }
  }
}