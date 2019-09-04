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
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*) ; 
 char* gVersion ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,char) ; 
 char* tcap_boldface ; 
 int /*<<< orphan*/  tcap_normal ; 

void
PrintStartupBanner(void)
{
	char v[80], *cp;
	char vdate[32];

	/* Print selected information from the version ID. */
	vdate[0] = '\0';
	(void) STRNCPY(v, gVersion + 5);
	cp = strchr(v, ',');
	if (cp != NULL) {
		*cp = '\0';
		cp[-5] = '\0';
		(void) STRNCPY(vdate, " (");
		(void) STRNCAT(vdate, v + 16);
		(void) STRNCAT(vdate, ", ");
		(void) STRNCAT(vdate, cp - 4);
		(void) STRNCAT(vdate, ")");
	}

#if defined(BETA) && (BETA > 0)
	(void) fprintf(stdout, "%s%.11s beta %d%s%s by Mike Gleason (ncftp@ncftp.com).\n",
		tcap_boldface,
		gVersion + 5,
		BETA,
		tcap_normal,
		vdate
	);
#else
	(void) fprintf(stdout, "%s%.11s%s%s by Mike Gleason (ncftp@ncftp.com).\n",
		tcap_boldface,
		gVersion + 5,
		tcap_normal,
		vdate
	);
#endif
	(void) fflush(stdout);
}