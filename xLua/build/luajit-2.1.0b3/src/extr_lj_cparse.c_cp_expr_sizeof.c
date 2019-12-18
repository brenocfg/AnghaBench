#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  cts; } ;
struct TYPE_14__ {scalar_t__ id; unsigned int u32; } ;
typedef  scalar_t__ CTSize ;
typedef  int /*<<< orphan*/  CTInfo ;
typedef  TYPE_1__ CPValue ;
typedef  TYPE_2__ CPState ;

/* Variables and functions */
 scalar_t__ CTID_A_CCHAR ; 
 scalar_t__ CTID_UINT32 ; 
 scalar_t__ CTSIZE_INVALID ; 
 int /*<<< orphan*/  LJ_ERR_FFI_INVSIZE ; 
 int /*<<< orphan*/  cp_check (TYPE_2__*,char) ; 
 scalar_t__ cp_decl_abstract (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_err (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_expr_comma (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_expr_unary (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ cp_istypedecl (TYPE_2__*) ; 
 scalar_t__ cp_opt (TYPE_2__*,char) ; 
 unsigned int ctype_align (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_info (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void cp_expr_sizeof(CPState *cp, CPValue *k, int wantsz)
{
  CTSize sz;
  CTInfo info;
  if (cp_opt(cp, '(')) {
    if (cp_istypedecl(cp))
      k->id = cp_decl_abstract(cp);
    else
      cp_expr_comma(cp, k);
    cp_check(cp, ')');
  } else {
    cp_expr_unary(cp, k);
  }
  info = lj_ctype_info(cp->cts, k->id, &sz);
  if (wantsz) {
    if (sz != CTSIZE_INVALID)
      k->u32 = sz;
    else if (k->id != CTID_A_CCHAR)  /* Special case for sizeof("string"). */
      cp_err(cp, LJ_ERR_FFI_INVSIZE);
  } else {
    k->u32 = 1u << ctype_align(info);
  }
  k->id = CTID_UINT32;  /* Really size_t. */
}