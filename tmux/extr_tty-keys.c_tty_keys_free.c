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
struct tty {int /*<<< orphan*/  key_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_keys_free1 (int /*<<< orphan*/ ) ; 

void
tty_keys_free(struct tty *tty)
{
	tty_keys_free1(tty->key_tree);
}