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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  gOneTimeMessagesSeen ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const* const,char*) ; 
 char* strtok (char*,char*) ; 

int
HasSeenOneTimeMessage(const char *const msg)
{
	char buf[256];
	char *a, *b;

	memcpy(buf, gOneTimeMessagesSeen, sizeof(buf));
	for (a = buf; (b = strtok(a, ",\n")) != NULL; a = NULL) {
		if (strcmp(msg, b) == 0)
			return (1);
	}
	return (0);
}