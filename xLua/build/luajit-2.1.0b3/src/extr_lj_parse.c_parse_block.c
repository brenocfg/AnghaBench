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
struct TYPE_4__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;

/* Variables and functions */
 int /*<<< orphan*/  fscope_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_chunk (TYPE_1__*) ; 

__attribute__((used)) static void parse_block(LexState *ls)
{
  FuncState *fs = ls->fs;
  FuncScope bl;
  fscope_begin(fs, &bl, 0);
  parse_chunk(ls);
  fscope_end(fs);
}