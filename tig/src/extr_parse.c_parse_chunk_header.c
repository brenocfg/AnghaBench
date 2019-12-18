#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lines; int position; } ;
struct TYPE_3__ {int lines; int position; } ;
struct chunk_header {TYPE_2__ new; TYPE_1__ old; } ;

/* Variables and functions */
 int STRING_SIZE (char*) ; 
 int /*<<< orphan*/  memset (struct chunk_header*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_ulong (char const**,int*,char,int) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

bool
parse_chunk_header(struct chunk_header *header, const char *line)
{
	memset(header, 0, sizeof(*header));
	header->new.lines = header->old.lines = 1;

	if (!prefixcmp(line, "@@ -"))
		line += STRING_SIZE("@@ -") - 1;
	else if (!prefixcmp(line, "@@@") &&
		 (line = strrchr(line, '-')))
		/* Stay at that '-'. */ ;
	else
		return false;

	return  parse_ulong(&line, &header->old.position, '-', false) &&
		parse_ulong(&line, &header->old.lines, ',', true) &&
		parse_ulong(&line, &header->new.position, '+', false) &&
		parse_ulong(&line, &header->new.lines, ',', false);
}