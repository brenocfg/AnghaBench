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
typedef  int /*<<< orphan*/  pathName ;

/* Variables and functions */
 int /*<<< orphan*/  OurDirectoryPath (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vt100VisibleStrlen ; 
 int /*<<< orphan*/  _chmod (char*,int) ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  gl_histsavefile (char*) ; 
 int /*<<< orphan*/  gl_strlen ; 
 int /*<<< orphan*/  kHistoryFileName ; 

void
SaveHistory(void)
{
	char pathName[256];

	if (gOurDirectoryPath[0] == '\0')
		return;		/* Don't create in root directory. */
	(void) OurDirectoryPath(pathName, sizeof(pathName), kHistoryFileName);

	gl_strlen = Vt100VisibleStrlen;
	gl_histsavefile(pathName);
	(void) _chmod(pathName, 00600);
}