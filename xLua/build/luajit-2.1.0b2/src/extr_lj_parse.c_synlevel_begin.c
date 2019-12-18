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
struct TYPE_4__ {scalar_t__ level; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_XLEVELS ; 
 scalar_t__ LJ_MAX_XLEVEL ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void synlevel_begin(LexState *ls)
{
  if (++ls->level >= LJ_MAX_XLEVEL)
    lj_lex_error(ls, 0, LJ_ERR_XLEVELS);
}