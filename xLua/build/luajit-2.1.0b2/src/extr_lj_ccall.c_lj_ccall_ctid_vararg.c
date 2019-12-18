#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_5__ {int ctypeid; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  info; } ;
typedef  int CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int CTALIGN_PTR ; 
 int CTID_BOOL ; 
 int CTID_DOUBLE ; 
 int CTID_P_CCHAR ; 
 int CTID_P_VOID ; 
 int /*<<< orphan*/  CTINFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 int /*<<< orphan*/  CT_PTR ; 
 TYPE_3__* cdataV (int /*<<< orphan*/ *) ; 
 int ctype_cid (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ctype_isfp (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isrefarray (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isstruct (int /*<<< orphan*/ ) ; 
 int lj_ctype_intern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tvisbool (int /*<<< orphan*/ *) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnumber (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

CTypeID lj_ccall_ctid_vararg(CTState *cts, cTValue *o)
{
  if (tvisnumber(o)) {
    return CTID_DOUBLE;
  } else if (tviscdata(o)) {
    CTypeID id = cdataV(o)->ctypeid;
    CType *s = ctype_get(cts, id);
    if (ctype_isrefarray(s->info)) {
      return lj_ctype_intern(cts,
	       CTINFO(CT_PTR, CTALIGN_PTR|ctype_cid(s->info)), CTSIZE_PTR);
    } else if (ctype_isstruct(s->info) || ctype_isfunc(s->info)) {
      /* NYI: how to pass a struct by value in a vararg argument? */
      return lj_ctype_intern(cts, CTINFO(CT_PTR, CTALIGN_PTR|id), CTSIZE_PTR);
    } else if (ctype_isfp(s->info) && s->size == sizeof(float)) {
      return CTID_DOUBLE;
    } else {
      return id;
    }
  } else if (tvisstr(o)) {
    return CTID_P_CCHAR;
  } else if (tvisbool(o)) {
    return CTID_BOOL;
  } else {
    return CTID_P_VOID;
  }
}