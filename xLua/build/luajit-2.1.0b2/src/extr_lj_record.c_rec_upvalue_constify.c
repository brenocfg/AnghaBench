#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_11__ {int size; int /*<<< orphan*/  info; } ;
struct TYPE_10__ {int marked; int /*<<< orphan*/  ctypeid; } ;
struct TYPE_9__ {scalar_t__ immutable; } ;
typedef  TYPE_1__ GCupval ;
typedef  TYPE_2__ GCcdata ;
typedef  TYPE_3__ CType ;

/* Variables and functions */
 int /*<<< orphan*/  J2G (int /*<<< orphan*/ *) ; 
 int LJ_GC_CDATA_FIN ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_2__* cdataV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdataisv (TYPE_2__*) ; 
 int /*<<< orphan*/  ctype_ctsG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_hassize (int /*<<< orphan*/ ) ; 
 TYPE_3__* ctype_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisthread (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisudata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uvval (TYPE_1__*) ; 

__attribute__((used)) static int rec_upvalue_constify(jit_State *J, GCupval *uvp)
{
  if (uvp->immutable) {
    cTValue *o = uvval(uvp);
    /* Don't constify objects that may retain large amounts of memory. */
#if LJ_HASFFI
    if (tviscdata(o)) {
      GCcdata *cd = cdataV(o);
      if (!cdataisv(cd) && !(cd->marked & LJ_GC_CDATA_FIN)) {
	CType *ct = ctype_raw(ctype_ctsG(J2G(J)), cd->ctypeid);
	if (!ctype_hassize(ct->info) || ct->size <= 16)
	  return 1;
      }
      return 0;
    }
#else
    UNUSED(J);
#endif
    if (!(tvistab(o) || tvisudata(o) || tvisthread(o)))
      return 1;
  }
  return 0;
}