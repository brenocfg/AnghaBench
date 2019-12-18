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
struct sd_markdown {int dummy; } ;

/* Variables and functions */
 size_t is_empty (char*,size_t) ; 
 scalar_t__ strncasecmp (char*,char const*,size_t) ; 

__attribute__((used)) static size_t
htmlblock_end_tag(
	const char *tag,
	size_t tag_len,
	struct sd_markdown *rndr,
	uint8_t *data,
	size_t size)
{
	size_t i, w;

	/* checking if tag is a match */
	if (tag_len + 3 >= size ||
		strncasecmp((char *)data + 2, tag, tag_len) != 0 ||
		data[tag_len + 2] != '>')
		return 0;

	/* checking white lines */
	i = tag_len + 3;
	w = 0;
	if (i < size && (w = is_empty(data + i, size - i)) == 0)
		return 0; /* non-blank after tag */
	i += w;
	w = 0;

	if (i < size)
		w = is_empty(data + i, size - i);

	return i + w;
}