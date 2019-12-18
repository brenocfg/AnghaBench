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
struct TYPE_7__ {char tok; } ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  int /*<<< orphan*/  CTInfo ;
typedef  TYPE_1__ CPState ;
typedef  int /*<<< orphan*/  CPDecl ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_VLA ; 
 int /*<<< orphan*/  CTINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTSIZE_INVALID ; 
 int /*<<< orphan*/  CT_ARRAY ; 
 int /*<<< orphan*/  cp_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_check (TYPE_1__*,char) ; 
 int /*<<< orphan*/  cp_decl_attributes (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_expr_ksize (TYPE_1__*) ; 
 scalar_t__ cp_opt (TYPE_1__*,char) ; 

__attribute__((used)) static void cp_decl_array(CPState *cp, CPDecl *decl)
{
  CTInfo info = CTINFO(CT_ARRAY, 0);
  CTSize nelem = CTSIZE_INVALID;  /* Default size for a[] or a[?]. */
  cp_decl_attributes(cp, decl);
  if (cp_opt(cp, '?'))
    info |= CTF_VLA;  /* Create variable-length array a[?]. */
  else if (cp->tok != ']')
    nelem = cp_expr_ksize(cp);
  cp_check(cp, ']');
  cp_add(decl, info, nelem);
}