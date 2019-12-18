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
 size_t htmlblock_end_tag (char const*,size_t,struct sd_markdown*,char*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t
htmlblock_end(const char *curtag,
	struct sd_markdown *rndr,
	uint8_t *data,
	size_t size,
	int start_of_line)
{
	size_t tag_size = strlen(curtag);
	size_t i = 1, end_tag;
	int block_lines = 0;

	while (i < size) {
		i++;
		while (i < size && !(data[i - 1] == '<' && data[i] == '/')) {
			if (data[i] == '\n')
				block_lines++;

			i++;
		}

		/* If we are only looking for unindented tags, skip the tag
		 * if it doesn't follow a newline.
		 *
		 * The only exception to this is if the tag is still on the
		 * initial line; in that case it still counts as a closing
		 * tag
		 */
		if (start_of_line && block_lines > 0 && data[i - 2] != '\n')
			continue;

		if (i + 2 + tag_size >= size)
			break;

		end_tag = htmlblock_end_tag(curtag, tag_size, rndr, data + i - 1, size - i + 1);
		if (end_tag)
			return i + end_tag - 1;
	}

	return 0;
}