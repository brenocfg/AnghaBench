#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ c; int /*<<< orphan*/  linenumber; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ CPState ;
typedef  scalar_t__ CPChar ;

/* Variables and functions */
 scalar_t__ cp_iseol (scalar_t__) ; 
 scalar_t__ cp_rawpeek (TYPE_1__*) ; 

__attribute__((used)) static void cp_newline(CPState *cp)
{
  CPChar c = cp_rawpeek(cp);
  if (cp_iseol(c) && c != cp->c) cp->p++;
  cp->linenumber++;
}