#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_term {TYPE_1__* codes; } ;
typedef  enum tty_code_code { ____Placeholder_tty_code_code } tty_code_code ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TTYCODE_NONE ; 

int
tty_term_has(struct tty_term *term, enum tty_code_code code)
{
	return (term->codes[code].type != TTYCODE_NONE);
}