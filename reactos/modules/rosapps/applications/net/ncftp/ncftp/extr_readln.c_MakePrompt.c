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
struct TYPE_2__ {scalar_t__ loggedIn; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbbrevStr (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Strncat (char*,char*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 TYPE_1__ gConn ; 
 int /*<<< orphan*/  gRemoteCWD ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,...) ; 
 char* tcap_boldface ; 
 char* tcap_normal ; 

void
MakePrompt(char *dst, size_t dsize)
{
	char acwd[64];

#	ifdef HAVE_SNPRINTF
	if (gConn.loggedIn != 0) {
		AbbrevStr(acwd, gRemoteCWD, 25, 0);
		snprintf(dst, dsize, "%sncftp%s %s %s>%s ",
			tcap_boldface, tcap_normal, acwd,
			tcap_boldface, tcap_normal);
	} else {
		snprintf(dst, dsize, "%sncftp%s> ",
			tcap_boldface, tcap_normal);
	}
#	else	/* HAVE_SNPRINTF */
	(void) Strncpy(dst, tcap_boldface, dsize);
	(void) Strncat(dst, "ncftp", dsize);
	(void) Strncat(dst, tcap_normal, dsize);
	if (gConn.loggedIn != 0) {
		AbbrevStr(acwd, gRemoteCWD, 25, 0);
		(void) Strncat(dst, " ", dsize);
		(void) Strncat(dst, acwd, dsize);
		(void) Strncat(dst, " ", dsize);
	}
	(void) Strncat(dst, tcap_boldface, dsize);
	(void) Strncat(dst, ">", dsize);
	(void) Strncat(dst, tcap_normal, dsize);
	(void) Strncat(dst, " ", dsize);
#	endif	/* HAVE_SNPRINTF */
}