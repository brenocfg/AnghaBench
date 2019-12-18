#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  array; } ;
struct TYPE_9__ {int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ MSize ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  bcread_ktabk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bcread_uleb128 (TYPE_1__*) ; 
 int /*<<< orphan*/  hsize2hbits (scalar_t__) ; 
 TYPE_2__* lj_tab_new (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_set (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GCtab *bcread_ktab(LexState *ls)
{
  MSize narray = bcread_uleb128(ls);
  MSize nhash = bcread_uleb128(ls);
  GCtab *t = lj_tab_new(ls->L, narray, hsize2hbits(nhash));
  if (narray) {  /* Read array entries. */
    MSize i;
    TValue *o = tvref(t->array);
    for (i = 0; i < narray; i++, o++)
      bcread_ktabk(ls, o);
  }
  if (nhash) {  /* Read hash entries. */
    MSize i;
    for (i = 0; i < nhash; i++) {
      TValue key;
      bcread_ktabk(ls, &key);
      lua_assert(!tvisnil(&key));
      bcread_ktabk(ls, lj_tab_set(ls->L, t, &key));
    }
  }
  return t;
}