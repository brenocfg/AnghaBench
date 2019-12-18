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
struct TYPE_3__ {int type; struct TYPE_3__* x; int /*<<< orphan*/  m; struct TYPE_3__* y; } ;
typedef  TYPE_1__ Renode ;

/* Variables and functions */
#define  P_ALT 136 
#define  P_ANY 135 
#define  P_CAT 134 
#define  P_CCLASS 133 
#define  P_CHAR 132 
#define  P_NCCLASS 131 
#define  P_PAR 130 
#define  P_REF 129 
#define  P_REP 128 

__attribute__((used)) static int empty(Renode *node)
{
	if (!node) return 1;
	switch (node->type) {
	default: return 1;
	case P_CAT: return empty(node->x) && empty(node->y);
	case P_ALT: return empty(node->x) || empty(node->y);
	case P_REP: return empty(node->x) || node->m == 0;
	case P_PAR: return empty(node->x);
	case P_REF: return empty(node->x);
	case P_ANY: case P_CHAR: case P_CCLASS: case P_NCCLASS: return 0;
	}
}