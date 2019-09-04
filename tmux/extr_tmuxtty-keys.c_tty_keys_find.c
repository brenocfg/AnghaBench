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
struct tty_key {int dummy; } ;
struct tty {int /*<<< orphan*/  key_tree; } ;

/* Variables and functions */
 struct tty_key* tty_keys_find1 (int /*<<< orphan*/ ,char const*,size_t,size_t*) ; 

__attribute__((used)) static struct tty_key *
tty_keys_find(struct tty *tty, const char *buf, size_t len, size_t *size)
{
	*size = 0;
	return (tty_keys_find1(tty->key_tree, buf, len, size));
}