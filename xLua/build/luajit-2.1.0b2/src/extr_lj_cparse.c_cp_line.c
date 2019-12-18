#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ u32; } ;
struct TYPE_6__ {scalar_t__ tok; scalar_t__ linenumber; TYPE_1__ val; } ;
typedef  TYPE_2__ CPState ;
typedef  scalar_t__ BCLine ;

/* Variables and functions */
 scalar_t__ CTOK_EOF ; 
 int /*<<< orphan*/  cp_next (TYPE_2__*) ; 

__attribute__((used)) static void cp_line(CPState *cp, BCLine hashline)
{
  BCLine newline = cp->val.u32;
  /* TODO: Handle file name and include it in error messages. */
  while (cp->tok != CTOK_EOF && cp->linenumber == hashline)
    cp_next(cp);
  cp->linenumber = newline;
}