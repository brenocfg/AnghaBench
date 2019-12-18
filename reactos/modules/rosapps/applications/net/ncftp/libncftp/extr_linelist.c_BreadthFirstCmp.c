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
struct TYPE_2__ {char* relname; } ;
typedef  TYPE_1__* FileInfoPtr ;

/* Variables and functions */
 int strcmp (char*,char*) ; 
 int strcoll (char*,char*) ; 

__attribute__((used)) static int
BreadthFirstCmp(const void *a, const void *b)
{
	FileInfoPtr *fipa, *fipb;
	char *cp, *cpa, *cpb;
	int depth, deptha, depthb;
	int c;

	fipa = (FileInfoPtr *) a;
	fipb = (FileInfoPtr *) b;

	cpa = (**fipa).relname;
	cpb = (**fipb).relname;

	for (cp = cpa, depth = 0;;) {
		c = *cp++;
		if (c == '\0')
			break;
		if ((c == '/') || (c == '\\')) {
			depth++;
		}
	}
	deptha = depth;

	for (cp = cpb, depth = 0;;) {
		c = *cp++;
		if (c == '\0')
			break;
		if ((c == '/') || (c == '\\')) {
			depth++;
		}
	}
	depthb = depth;

	if (deptha < depthb)
		return (-1);
	else if (deptha > depthb)
		return (1);

#ifdef HAVE_SETLOCALE
	return (strcoll(cpa, cpb));
#else
	return (strcmp(cpa, cpb));
#endif
}