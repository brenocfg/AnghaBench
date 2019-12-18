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
struct TYPE_3__ {char* lastFTPCmdResultStr; int /*<<< orphan*/  errNo; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 char* FTPStrError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const,...) ; 
 int const kNoErr ; 
 int /*<<< orphan*/  stderr ; 

void
FTPPerror(const FTPCIPtr cip, const int err, const int eerr, const char *const s1, const char *const s2)
{
	if (err != kNoErr) {
		if (err == eerr) {
			if ((s2 == NULL) || (s2[0] == '\0')) {
				if ((s1 == NULL) || (s1[0] == '\0')) {
					(void) fprintf(stderr, "server said: %s\n", cip->lastFTPCmdResultStr);
				} else {
					(void) fprintf(stderr, "%s: server said: %s\n", s1, cip->lastFTPCmdResultStr);
				}
			} else if ((s1 == NULL) || (s1[0] == '\0')) {
				(void) fprintf(stderr, "%s: server said: %s\n", s2, cip->lastFTPCmdResultStr);
			} else {
				(void) fprintf(stderr, "%s %s: server said: %s\n", s1, s2, cip->lastFTPCmdResultStr);
			}
		} else {
			if ((s2 == NULL) || (s2[0] == '\0')) {
				if ((s1 == NULL) || (s1[0] == '\0')) {
					(void) fprintf(stderr, "%s.\n", FTPStrError(cip->errNo));
				} else {
					(void) fprintf(stderr, "%s: %s.\n", s1, FTPStrError(cip->errNo));
				}
			} else if ((s1 == NULL) || (s1[0] == '\0')) {
				(void) fprintf(stderr, "%s: %s.\n", s2, FTPStrError(cip->errNo));
			} else {
				(void) fprintf(stderr, "%s %s: %s.\n", s1, s2, FTPStrError(cip->errNo));
			}
		}
	}
}