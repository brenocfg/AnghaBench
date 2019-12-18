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
struct lexbuf {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int CSS_HASH ; 
 int /*<<< orphan*/  css_lex_next (struct lexbuf*) ; 
 int /*<<< orphan*/  css_push_char (struct lexbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ isnmchar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int css_lex_hash(struct lexbuf *buf)
{
	while (isnmchar(buf->c))
	{
		css_push_char(buf, buf->c);
		css_lex_next(buf);
	}
	css_push_char(buf, 0);
	return CSS_HASH;
}