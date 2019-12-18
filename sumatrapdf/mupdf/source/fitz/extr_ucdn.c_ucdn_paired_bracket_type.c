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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ BracketPair ;

/* Variables and functions */
 int UCDN_BIDI_PAIRED_BRACKET_TYPE_NONE ; 
 TYPE_1__* search_bp (int /*<<< orphan*/ ) ; 

int ucdn_paired_bracket_type(uint32_t code)
{
	BracketPair *res = search_bp(code);
	if (res == NULL)
		return UCDN_BIDI_PAIRED_BRACKET_TYPE_NONE;
	else
		return res->type;
}