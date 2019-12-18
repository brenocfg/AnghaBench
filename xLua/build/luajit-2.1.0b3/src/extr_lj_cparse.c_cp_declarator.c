#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int attr; int mode; int /*<<< orphan*/  bits; int /*<<< orphan*/  nameid; int /*<<< orphan*/  name; int /*<<< orphan*/  pos; } ;
struct TYPE_21__ {int /*<<< orphan*/  id; } ;
struct TYPE_22__ {scalar_t__ depth; char tok; TYPE_1__ val; int /*<<< orphan*/  str; } ;
typedef  int CTSize ;
typedef  int CTInfo ;
typedef  TYPE_2__ CPState ;
typedef  int /*<<< orphan*/  CPDeclIdx ;
typedef  TYPE_3__ CPDecl ;

/* Variables and functions */
 scalar_t__ CPARSE_MAX_DECLDEPTH ; 
 int CPARSE_MODE_ABSTRACT ; 
 int CPARSE_MODE_DIRECT ; 
 int CPARSE_MODE_FIELD ; 
 int /*<<< orphan*/  CTALIGN (int) ; 
 int /*<<< orphan*/  CTALIGN_PTR ; 
 int CTF_QUAL ; 
 int CTF_REF ; 
 int CTINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CTINFO_REF (int /*<<< orphan*/ ) ; 
 int CTMASK_MSIZEP ; 
 char CTOK_ANDAND ; 
 char CTOK_EOF ; 
 char CTOK_IDENT ; 
 int CTSHIFT_MSIZEP ; 
 int CTSIZE_PTR ; 
 int /*<<< orphan*/  CT_PTR ; 
 int /*<<< orphan*/  LJ_ERR_XLEVELS ; 
 int /*<<< orphan*/  cp_check (TYPE_2__*,char) ; 
 int /*<<< orphan*/  cp_decl_array (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_decl_attributes (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_decl_func (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_err (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_err_token (TYPE_2__*,char) ; 
 int /*<<< orphan*/  cp_expr_ksize (TYPE_2__*) ; 
 scalar_t__ cp_istypedecl (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_next (TYPE_2__*) ; 
 scalar_t__ cp_opt (TYPE_2__*,char) ; 
 int /*<<< orphan*/  cp_push (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  cp_push_attributes (TYPE_3__*) ; 
 int ctype_msizeP (int) ; 

__attribute__((used)) static void cp_declarator(CPState *cp, CPDecl *decl)
{
  if (++cp->depth > CPARSE_MAX_DECLDEPTH) cp_err(cp, LJ_ERR_XLEVELS);

  for (;;) {  /* Head of declarator. */
    if (cp_opt(cp, '*')) {  /* Pointer. */
      CTSize sz;
      CTInfo info;
      cp_decl_attributes(cp, decl);
      sz = CTSIZE_PTR;
      info = CTINFO(CT_PTR, CTALIGN_PTR);
#if LJ_64
      if (ctype_msizeP(decl->attr) == 4) {
	sz = 4;
	info = CTINFO(CT_PTR, CTALIGN(2));
      }
#endif
      info += (decl->attr & (CTF_QUAL|CTF_REF));
      decl->attr &= ~(CTF_QUAL|(CTMASK_MSIZEP<<CTSHIFT_MSIZEP));
      cp_push(decl, info, sz);
    } else if (cp_opt(cp, '&') || cp_opt(cp, CTOK_ANDAND)) {  /* Reference. */
      decl->attr &= ~(CTF_QUAL|(CTMASK_MSIZEP<<CTSHIFT_MSIZEP));
      cp_push(decl, CTINFO_REF(0), CTSIZE_PTR);
    } else {
      break;
    }
  }

  if (cp_opt(cp, '(')) {  /* Inner declarator. */
    CPDeclIdx pos;
    cp_decl_attributes(cp, decl);
    /* Resolve ambiguity between inner declarator and 1st function parameter. */
    if ((decl->mode & CPARSE_MODE_ABSTRACT) &&
	(cp->tok == ')' || cp_istypedecl(cp))) goto func_decl;
    pos = decl->pos;
    cp_declarator(cp, decl);
    cp_check(cp, ')');
    decl->pos = pos;
  } else if (cp->tok == CTOK_IDENT) {  /* Direct declarator. */
    if (!(decl->mode & CPARSE_MODE_DIRECT)) cp_err_token(cp, CTOK_EOF);
    decl->name = cp->str;
    decl->nameid = cp->val.id;
    cp_next(cp);
  } else {  /* Abstract declarator. */
    if (!(decl->mode & CPARSE_MODE_ABSTRACT)) cp_err_token(cp, CTOK_IDENT);
  }

  for (;;) {  /* Tail of declarator. */
    if (cp_opt(cp, '[')) {  /* Array. */
      cp_decl_array(cp, decl);
    } else if (cp_opt(cp, '(')) {  /* Function. */
    func_decl:
      cp_decl_func(cp, decl);
    } else {
      break;
    }
  }

  if ((decl->mode & CPARSE_MODE_FIELD) && cp_opt(cp, ':'))  /* Field width. */
    decl->bits = cp_expr_ksize(cp);

  /* Process postfix attributes. */
  cp_decl_attributes(cp, decl);
  cp_push_attributes(decl);

  cp->depth--;
}