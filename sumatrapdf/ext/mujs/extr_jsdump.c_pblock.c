#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 scalar_t__ STM_BLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  in (int) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  pstmlist (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblock(int d, js_Ast *block)
{
	assert(block->type == STM_BLOCK);
	pc('{'); nl();
	pstmlist(d, block->a);
	in(d); pc('}');
}