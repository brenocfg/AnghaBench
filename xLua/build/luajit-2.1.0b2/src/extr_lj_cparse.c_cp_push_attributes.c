#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t pos; int fattr; int attr; int mode; TYPE_1__* stack; } ;
struct TYPE_5__ {int info; } ;
typedef  TYPE_1__ CType ;
typedef  TYPE_2__ CPDecl ;

/* Variables and functions */
 int CPARSE_MODE_FIELD ; 
 int /*<<< orphan*/  CTATTRIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTA_ALIGN ; 
 int CTFP_ALIGNED ; 
 int CTFP_CCONV ; 
 int CTF_VARARG ; 
 int /*<<< orphan*/  CTINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CTMASK_CID ; 
 int CTMASK_NUM ; 
 int /*<<< orphan*/  CT_ATTRIB ; 
 int /*<<< orphan*/  cp_push (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_align (int) ; 
 scalar_t__ ctype_isfunc (int) ; 

__attribute__((used)) static void cp_push_attributes(CPDecl *decl)
{
  CType *ct = &decl->stack[decl->pos];
  if (ctype_isfunc(ct->info)) {  /* Ok to modify in-place. */
#if LJ_TARGET_X86
    if ((decl->fattr & CTFP_CCONV))
      ct->info = (ct->info & (CTMASK_NUM|CTF_VARARG|CTMASK_CID)) +
		 (decl->fattr & ~CTMASK_CID);
#endif
  } else {
    if ((decl->attr & CTFP_ALIGNED) && !(decl->mode & CPARSE_MODE_FIELD))
      cp_push(decl, CTINFO(CT_ATTRIB, CTATTRIB(CTA_ALIGN)),
	      ctype_align(decl->attr));
  }
}