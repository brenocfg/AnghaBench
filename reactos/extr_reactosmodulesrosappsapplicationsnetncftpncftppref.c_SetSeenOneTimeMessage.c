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

/* Variables and functions */
 int /*<<< orphan*/  STRNCAT (char*,char const* const) ; 
 int /*<<< orphan*/  STRNCPY (char*,char const* const) ; 
 char* gOneTimeMessagesSeen ; 
 int /*<<< orphan*/  gPrefsDirty ; 

void
SetSeenOneTimeMessage(const char *const msg)
{
	gPrefsDirty++;
	if (gOneTimeMessagesSeen[0] == '\0')
		STRNCPY(gOneTimeMessagesSeen, msg);
	else {
		STRNCAT(gOneTimeMessagesSeen, ",");
		STRNCAT(gOneTimeMessagesSeen, msg);
	}
}