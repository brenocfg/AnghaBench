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
struct lexbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_lex_accept (struct lexbuf*,int) ; 
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 

__attribute__((used)) static void css_lex_expect(struct lexbuf *buf, int t)
{
	if (!css_lex_accept(buf, t))
		fz_css_error(buf, "unexpected character");
}