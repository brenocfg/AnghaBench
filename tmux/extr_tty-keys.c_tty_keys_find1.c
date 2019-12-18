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
struct tty_key {char const ch; scalar_t__ key; struct tty_key* right; struct tty_key* left; struct tty_key* next; } ;

/* Variables and functions */
 scalar_t__ KEYC_UNKNOWN ; 

__attribute__((used)) static struct tty_key *
tty_keys_find1(struct tty_key *tk, const char *buf, size_t len, size_t *size)
{
	/* If no data, no match. */
	if (len == 0)
		return (NULL);

	/* If the node is NULL, this is the end of the tree. No match. */
	if (tk == NULL)
		return (NULL);

	/* Pick the next in the sequence. */
	if (tk->ch == *buf) {
		/* Move forward in the string. */
		buf++; len--;
		(*size)++;

		/* At the end of the string, return the current node. */
		if (len == 0 || (tk->next == NULL && tk->key != KEYC_UNKNOWN))
			return (tk);

		/* Move into the next tree for the following character. */
		tk = tk->next;
	} else {
		if (*buf < tk->ch)
			tk = tk->left;
		else if (*buf > tk->ch)
			tk = tk->right;
	}

	/* Move to the next in the tree. */
	return (tty_keys_find1(tk, buf, len, size));
}