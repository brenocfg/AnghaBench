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
struct TYPE_5__ {size_t top; size_t pos; TYPE_1__* stack; int /*<<< orphan*/  cp; } ;
struct TYPE_4__ {scalar_t__ next; int /*<<< orphan*/  name; scalar_t__ sib; int /*<<< orphan*/  size; int /*<<< orphan*/  info; } ;
typedef  scalar_t__ CTypeID1 ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  int /*<<< orphan*/  CTInfo ;
typedef  size_t CPDeclIdx ;
typedef  TYPE_2__ CPDecl ;

/* Variables and functions */
 size_t CPARSE_MAX_DECLSTACK ; 
 int /*<<< orphan*/  LJ_ERR_XLEVELS ; 
 int /*<<< orphan*/  cp_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CPDeclIdx cp_add(CPDecl *decl, CTInfo info, CTSize size)
{
  CPDeclIdx top = decl->top;
  if (top >= CPARSE_MAX_DECLSTACK) cp_err(decl->cp, LJ_ERR_XLEVELS);
  decl->stack[top].info = info;
  decl->stack[top].size = size;
  decl->stack[top].sib = 0;
  setgcrefnull(decl->stack[top].name);
  decl->stack[top].next = decl->stack[decl->pos].next;
  decl->stack[decl->pos].next = (CTypeID1)top;
  decl->top = top+1;
  return top;
}