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
typedef  char uint8_t ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufput (struct buf*,char const*,size_t) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 

__attribute__((used)) static void expand_tabs(struct buf *ob, const uint8_t *line, size_t size)
{
	size_t  i = 0, tab = 0;

	while (i < size) {
		size_t org = i;

		while (i < size && line[i] != '\t') {
			i++; tab++;
		}

		if (i > org)
			bufput(ob, line + org, i - org);

		if (i >= size)
			break;

		do {
			bufputc(ob, ' '); tab++;
		} while (tab % 4);

		i++;
	}
}