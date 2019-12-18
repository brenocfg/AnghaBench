#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* html_entities ; 
 size_t nelem (TYPE_1__*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static size_t xml_parse_entity(int *c, char *a)
{
	char *b;
	size_t i;

	if (a[1] == '#') {
		if (a[2] == 'x')
			*c = strtol(a + 3, &b, 16);
		else
			*c = strtol(a + 2, &b, 10);
		if (*b == ';')
			return b - a + 1;
	}
	else if (a[1] == 'l' && a[2] == 't' && a[3] == ';') {
		*c = '<';
		return 4;
	}
	else if (a[1] == 'g' && a[2] == 't' && a[3] == ';') {
		*c = '>';
		return 4;
	}
	else if (a[1] == 'a' && a[2] == 'm' && a[3] == 'p' && a[4] == ';') {
		*c = '&';
		return 5;
	}
	else if (a[1] == 'a' && a[2] == 'p' && a[3] == 'o' && a[4] == 's' && a[5] == ';') {
		*c = '\'';
		return 6;
	}
	else if (a[1] == 'q' && a[2] == 'u' && a[3] == 'o' && a[4] == 't' && a[5] == ';') {
		*c = '"';
		return 6;
	}

	/* We should only be doing this for XHTML, but it shouldn't be a problem. */
	for (i = 0; i < nelem(html_entities); ++i) {
		size_t n = strlen(html_entities[i].name);
		if (!strncmp(a+1, html_entities[i].name, n) && a[n+1] == ';') {
			*c = html_entities[i].c;
			return n + 2;
		}
	}

	*c = *a;
	return 1;
}