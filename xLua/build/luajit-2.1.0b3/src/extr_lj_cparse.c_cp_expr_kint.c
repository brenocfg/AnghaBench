#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cts; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ CType ;
typedef  TYPE_2__ CPValue ;
typedef  TYPE_3__ CPState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_BADVAL ; 
 int /*<<< orphan*/  cp_err (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_expr_sub (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_isinteger (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_expr_kint(CPState *cp, CPValue *k)
{
  CType *ct;
  cp_expr_sub(cp, k, 0);
  ct = ctype_raw(cp->cts, k->id);
  if (!ctype_isinteger(ct->info)) cp_err(cp, LJ_ERR_BADVAL);
}