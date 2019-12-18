#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int info; int /*<<< orphan*/  cts; } ;
typedef  TYPE_1__ CType ;
typedef  int CTSize ;
typedef  int CTInfo ;
typedef  TYPE_1__ CPState ;

/* Variables and functions */
 int CTFP_ALIGNED ; 
 int CTF_VECTOR ; 
 int /*<<< orphan*/  UNUSED (TYPE_1__*) ; 
 int ctype_align (int) ; 
 scalar_t__ ctype_isarray (int) ; 
 scalar_t__ ctype_isenum (int) ; 
 scalar_t__ ctype_isnum (int) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static CTSize cp_field_align(CPState *cp, CType *ct, CTInfo info)
{
  CTSize align = ctype_align(info);
  UNUSED(cp); UNUSED(ct);
#if (LJ_TARGET_X86 && !LJ_ABI_WIN) || (LJ_TARGET_ARM && __APPLE__)
  /* The SYSV i386 and iOS ABIs limit alignment of non-vector fields to 2^2. */
  if (align > 2 && !(info & CTFP_ALIGNED)) {
    if (ctype_isarray(info) && !(info & CTF_VECTOR)) {
      do {
	ct = ctype_rawchild(cp->cts, ct);
	info = ct->info;
      } while (ctype_isarray(info) && !(info & CTF_VECTOR));
    }
    if (ctype_isnum(info) || ctype_isenum(info))
      align = 2;
  }
#endif
  return align;
}