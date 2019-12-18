#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  hasUTIME; int /*<<< orphan*/  hasPASV; int /*<<< orphan*/  hasMDTM; int /*<<< orphan*/  hasSIZE; int /*<<< orphan*/  port; int /*<<< orphan*/  acct; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; int /*<<< orphan*/  host; } ;
struct TYPE_4__ {char* name; char* user; char* pass; char* acct; char* lastIP; int /*<<< orphan*/  hasUTIME; int /*<<< orphan*/  hasPASV; int /*<<< orphan*/  hasMDTM; int /*<<< orphan*/  hasSIZE; int /*<<< orphan*/  lastCall; int /*<<< orphan*/  port; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__* BookmarkPtr ;

/* Variables and functions */
 int /*<<< orphan*/  AbsoluteToRelative (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ gConn ; 
 scalar_t__ gFirewallType ; 
 int /*<<< orphan*/  gRemoteCWD ; 
 int /*<<< orphan*/  gStartDir ; 
 scalar_t__ kFirewallNotInUse ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
FillBookmarkInfo(BookmarkPtr bmp)
{
	char dir[160];

	(void) STRNCPY(bmp->name, gConn.host);
	if ((STREQ(gConn.user, "anonymous")) || (STREQ(gConn.user, "ftp"))) {
		bmp->user[0] = '\0';
		bmp->pass[0] = '\0';
		bmp->acct[0] = '\0';
	} else {
		(void) STRNCPY(bmp->user, gConn.user);
		(void) STRNCPY(bmp->pass, gConn.pass);
		(void) STRNCPY(bmp->acct, gConn.acct);
	}

	/* We now save relative paths, because the pathname in URLs are
	 * relative by nature.  This makes non-anonymous FTP URLs shorter
	 * because it doesn't have to include the pathname of their
	 * home directory.
	 */
	(void) STRNCPY(dir, gRemoteCWD);
	AbsoluteToRelative(bmp->dir, sizeof(bmp->dir), dir, gStartDir, strlen(gStartDir));
	bmp->port = gConn.port;
	(void) time(&bmp->lastCall);
	bmp->hasSIZE = gConn.hasSIZE;
	bmp->hasMDTM = gConn.hasMDTM;
	bmp->hasPASV = gConn.hasPASV;
	bmp->hasUTIME = gConn.hasUTIME;
	if (gFirewallType == kFirewallNotInUse)
		(void) STRNCPY(bmp->lastIP, gConn.ip);
}