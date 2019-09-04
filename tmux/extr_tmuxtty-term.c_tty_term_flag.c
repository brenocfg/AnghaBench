#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_term {TYPE_2__* codes; } ;
typedef  enum tty_code_code { ____Placeholder_tty_code_code } tty_code_code ;
struct TYPE_3__ {int flag; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ value; } ;

/* Variables and functions */
 scalar_t__ TTYCODE_FLAG ; 
 int /*<<< orphan*/  fatalx (char*,int) ; 
 int /*<<< orphan*/  tty_term_has (struct tty_term*,int) ; 

int
tty_term_flag(struct tty_term *term, enum tty_code_code code)
{
	if (!tty_term_has(term, code))
		return (0);
	if (term->codes[code].type != TTYCODE_FLAG)
		fatalx("not a flag: %d", code);
	return (term->codes[code].value.flag);
}