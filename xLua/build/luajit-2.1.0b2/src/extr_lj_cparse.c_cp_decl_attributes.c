#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  fattr; } ;
struct TYPE_14__ {int tok; TYPE_1__* ct; } ;
struct TYPE_13__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ CPState ;
typedef  TYPE_3__ CPDecl ;

/* Variables and functions */
 int /*<<< orphan*/  CCONV ; 
 int /*<<< orphan*/  CTFP_CCONV ; 
 int /*<<< orphan*/  CTF_CONST ; 
 int /*<<< orphan*/  CTF_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_VOLATILE ; 
#define  CTOK_ASM 136 
#define  CTOK_ATTRIBUTE 135 
#define  CTOK_CCDECL 134 
#define  CTOK_CONST 133 
#define  CTOK_DECLSPEC 132 
#define  CTOK_EXTENSION 131 
#define  CTOK_PTRSZ 130 
#define  CTOK_RESTRICT 129 
#define  CTOK_VOLATILE 128 
 int /*<<< orphan*/  MSIZEP ; 
 int /*<<< orphan*/  cp_decl_asm (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_decl_gccattribute (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_decl_msvcattribute (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_next (TYPE_2__*) ; 

__attribute__((used)) static void cp_decl_attributes(CPState *cp, CPDecl *decl)
{
  for (;;) {
    switch (cp->tok) {
    case CTOK_CONST: decl->attr |= CTF_CONST; break;
    case CTOK_VOLATILE: decl->attr |= CTF_VOLATILE; break;
    case CTOK_RESTRICT: break;  /* Ignore. */
    case CTOK_EXTENSION: break;  /* Ignore. */
    case CTOK_ATTRIBUTE: cp_decl_gccattribute(cp, decl); continue;
    case CTOK_ASM: cp_decl_asm(cp, decl); continue;
    case CTOK_DECLSPEC: cp_decl_msvcattribute(cp, decl); continue;
    case CTOK_CCDECL:
#if LJ_TARGET_X86
      CTF_INSERT(decl->fattr, CCONV, cp->ct->size);
      decl->fattr |= CTFP_CCONV;
#endif
      break;
    case CTOK_PTRSZ:
#if LJ_64
      CTF_INSERT(decl->attr, MSIZEP, cp->ct->size);
#endif
      break;
    default: return;
    }
    cp_next(cp);
  }
}