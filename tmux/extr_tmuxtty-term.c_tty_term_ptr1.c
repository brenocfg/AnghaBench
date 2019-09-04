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
struct tty_term {int dummy; } ;
typedef  enum tty_code_code { ____Placeholder_tty_code_code } tty_code_code ;

/* Variables and functions */
 char const* tparm (char*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_string (struct tty_term*,int) ; 

const char *
tty_term_ptr1(struct tty_term *term, enum tty_code_code code, const void *a)
{
	return (tparm((char *) tty_term_string(term, code), (long)a, 0, 0, 0, 0, 0, 0, 0, 0));
}