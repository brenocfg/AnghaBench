#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct time {int dummy; } ;
struct ident {int dummy; } ;
struct TYPE_2__ {char const* name; char const* email; } ;

/* Variables and functions */
 scalar_t__ STRING_SIZE (char*) ; 
 struct ident* get_author (char const*,char const*) ; 
 int /*<<< orphan*/  parse_timesec (struct time*,char*) ; 
 int /*<<< orphan*/  parse_timezone (struct time*,char*) ; 
 char* strchr (char*,char) ; 
 char* string_trim (char*) ; 
 scalar_t__ strlen (char*) ; 
 TYPE_1__ unknown_ident ; 

void
parse_author_line(char *ident, const struct ident **author, struct time *time)
{
	char *nameend = strchr(ident, '<');
	char *emailend = strchr(ident, '>');
	const char *name, *email = "";

	if (nameend && emailend)
		*nameend = *emailend = 0;
	name = string_trim(ident);
	if (nameend)
		email = string_trim(nameend + 1);
	if (!*name)
		name = *email ? email : unknown_ident.name;
	if (!*email)
		email = *name ? name : unknown_ident.email;

	*author = get_author(name, email);

	/* Parse epoch and timezone */
	if (time && emailend && emailend[1] == ' ') {
		char *secs = emailend + 2;
		char *zone = strchr(secs, ' ');

		parse_timesec(time, secs);

		if (zone && strlen(zone) == STRING_SIZE(" +0700"))
			parse_timezone(time, zone + 1);
	}
}