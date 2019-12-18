#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  TK_BREAK 131 
#define  TK_CONTINUE 130 
#define  TK_RETURN 129 
#define  TK_THROW 128 

__attribute__((used)) static int isnlthcontext(int last)
{
	switch (last) {
	case TK_BREAK:
	case TK_CONTINUE:
	case TK_RETURN:
	case TK_THROW:
		return 1;
	default:
		return 0;
	}
}