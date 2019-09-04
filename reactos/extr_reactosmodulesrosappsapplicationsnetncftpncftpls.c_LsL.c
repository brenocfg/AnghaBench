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
typedef  int longest_int ;
struct TYPE_6__ {int maxPlugLen; TYPE_1__** vec; } ;
struct TYPE_5__ {char* rlinkto; scalar_t__ size; int plug; char* relname; int /*<<< orphan*/  mdtm; scalar_t__ type; } ;
typedef  TYPE_1__** FileInfoVec ;
typedef  TYPE_1__* FileInfoPtr ;
typedef  TYPE_3__* FileInfoListPtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LsDate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Trace (int /*<<< orphan*/ ,char*,char*,char*,char const*,char*,char const*,char*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char const*,char*,char const*,char*,char const*,char const*,char*) ; 
 scalar_t__ gNowMinus6Mon ; 
 scalar_t__ gNowPlus1Hr ; 
 scalar_t__ kSizeUnknown ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

void
LsL(FileInfoListPtr dirp, int endChars, int linkedTo, FILE *stream)
{
	FileInfoPtr diritemp;
	FileInfoVec diritemv;
	int i;
	char fTail[2];
	int fType;
	const char *l1, *l2;
	char datestr[16];
	char sizestr[32];
	char plugspec[16];
	char plugstr[64];
	const char *expad;

	fTail[0] = '\0';
	fTail[1] = '\0';

	(void) time(&gNowPlus1Hr);
	gNowMinus6Mon = gNowPlus1Hr - 15552000;
	gNowPlus1Hr += 3600;

	diritemv = dirp->vec;
#ifdef HAVE_SNPRINTF
	(void) snprintf(
		plugspec,
		sizeof(plugspec) - 1,
#else
	(void) sprintf(
		plugspec,
#endif
		"%%-%ds",
		(int) dirp->maxPlugLen
	);

	if (dirp->maxPlugLen < 29) {
		/* We have some extra space to work with,
		 * so we can space out the columns a little.
		 */
		expad = "  ";
	} else {
		expad = "";
	}

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

		if (diritemp->rlinkto != NULL) {
			if (linkedTo != 0) {
				l1 = "";
				l2 = "";
			} else {
				l1 = " -> ";
				l2 = diritemp->rlinkto;
			}
		} else {
			l1 = "";
			l2 = "";
		}

		LsDate(datestr, diritemp->mdtm);

		if (diritemp->size == kSizeUnknown) {
			*sizestr = '\0';
		} else {
#ifdef HAVE_SNPRINTF
			(void) snprintf(
				sizestr,
				sizeof(sizestr) - 1,
#else
			(void) sprintf(
				sizestr,
#endif
#if defined(HAVE_LONG_LONG) && defined(PRINTF_LONG_LONG)
				PRINTF_LONG_LONG,
#else
				"%ld",
#endif
				(longest_int) diritemp->size
			);
		}

#ifdef HAVE_SNPRINTF
		(void) snprintf(
			plugstr,
			sizeof(plugstr) - 1,
#else
		(void) sprintf(
			plugstr,
#endif
			plugspec,
			diritemp->plug
		);

		(void) fprintf(stream, "%s %12s %s%s %s%s%s%s%s\n",
			plugstr,
			sizestr,
			expad,
			datestr,
			expad,
			diritemp->relname,
			l1,
			l2,
			fTail
		);
		Trace(0, "%s %12s %s%s %s%s%s%s%s\n",
			plugstr,
			sizestr,
			expad,
			datestr,
			expad,
			diritemp->relname,
			l1,
			l2,
			fTail
		);
	}
}