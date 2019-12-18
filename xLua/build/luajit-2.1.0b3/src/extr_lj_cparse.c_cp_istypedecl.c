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
struct TYPE_5__ {char tok; TYPE_1__* ct; } ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ CPState ;

/* Variables and functions */
 char CTOK_FIRSTDECL ; 
 char CTOK_IDENT ; 
 char CTOK_LASTDECL ; 
 scalar_t__ ctype_istypedef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp_istypedecl(CPState *cp)
{
  if (cp->tok >= CTOK_FIRSTDECL && cp->tok <= CTOK_LASTDECL) return 1;
  if (cp->tok == CTOK_IDENT && ctype_istypedef(cp->ct->info)) return 1;
  if (cp->tok == '$') return 1;
  return 0;
}