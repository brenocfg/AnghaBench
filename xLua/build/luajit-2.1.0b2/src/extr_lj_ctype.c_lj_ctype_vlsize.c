#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {int size; int /*<<< orphan*/  info; scalar_t__ sib; } ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;

/* Variables and functions */
 int CTSIZE_INVALID ; 
 scalar_t__ CT_FIELD ; 
 scalar_t__ ctype_cid (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ctype_hassize (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isstruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_isvlarray (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_raw (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ctype_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

CTSize lj_ctype_vlsize(CTState *cts, CType *ct, CTSize nelem)
{
  uint64_t xsz = 0;
  if (ctype_isstruct(ct->info)) {
    CTypeID arrid = 0, fid = ct->sib;
    xsz = ct->size;  /* Add the struct size. */
    while (fid) {
      CType *ctf = ctype_get(cts, fid);
      if (ctype_type(ctf->info) == CT_FIELD)
	arrid = ctype_cid(ctf->info);  /* Remember last field of VLS. */
      fid = ctf->sib;
    }
    ct = ctype_raw(cts, arrid);
  }
  lua_assert(ctype_isvlarray(ct->info));  /* Must be a VLA. */
  ct = ctype_rawchild(cts, ct);  /* Get array element. */
  lua_assert(ctype_hassize(ct->info));
  /* Calculate actual size of VLA and check for overflow. */
  xsz += (uint64_t)ct->size * nelem;
  return xsz < 0x80000000u ? (CTSize)xsz : CTSIZE_INVALID;
}