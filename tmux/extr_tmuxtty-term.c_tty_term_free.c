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
typedef  size_t u_int ;
struct TYPE_2__ {struct tty_term* string; } ;
struct tty_term {scalar_t__ references; scalar_t__ type; struct tty_term* name; struct tty_term* codes; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct tty_term*,int /*<<< orphan*/ ) ; 
 scalar_t__ TTYCODE_STRING ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct tty_term*) ; 
 size_t tty_term_ncodes () ; 

void
tty_term_free(struct tty_term *term)
{
	u_int	i;

	if (--term->references != 0)
		return;

	LIST_REMOVE(term, entry);

	for (i = 0; i < tty_term_ncodes(); i++) {
		if (term->codes[i].type == TTYCODE_STRING)
			free(term->codes[i].value.string);
	}
	free(term->codes);

	free(term->name);
	free(term);
}