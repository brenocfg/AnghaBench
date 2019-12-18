#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {scalar_t__ visible; int /*<<< orphan*/  (* proc ) (int,char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  varname; } ;
typedef  int /*<<< orphan*/  (* PrefProc ) (int,char*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ISTREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ * const) ; 
 int gNumPrefOpts ; 
 TYPE_1__* gPrefOpts ; 
 int /*<<< orphan*/  gPrefsDirty ; 
 scalar_t__ kPrefOptObselete ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int,char*,int /*<<< orphan*/ *) ; 

void
ProcessPrefsFile(FILE *const fp)
{
	char line[1024];
	char *tok1, *tok2;
	int t;

	line[sizeof(line) - 1] = '\0';
	while (fgets(line, sizeof(line) - 1, fp) != NULL) {
		tok1 = strtok(line, " =\t\r\n");
		if ((tok1 == NULL) || (tok1[0] == '#'))
			continue;
		tok2 = strtok(NULL, "\r\n");
		if (tok2 == NULL)
			continue;

		for (t=0; t<gNumPrefOpts; t++) {
			if (ISTREQ(tok1, gPrefOpts[t].varname)) {
				if (gPrefOpts[t].visible == kPrefOptObselete) {
					/* Probably converting an
					 * old 2.4.2 file.
					 */
					gPrefsDirty++;
				} else if (gPrefOpts[t].proc != (PrefProc) 0) {
					(*gPrefOpts[t].proc)(t, tok2, NULL);
				}
			}
		}
	}
}