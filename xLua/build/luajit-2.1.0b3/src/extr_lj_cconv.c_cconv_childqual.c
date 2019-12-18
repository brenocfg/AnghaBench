#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int info; int size; } ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTInfo ;

/* Variables and functions */
 scalar_t__ CTA_QUAL ; 
 int CTF_QUAL ; 
 scalar_t__ ctype_attrib (int) ; 
 TYPE_1__* ctype_child (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ctype_isattrib (int) ; 
 int /*<<< orphan*/  ctype_isenum (int) ; 

__attribute__((used)) static CType *cconv_childqual(CTState *cts, CType *ct, CTInfo *qual)
{
  ct = ctype_child(cts, ct);
  for (;;) {
    if (ctype_isattrib(ct->info)) {
      if (ctype_attrib(ct->info) == CTA_QUAL) *qual |= ct->size;
    } else if (!ctype_isenum(ct->info)) {
      break;
    }
    ct = ctype_child(cts, ct);
  }
  *qual |= (ct->info & CTF_QUAL);
  return ct;
}