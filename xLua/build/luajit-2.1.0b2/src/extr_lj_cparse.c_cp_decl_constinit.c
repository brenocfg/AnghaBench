#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  cts; } ;
struct TYPE_13__ {int u32; } ;
struct TYPE_12__ {int info; int size; } ;
typedef  int CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int CTSize ;
typedef  int CTInfo ;
typedef  TYPE_2__ CPValue ;
typedef  TYPE_3__ CPState ;

/* Variables and functions */
 int CTF_CONST ; 
 int CTF_UNSIGNED ; 
 int CTINFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CT_CONSTVAL ; 
 int /*<<< orphan*/  LJ_ERR_FFI_INVTYPE ; 
 int /*<<< orphan*/  cp_check (TYPE_3__*,char) ; 
 int /*<<< orphan*/  cp_err (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_expr_sub (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ctype_cid (int) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ctype_isattrib (int) ; 
 int /*<<< orphan*/  ctype_isinteger (int) ; 
 int lj_ctype_new (int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static CTypeID cp_decl_constinit(CPState *cp, CType **ctp, CTypeID ctypeid)
{
  CType *ctt = ctype_get(cp->cts, ctypeid);
  CTInfo info;
  CTSize size;
  CPValue k;
  CTypeID constid;
  while (ctype_isattrib(ctt->info)) {  /* Skip attributes. */
    ctypeid = ctype_cid(ctt->info);  /* Update ID, too. */
    ctt = ctype_get(cp->cts, ctypeid);
  }
  info = ctt->info;
  size = ctt->size;
  if (!ctype_isinteger(info) || !(info & CTF_CONST) || size > 4)
    cp_err(cp, LJ_ERR_FFI_INVTYPE);
  cp_check(cp, '=');
  cp_expr_sub(cp, &k, 0);
  constid = lj_ctype_new(cp->cts, ctp);
  (*ctp)->info = CTINFO(CT_CONSTVAL, CTF_CONST|ctypeid);
  k.u32 <<= 8*(4-size);
  if ((info & CTF_UNSIGNED))
    k.u32 >>= 8*(4-size);
  else
    k.u32 = (uint32_t)((int32_t)k.u32 >> 8*(4-size));
  (*ctp)->size = k.u32;
  return constid;
}