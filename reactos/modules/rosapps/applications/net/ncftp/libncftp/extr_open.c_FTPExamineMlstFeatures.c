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
struct TYPE_3__ {int mlsFeatures; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 scalar_t__ ISTREQ (char*,char*) ; 
 scalar_t__ ISTRNEQ (char*,char*,int) ; 
 int /*<<< orphan*/  STRNCPY (char*,char const*) ; 
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
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
FTPExamineMlstFeatures(const FTPCIPtr cip, const char *features)
{
	char buf[256], *feat;
	int flags;

	flags = 0;
	STRNCPY(buf, features);
	feat = strtok(buf, ";*");
	while (feat != NULL) {
		if (ISTRNEQ(feat, "OS.", 3))
			feat += 3;
		if (ISTREQ(feat, "type")) {
			flags |= kMlsOptType;
		} else if (ISTREQ(feat, "size")) {
			flags |= kMlsOptSize;
		} else if (ISTREQ(feat, "modify")) {
			flags |= kMlsOptModify;
		} else if (ISTREQ(feat, "UNIX.mode")) {
			flags |= kMlsOptUNIXmode;
		} else if (ISTREQ(feat, "UNIX.owner")) {
			flags |= kMlsOptUNIXowner;
		} else if (ISTREQ(feat, "UNIX.group")) {
			flags |= kMlsOptUNIXgroup;
		} else if (ISTREQ(feat, "perm")) {
			flags |= kMlsOptPerm;
		} else if (ISTREQ(feat, "UNIX.uid")) {
			flags |= kMlsOptUNIXuid;
		} else if (ISTREQ(feat, "UNIX.gid")) {
			flags |= kMlsOptUNIXgid;
		} else if (ISTREQ(feat, "UNIX.gid")) {
			flags |= kMlsOptUnique;
		}
		feat = strtok(NULL, ";*");
	}

	cip->mlsFeatures = flags;
}