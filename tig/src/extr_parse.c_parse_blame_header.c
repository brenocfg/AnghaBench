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
struct blame_header {size_t orig_lineno; size_t lineno; size_t group; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int SIZEOF_REV ; 
 int /*<<< orphan*/  parse_number (char const**,size_t*,int,size_t) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

bool
parse_blame_header(struct blame_header *header, const char *text, size_t max_lineno)
{
	const char *pos = text + SIZEOF_REV - 2;

	if (strlen(text) <= SIZEOF_REV || pos[1] != ' ')
		return false;

	string_ncopy(header->id, text, SIZEOF_REV);

	if (!parse_number(&pos, &header->orig_lineno, 1, 9999999) ||
	    !parse_number(&pos, &header->lineno, 1, max_lineno) ||
	    !parse_number(&pos, &header->group, 1, max_lineno - header->lineno + 1))
		return false;

	return true;
}