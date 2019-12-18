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
struct TYPE_7__ {int info; scalar_t__ size; scalar_t__ sib; } ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int CTF_VARARG ; 
 scalar_t__ CTSIZE_PTR ; 
 scalar_t__ LJ_64 ; 
 int LUA_MINSTACK ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ctype_isattrib (int) ; 
 scalar_t__ ctype_isenum (int) ; 
 int /*<<< orphan*/  ctype_isfield (int) ; 
 scalar_t__ ctype_isfunc (int) ; 
 scalar_t__ ctype_isnum (int) ; 
 scalar_t__ ctype_isptr (int) ; 
 scalar_t__ ctype_isvoid (int) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CType *callback_checkfunc(CTState *cts, CType *ct)
{
  int narg = 0;
  if (!ctype_isptr(ct->info) || (LJ_64 && ct->size != CTSIZE_PTR))
    return NULL;
  ct = ctype_rawchild(cts, ct);
  if (ctype_isfunc(ct->info)) {
    CType *ctr = ctype_rawchild(cts, ct);
    CTypeID fid = ct->sib;
    if (!(ctype_isvoid(ctr->info) || ctype_isenum(ctr->info) ||
	  ctype_isptr(ctr->info) || (ctype_isnum(ctr->info) && ctr->size <= 8)))
      return NULL;
    if ((ct->info & CTF_VARARG))
      return NULL;
    while (fid) {
      CType *ctf = ctype_get(cts, fid);
      if (!ctype_isattrib(ctf->info)) {
	CType *cta;
	lua_assert(ctype_isfield(ctf->info));
	cta = ctype_rawchild(cts, ctf);
	if (!(ctype_isenum(cta->info) || ctype_isptr(cta->info) ||
	      (ctype_isnum(cta->info) && cta->size <= 8)) ||
	    ++narg >= LUA_MINSTACK-3)
	  return NULL;
      }
      fid = ctf->sib;
    }
    return ct;
  }
  return NULL;
}