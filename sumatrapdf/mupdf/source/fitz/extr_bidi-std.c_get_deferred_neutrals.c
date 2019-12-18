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
typedef  int /*<<< orphan*/  fz_bidi_level ;
typedef  int fz_bidi_chartype ;
typedef  int fz_bidi_action ;

/* Variables and functions */
 int En ; 
 int embedding_direction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_bidi_chartype
get_deferred_neutrals(fz_bidi_action action, fz_bidi_level level)
{
	action = (action >> 4) & 0xF;
	if (action == (En >> 4))
		return embedding_direction(level);
	else
		return action;
}