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
 unsigned int SD_AUTOLINK_SHORT_DOMAINS ; 
 size_t autolink_delim (char*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  bufput (struct buf*,char*,size_t) ; 
 size_t check_domain (char*,size_t,unsigned int) ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  sd_autolink_issafe (char*,size_t) ; 
 size_t strlen (char*) ; 

size_t
sd_autolink__url(
	size_t *rewind_p,
	struct buf *link,
	uint8_t *data,
	size_t max_rewind,
	size_t size,
	unsigned int flags)
{
	size_t link_end, rewind = 0, domain_len;

	if (size < 4 || data[1] != '/' || data[2] != '/')
		return 0;

	while (rewind < max_rewind && isalpha(data[-rewind - 1]))
		rewind++;

	if (!sd_autolink_issafe(data - rewind, size + rewind))
		return 0;

	link_end = strlen("://");

	domain_len = check_domain(
		data + link_end,
		size - link_end,
		flags & SD_AUTOLINK_SHORT_DOMAINS);

	if (domain_len == 0)
		return 0;

	link_end += domain_len;
	while (link_end < size && !isspace(data[link_end]))
		link_end++;

	link_end = autolink_delim(data, link_end, max_rewind, size);

	if (link_end == 0)
		return 0;

	/**
	 * In certain cases, we may refer to a link at the end of a
	 * sentence so the period should not be part of the URL.
	 */
	if (data[link_end - 1] == '.')
		link_end--;

	bufput(link, data - rewind, link_end + rewind);
	*rewind_p = rewind;

	return link_end;
}