#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* fs; int /*<<< orphan*/  tok; } ;
struct TYPE_8__ {scalar_t__ framesize; scalar_t__ freereg; scalar_t__ nactvar; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  lex_opt (TYPE_2__*,char) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  parse_isend (int /*<<< orphan*/ ) ; 
 int parse_stmt (TYPE_2__*) ; 
 int /*<<< orphan*/  synlevel_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  synlevel_end (TYPE_2__*) ; 

__attribute__((used)) static void parse_chunk(LexState *ls)
{
  int islast = 0;
  synlevel_begin(ls);
  while (!islast && !parse_isend(ls->tok)) {
    islast = parse_stmt(ls);
    lex_opt(ls, ';');
    lua_assert(ls->fs->framesize >= ls->fs->freereg &&
	       ls->fs->freereg >= ls->fs->nactvar);
    ls->fs->freereg = ls->fs->nactvar;  /* Free registers after each stmt. */
  }
  synlevel_end(ls);
}