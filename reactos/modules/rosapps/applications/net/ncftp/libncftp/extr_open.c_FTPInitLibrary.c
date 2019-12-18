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
struct servent {int /*<<< orphan*/  s_port; } ;
struct TYPE_4__ {unsigned int defaultPort; int init; int socksInit; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  FTPLibraryInfo ;
typedef  TYPE_1__* FTPLIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKSinit (char*) ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct servent* getservbyname (char*,char*) ; 
 scalar_t__ kDefaultFTPPort ; 
 int kErrBadParameter ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

int
FTPInitLibrary(const FTPLIPtr lip)
{
	struct servent *ftp;

	if (lip == NULL)
		return (kErrBadParameter);

	(void) memset(lip, 0, sizeof(FTPLibraryInfo));
	if ((ftp = getservbyname("ftp", "tcp")) == NULL)
		lip->defaultPort = (unsigned int) kDefaultFTPPort;
	else
		lip->defaultPort = (unsigned int) ntohs(ftp->s_port);

	lip->init = 1;
	(void) STRNCPY(lip->magic, kLibraryMagic);

	/* We'll initialize the defaultAnonPassword field
	 * later when we try the first anon ftp connection.
	 */

#ifdef HAVE_LIBSOCKS
	SOCKSinit("libncftp");
	lip->socksInit = 1;
#endif
	return (kNoErr);
}