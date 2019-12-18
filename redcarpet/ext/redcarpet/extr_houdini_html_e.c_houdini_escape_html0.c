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
typedef  size_t uint8_t ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESCAPE_GROW_FACTOR (size_t) ; 
 int /*<<< orphan*/ * HTML_ESCAPES ; 
 size_t* HTML_ESCAPE_TABLE ; 
 int /*<<< orphan*/  bufgrow (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufput (struct buf*,size_t const*,size_t) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 int /*<<< orphan*/  bufputs (struct buf*,int /*<<< orphan*/ ) ; 

void
houdini_escape_html0(struct buf *ob, const uint8_t *src, size_t size, int secure)
{
	size_t i = 0, org, esc = 0;

	bufgrow(ob, ESCAPE_GROW_FACTOR(size));

	while (i < size) {
		org = i;
		while (i < size && (esc = HTML_ESCAPE_TABLE[src[i]]) == 0)
			i++;

		if (i > org)
			bufput(ob, src + org, i - org);

		/* escaping */
		if (i >= size)
			break;

		/* The forward slash is only escaped in secure mode */
		if (src[i] == '/' && !secure)
			bufputc(ob, '/');
		else
			bufputs(ob, HTML_ESCAPES[esc]);

		i++;
	}
}