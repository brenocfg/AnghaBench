#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_7__ {int /*<<< orphan*/  ctypeid; } ;
struct TYPE_6__ {int info; int size; } ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int CTF_BOOL ; 
 int CTF_FP ; 
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_INT64 ; 
 int /*<<< orphan*/  CTID_UINT64 ; 
 int CTINFO (int /*<<< orphan*/ ,int) ; 
 int CTMASK_NUM ; 
 int /*<<< orphan*/  CT_NUM ; 
 TYPE_5__* cdataV (int /*<<< orphan*/ *) ; 
 TYPE_1__* ctype_child (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ctype_isenum (int) ; 
 TYPE_1__* lj_ctype_rawref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CTypeID crec_bit64_type(CTState *cts, cTValue *tv)
{
  if (tviscdata(tv)) {
    CType *ct = lj_ctype_rawref(cts, cdataV(tv)->ctypeid);
    if (ctype_isenum(ct->info)) ct = ctype_child(cts, ct);
    if ((ct->info & (CTMASK_NUM|CTF_BOOL|CTF_FP|CTF_UNSIGNED)) ==
	CTINFO(CT_NUM, CTF_UNSIGNED) && ct->size == 8)
      return CTID_UINT64;  /* Use uint64_t, since it has the highest rank. */
    return CTID_INT64;  /* Otherwise use int64_t. */
  }
  return 0;  /* Use regular 32 bit ops. */
}