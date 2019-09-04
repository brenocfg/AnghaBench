#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int usedMLS; int mlsFeatures; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  FTPCmd (TYPE_1__* const,char*,char*) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int kMlsOptModify ; 
 int kMlsOptPerm ; 
 int kMlsOptSize ; 
 int kMlsOptType ; 
 int kMlsOptUNIXgid ; 
 int kMlsOptUNIXgroup ; 
 int kMlsOptUNIXmode ; 
 int kMlsOptUNIXowner ; 
 int kMlsOptUNIXuid ; 
 int kMlsOptUnique ; 
 int kPreferredMlsOpts ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
FTPRequestMlsOptions(const FTPCIPtr cip)
{
	int f;
	char optstr[128];
	size_t optstrlen;

	if (cip->usedMLS == 0) {
		/* First MLSD/MLST ? */
		cip->usedMLS = 1;

		f = cip->mlsFeatures & kPreferredMlsOpts;
		optstr[0] = '\0';

		/* TYPE */
		if ((f & kMlsOptType) != 0) {
			STRNCAT(optstr, "type;");
		}

		/* SIZE */
		if ((f & kMlsOptSize) != 0) {
			STRNCAT(optstr, "size;");
		}

		/* MODTIME */
		if ((f & kMlsOptModify) != 0) {
			STRNCAT(optstr, "modify;");
		}

		/* MODE */
		if ((f & kMlsOptUNIXmode) != 0) {
			STRNCAT(optstr, "UNIX.mode;");
		}

		/* PERM */
		if ((f & kMlsOptPerm) != 0) {
			STRNCAT(optstr, "perm;");
		}

		/* OWNER */
		if ((f & kMlsOptUNIXowner) != 0) {
			STRNCAT(optstr, "UNIX.owner;");
		}

		/* UID */
		if ((f & kMlsOptUNIXuid) != 0) {
			STRNCAT(optstr, "UNIX.uid;");
		}

		/* GROUP */
		if ((f & kMlsOptUNIXgroup) != 0) {
			STRNCAT(optstr, "UNIX.group;");
		}

		/* GID */
		if ((f & kMlsOptUNIXgid) != 0) {
			STRNCAT(optstr, "UNIX.gid;");
		}

		/* UNIQUE */
		if ((f & kMlsOptUnique) != 0) {
			STRNCAT(optstr, "unique;");
		}

		/* Tell the server what we prefer. */
		optstrlen = strlen(optstr);
		if (optstrlen > 0) {
			if (optstr[optstrlen - 1] == ';')
				optstr[optstrlen - 1] = '\0';
			(void) FTPCmd(cip, "OPTS MLST %s", optstr);
		}
	}
}