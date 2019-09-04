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
struct tty_ctx {int num; int /*<<< orphan*/  ptr; } ;
struct tty {int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_MS ; 
 int /*<<< orphan*/  b64_ntop (int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  tty_putcode_ptr2 (struct tty*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xmalloc (size_t) ; 

void
tty_cmd_setselection(struct tty *tty, const struct tty_ctx *ctx)
{
	char	*buf;
	size_t	 off;

	if (!tty_term_has(tty->term, TTYC_MS))
		return;

	off = 4 * ((ctx->num + 2) / 3) + 1; /* storage for base64 */
	buf = xmalloc(off);

	b64_ntop(ctx->ptr, ctx->num, buf, off);
	tty_putcode_ptr2(tty, TTYC_MS, "", buf);

	free(buf);
}