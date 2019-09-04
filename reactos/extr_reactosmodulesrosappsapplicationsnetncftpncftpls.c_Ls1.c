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
struct TYPE_6__ {TYPE_1__** vec; } ;
struct TYPE_5__ {char* relname; scalar_t__ type; } ;
typedef  TYPE_1__** FileInfoVec ;
typedef  TYPE_1__* FileInfoPtr ;
typedef  TYPE_3__* FileInfoListPtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Trace (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

void
Ls1(FileInfoListPtr dirp, int endChars, FILE *stream)
{
	char fTail[2];
	int i;
	int fType;
	FileInfoVec diritemv;
	FileInfoPtr diritemp;

	fTail[0] = '\0';
	fTail[1] = '\0';
	diritemv = dirp->vec;

	for (i=0; ; i++) {
		diritemp = diritemv[i];
		if (diritemp == NULL)
			break;

		fType = (int) diritemp->type;
		if (endChars != 0) {
			if (fType == 'd')
				fTail[0] = '/';
			else
				fTail[0] = '\0';
		}

		(void) fprintf(stream, "%s%s\n",
			diritemp->relname,
			fTail
		);

		Trace(0, "%s%s\n",
			diritemp->relname,
			fTail
		);
	}
}