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
struct TYPE_3__ {char* user; char* pass; char* name; int port; char* dir; } ;
typedef  TYPE_1__* BookmarkPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Strncat (char*,char*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

void
BookmarkToURL(BookmarkPtr bmp, char *url, size_t urlsize)
{
	char pbuf[32];

	/* //<user>:<password>@<host>:<port>/<url-path> */
	/* Note that if an absolute path is given,
	 * you need to escape the first entry, i.e. /pub -> %2Fpub
	 */
	(void) Strncpy(url, "ftp://", urlsize);
	if (bmp->user[0] != '\0') {
		(void) Strncat(url, bmp->user, urlsize);
		if (bmp->pass[0] != '\0') {
			(void) Strncat(url, ":", urlsize);
			(void) Strncat(url, "PASSWORD", urlsize);
		}
		(void) Strncat(url, "@", urlsize);
	}
	(void) Strncat(url, bmp->name, urlsize);
	if (bmp->port != 21) {
		(void) sprintf(pbuf, ":%u", (unsigned int) bmp->port);
		(void) Strncat(url, pbuf, urlsize);
	}
	if (bmp->dir[0] == '/') {
		/* Absolute URL path, must escape first slash. */
		(void) Strncat(url, "/%2F", urlsize);
		(void) Strncat(url, bmp->dir + 1, urlsize);
		(void) Strncat(url, "/", urlsize);
	} else if (bmp->dir[0] != '\0') {
		(void) Strncat(url, "/", urlsize);
		(void) Strncat(url, bmp->dir, urlsize);
		(void) Strncat(url, "/", urlsize);
	}
}