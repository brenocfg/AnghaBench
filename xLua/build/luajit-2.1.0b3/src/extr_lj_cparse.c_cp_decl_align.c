#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {char tok; } ;
typedef  int CTSize ;
typedef  TYPE_1__ CPState ;
typedef  TYPE_2__ CPDecl ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN ; 
 int /*<<< orphan*/  CTFP_ALIGNED ; 
 int /*<<< orphan*/  CTF_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cp_decl_sizeattr (TYPE_1__*) ; 
 int lj_fls (int) ; 

__attribute__((used)) static void cp_decl_align(CPState *cp, CPDecl *decl)
{
  CTSize al = 4;  /* Unspecified alignment is 16 bytes. */
  if (cp->tok == '(') {
    al = cp_decl_sizeattr(cp);
    al = al ? lj_fls(al) : 0;
  }
  CTF_INSERT(decl->attr, ALIGN, al);
  decl->attr |= CTFP_ALIGNED;
}