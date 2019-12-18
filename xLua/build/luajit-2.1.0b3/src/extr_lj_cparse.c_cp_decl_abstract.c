#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  int /*<<< orphan*/  CPState ;
typedef  TYPE_1__ CPDecl ;

/* Variables and functions */
 int /*<<< orphan*/  CPARSE_MODE_ABSTRACT ; 
 int /*<<< orphan*/  cp_decl_intern (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_decl_spec (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_declarator (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static CTypeID cp_decl_abstract(CPState *cp)
{
  CPDecl decl;
  cp_decl_spec(cp, &decl, 0);
  decl.mode = CPARSE_MODE_ABSTRACT;
  cp_declarator(cp, &decl);
  return cp_decl_intern(cp, &decl);
}