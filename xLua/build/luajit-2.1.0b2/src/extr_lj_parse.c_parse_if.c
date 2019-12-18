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
struct TYPE_7__ {scalar_t__ tok; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  BCPos ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  NO_JMP ; 
 scalar_t__ TK_else ; 
 scalar_t__ TK_elseif ; 
 int /*<<< orphan*/  TK_end ; 
 int /*<<< orphan*/  TK_if ; 
 int /*<<< orphan*/  bcemit_jmp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jmp_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_tohere (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_block (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_then (TYPE_1__*) ; 

__attribute__((used)) static void parse_if(LexState *ls, BCLine line)
{
  FuncState *fs = ls->fs;
  BCPos flist;
  BCPos escapelist = NO_JMP;
  flist = parse_then(ls);
  while (ls->tok == TK_elseif) {  /* Parse multiple 'elseif' blocks. */
    jmp_append(fs, &escapelist, bcemit_jmp(fs));
    jmp_tohere(fs, flist);
    flist = parse_then(ls);
  }
  if (ls->tok == TK_else) {  /* Parse optional 'else' block. */
    jmp_append(fs, &escapelist, bcemit_jmp(fs));
    jmp_tohere(fs, flist);
    lj_lex_next(ls);  /* Skip 'else'. */
    parse_block(ls);
  } else {
    jmp_append(fs, &escapelist, flist);
  }
  jmp_tohere(fs, escapelist);
  lex_match(ls, TK_end, TK_if, line);
}