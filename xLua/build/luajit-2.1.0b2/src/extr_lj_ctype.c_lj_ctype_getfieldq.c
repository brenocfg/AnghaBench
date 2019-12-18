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
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  info; int /*<<< orphan*/  name; scalar_t__ sib; } ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  scalar_t__ CTSize ;
typedef  scalar_t__ CTInfo ;

/* Variables and functions */
 scalar_t__ CTA_QUAL ; 
 int /*<<< orphan*/  CTA_SUBTYPE ; 
 scalar_t__ ctype_attrib (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_child (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctype_isattrib (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isxattrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gcref (int /*<<< orphan*/ ) ; 
 scalar_t__ obj2gco (int /*<<< orphan*/ *) ; 

CType *lj_ctype_getfieldq(CTState *cts, CType *ct, GCstr *name, CTSize *ofs,
			  CTInfo *qual)
{
  while (ct->sib) {
    ct = ctype_get(cts, ct->sib);
    if (gcref(ct->name) == obj2gco(name)) {
      *ofs = ct->size;
      return ct;
    }
    if (ctype_isxattrib(ct->info, CTA_SUBTYPE)) {
      CType *fct, *cct = ctype_child(cts, ct);
      CTInfo q = 0;
      while (ctype_isattrib(cct->info)) {
	if (ctype_attrib(cct->info) == CTA_QUAL) q |= cct->size;
	cct = ctype_child(cts, cct);
      }
      fct = lj_ctype_getfieldq(cts, cct, name, ofs, qual);
      if (fct) {
	if (qual) *qual |= q;
	*ofs += ct->size;
	return fct;
      }
    }
  }
  return NULL;  /* Not found. */
}