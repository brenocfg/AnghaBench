#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pos; int specpos; int top; int /*<<< orphan*/ * redir; int /*<<< orphan*/ * name; int /*<<< orphan*/  specfattr; int /*<<< orphan*/  fattr; int /*<<< orphan*/  specattr; int /*<<< orphan*/  attr; TYPE_1__* stack; } ;
struct TYPE_4__ {scalar_t__ next; } ;
typedef  TYPE_2__ CPDecl ;

/* Variables and functions */

__attribute__((used)) static void cp_decl_reset(CPDecl *decl)
{
  decl->pos = decl->specpos;
  decl->top = decl->specpos+1;
  decl->stack[decl->specpos].next = 0;
  decl->attr = decl->specattr;
  decl->fattr = decl->specfattr;
  decl->name = NULL;
  decl->redir = NULL;
}