#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 scalar_t__ STM_BLOCK ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  pblock (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pstm (int,TYPE_1__*) ; 
 int /*<<< orphan*/  sp () ; 

__attribute__((used)) static void pstmh(int d, js_Ast *stm)
{
	if (stm->type == STM_BLOCK) {
		sp();
		pblock(d, stm);
	} else {
		nl();
		pstm(d+1, stm);
	}
}