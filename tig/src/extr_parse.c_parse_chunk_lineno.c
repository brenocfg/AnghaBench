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
struct TYPE_4__ {unsigned long position; } ;
struct TYPE_3__ {unsigned long position; } ;
struct chunk_header {TYPE_2__ new; TYPE_1__ old; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_chunk_header (struct chunk_header*,char const*) ; 

bool
parse_chunk_lineno(unsigned long *lineno, const char *chunk, int marker)
{
	struct chunk_header chunk_header;

	*lineno = 0;

	if (!parse_chunk_header(&chunk_header, chunk))
		return false;

	*lineno = marker == '-' ? chunk_header.old.position : chunk_header.new.position;
	return true;
}