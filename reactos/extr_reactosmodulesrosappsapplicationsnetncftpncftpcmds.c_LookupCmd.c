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
struct in_addr {int dummy; } ;
struct hostent {char** h_addr_list; char* h_name; char** h_aliases; } ;
typedef  int /*<<< orphan*/  ipStr ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 struct hostent* GetHostEntry (char const*,struct in_addr*) ; 
 int Getopt (int const,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  MyInetAddr (char*,int,char**,int) ; 
 int /*<<< orphan*/  PrintCmdUsage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Trace (int,char*,...) ; 
 int gOptInd ; 
 int /*<<< orphan*/  gUnusedArg ; 

void
LookupCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int i, j;
	struct hostent *hp;
	const char *host;
	char **cpp;
	struct in_addr ip_address;
	int shortMode, opt;
	char ipStr[16];

	ARGSUSED(gUnusedArg);
	shortMode = 1;

	GetoptReset();
	while ((opt = Getopt(argc, argv, "v")) >= 0) {
		if (opt == 'v')
			shortMode = 0;
		else {
			PrintCmdUsage(cmdp);
			return;
		}
	}

	for (i=gOptInd; i<argc; i++) {
		hp = GetHostEntry((host = argv[i]), &ip_address);
		if ((i > gOptInd) && (shortMode == 0))
			Trace(-1, "\n");
		if (hp == NULL) {
			Trace(-1, "Unable to get information about site %s.\n", host);
		} else if (shortMode) {
			MyInetAddr(ipStr, sizeof(ipStr), hp->h_addr_list, 0);
			Trace(-1, "%-40s %s\n", hp->h_name, ipStr);
		} else {
			Trace(-1, "%s:\n", host);
			Trace(-1, "    Name:     %s\n", hp->h_name);
			for (cpp = hp->h_aliases; *cpp != NULL; cpp++)
				Trace(-1, "    Alias:    %s\n", *cpp);
			for (j = 0, cpp = hp->h_addr_list; *cpp != NULL; cpp++, ++j) {
				MyInetAddr(ipStr, sizeof(ipStr), hp->h_addr_list, j);
				Trace(-1, "    Address:  %s\n", ipStr);
			}
		}
	}
}