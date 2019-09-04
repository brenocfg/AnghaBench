#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bm ;
struct TYPE_6__ {char* host; char* user; char* pass; char* acct; int /*<<< orphan*/  port; } ;
struct TYPE_5__ {char* name; char* user; char* pass; char* acct; int /*<<< orphan*/  dir; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  AbsoluteToRelative (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BookmarkToURL (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  STREQ (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 TYPE_3__ gConn ; 
 char* gRemoteCWD ; 
 int /*<<< orphan*/  gStartDir ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
CurrentURL(char *dst, size_t dsize, int showpass)
{
	Bookmark bm;
	char dir[160];

	memset(&bm, 0, sizeof(bm));
	(void) STRNCPY(bm.name, gConn.host);
	if ((gConn.user[0] != '\0') && (! STREQ(gConn.user, "anonymous")) && (! STREQ(gConn.user, "ftp"))) {
		(void) STRNCPY(bm.user, gConn.user);
		(void) STRNCPY(bm.pass, (showpass == 0) ? "PASSWORD" : gConn.pass);
		(void) STRNCPY(bm.acct, gConn.acct);
	}

	bm.port = gConn.port;

	/* We now save relative paths, because the pathname in URLs are
	 * relative by nature.  This makes non-anonymous FTP URLs shorter
	 * because it doesn't have to include the pathname of their
	 * home directory.
	 */
	(void) STRNCPY(dir, gRemoteCWD);
	AbsoluteToRelative(bm.dir, sizeof(bm.dir), dir, gStartDir, strlen(gStartDir));

	BookmarkToURL(&bm, dst, dsize);
}