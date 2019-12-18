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
struct TYPE_3__ {char* pszNextLastCDComponent; char* pszPD; char* pszPDPlusSlash; char* szCD; char* szCDPlusSlash; char* szCurDrive; char* pszLastCDComponent; char* szParentDir; char* szParentDirPlusSlash; char* szNextLastCDComponent; int /*<<< orphan*/  szCurDriveSlash; } ;
typedef  TYPE_1__ DirComponents ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectory (int,char*) ; 
 int /*<<< orphan*/  check_result (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t const) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 void* strrchr (char*,char) ; 

__attribute__((used)) static void InitDirComponents(DirComponents* p)
{
	/* While the following code seems to work, it's an unholy mess
	 * and should probably be cleaned up.
	 */
	BOOLEAN bOK;

	p->pszNextLastCDComponent = 0;
	p->pszPD = 0;
	p->pszPDPlusSlash = 0;

	GetCurrentDirectory(sizeof(p->szCD) / sizeof(*p->szCD), p->szCD);

	bOK = strlen(p->szCD) >= 2 && p->szCD[1] == ':';
	check_result(bOK, "Expected curdir to be a drive letter. It's not");

	if (!bOK) {
		printf("Curdir is \"%s\"\n", p->szCD);
		exit(1);
	}

	bOK = p->szCD[2] == '\\';
	check_result(bOK, "CD is missing a slash as its third character");
	if (!bOK) {
		printf("CD is \"%s\"\n", p->szCD);
		exit(1);
	}

	// Note that if executed from the root directory, a backslash is
	// already appended.
	strcpy(p->szCDPlusSlash, p->szCD);
	if (strlen(p->szCD) > 3) {
		// Append trailing backslash
		strcat(p->szCDPlusSlash, "\\");
	}

	memcpy(p->szCurDrive, p->szCD, 2);
	p->szCurDrive[2] = 0;
	sprintf(p->szCurDriveSlash, "%s\\", p->szCurDrive);

	p->pszLastCDComponent = strrchr(p->szCD, '\\');
	if (p->pszLastCDComponent)
	{
		// We have a parent directory
		memcpy(p->szParentDir, p->szCD, p->pszLastCDComponent - p->szCD);
		p->szParentDir[p->pszLastCDComponent - p->szCD] = 0;
		p->pszPD = p->szParentDir;
		if (strlen(p->szParentDir) == 2 && p->szParentDir[1] == ':') {
			// When run from root directory, this is expected to
			// have a trailing backslash
			strcat(p->szParentDir, "\\");
		}
		strcpy(p->szParentDirPlusSlash, p->szParentDir);
		if (p->szParentDirPlusSlash[strlen(p->szParentDirPlusSlash)-1] != '\\') {
			strcat(p->szParentDirPlusSlash, "\\");
		}
		p->pszPDPlusSlash = p->szParentDirPlusSlash;

		// Check if we have a directory above that too.
		*p->pszLastCDComponent = 0;
		p->pszNextLastCDComponent = strrchr(p->szCD, '\\');
		*p->pszLastCDComponent = '\\';
		if (p->pszNextLastCDComponent) {
			++p->pszNextLastCDComponent; // skip the leading slash
			if (p->pszNextLastCDComponent + 1 >= p->pszLastCDComponent) {
				p->pszNextLastCDComponent = 0;
			} else {
				const size_t siz = p->pszLastCDComponent - p->pszNextLastCDComponent;
				memcpy(p->szNextLastCDComponent, p->pszNextLastCDComponent, siz);
				p->szNextLastCDComponent[siz] = 0;
				p->pszNextLastCDComponent = p->szNextLastCDComponent;
			}
		}
	}
	if (p->pszLastCDComponent && p->pszLastCDComponent[1] == 0) {
		// If the backslash is the last character in the path,
		// this is a NULL-component.
		p->pszLastCDComponent = 0;
	} else {
		++p->pszLastCDComponent; // skip the leading slash
	}
}