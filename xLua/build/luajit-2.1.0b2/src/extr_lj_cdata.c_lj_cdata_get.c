#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 scalar_t__ CTSIZE_PTR ; 
 int /*<<< orphan*/  cdata_getconst (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ctype_child (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ctype_cid (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isattrib (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isbitfield (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isconstval (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isfield (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_ispointer (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isref (int /*<<< orphan*/ ) ; 
 int lj_cconv_tv_bf (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lj_cconv_tv_ct (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

int lj_cdata_get(CTState *cts, CType *s, TValue *o, uint8_t *sp)
{
  CTypeID sid;

  if (ctype_isconstval(s->info)) {
    cdata_getconst(cts, o, s);
    return 0;  /* No GC step needed. */
  } else if (ctype_isbitfield(s->info)) {
    return lj_cconv_tv_bf(cts, s, o, sp);
  }

  /* Get child type of pointer/array/field. */
  lua_assert(ctype_ispointer(s->info) || ctype_isfield(s->info));
  sid = ctype_cid(s->info);
  s = ctype_get(cts, sid);

  /* Resolve reference for field. */
  if (ctype_isref(s->info)) {
    lua_assert(s->size == CTSIZE_PTR);
    sp = *(uint8_t **)sp;
    sid = ctype_cid(s->info);
    s = ctype_get(cts, sid);
  }

  /* Skip attributes. */
  while (ctype_isattrib(s->info))
    s = ctype_child(cts, s);

  return lj_cconv_tv_ct(cts, s, sid, o, sp);
}