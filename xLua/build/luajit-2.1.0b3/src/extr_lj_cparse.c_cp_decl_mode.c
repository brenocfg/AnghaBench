#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {scalar_t__ tok; int /*<<< orphan*/  str; } ;
typedef  int CTSize ;
typedef  TYPE_1__ CPState ;
typedef  TYPE_2__ CPDecl ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CTOK_IDENT ; 
 int /*<<< orphan*/  MSIZEP ; 
 int /*<<< orphan*/  VSIZEP ; 
 int /*<<< orphan*/  cp_check (TYPE_1__*,char) ; 
 int /*<<< orphan*/  cp_next (TYPE_1__*) ; 
 int lj_fls (int) ; 
 char* strdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_decl_mode(CPState *cp, CPDecl *decl)
{
  cp_check(cp, '(');
  if (cp->tok == CTOK_IDENT) {
    const char *s = strdata(cp->str);
    CTSize sz = 0, vlen = 0;
    if (s[0] == '_' && s[1] == '_') s += 2;
    if (*s == 'V') {
      s++;
      vlen = *s++ - '0';
      if (*s >= '0' && *s <= '9')
	vlen = vlen*10 + (*s++ - '0');
    }
    switch (*s++) {
    case 'Q': sz = 1; break;
    case 'H': sz = 2; break;
    case 'S': sz = 4; break;
    case 'D': sz = 8; break;
    case 'T': sz = 16; break;
    case 'O': sz = 32; break;
    default: goto bad_size;
    }
    if (*s == 'I' || *s == 'F') {
      CTF_INSERT(decl->attr, MSIZEP, sz);
      if (vlen) CTF_INSERT(decl->attr, VSIZEP, lj_fls(vlen*sz));
    }
  bad_size:
    cp_next(cp);
  }
  cp_check(cp, ')');
}