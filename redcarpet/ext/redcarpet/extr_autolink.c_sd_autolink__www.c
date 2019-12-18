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
typedef  int /*<<< orphan*/  uint8_t ;
struct buf {int dummy; } ;

/* Variables and functions */
 size_t autolink_delim (int /*<<< orphan*/ *,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ *,size_t) ; 
 size_t check_domain (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ispunct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

size_t
sd_autolink__www(
	size_t *rewind_p,
	struct buf *link,
	uint8_t *data,
	size_t max_rewind,
	size_t size,
	unsigned int flags)
{
	size_t link_end;

	if (max_rewind > 0 && !ispunct(data[-1]) && !isspace(data[-1]))
		return 0;

	if (size < 4 || memcmp(data, "www.", strlen("www.")) != 0)
		return 0;

	link_end = check_domain(data, size, 0);

	if (link_end == 0)
		return 0;

	while (link_end < size && !isspace(data[link_end]))
		link_end++;

	link_end = autolink_delim(data, link_end, max_rewind, size);

	if (link_end == 0)
		return 0;

	bufput(link, data, link_end);
	*rewind_p = 0;

	return (int)link_end;
}