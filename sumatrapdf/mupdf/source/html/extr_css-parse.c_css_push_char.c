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
struct lexbuf {int string_len; int* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 
 scalar_t__ nelem (int*) ; 

__attribute__((used)) static void css_push_char(struct lexbuf *buf, int c)
{
	if (buf->string_len + 1 >= (int)nelem(buf->string))
		fz_css_error(buf, "token too long");
	buf->string[buf->string_len++] = c;
}