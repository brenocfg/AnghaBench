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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int nFileInfos; TYPE_1__** vec; scalar_t__ maxFileLen; } ;
struct TYPE_5__ {char* relname; char type; scalar_t__ relnameLen; } ;
typedef  TYPE_1__** FileInfoVec ;
typedef  TYPE_1__* FileInfoPtr ;
typedef  TYPE_3__* FileInfoListPtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Trace (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int gScreenColumns ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
LsC(FileInfoListPtr dirp, int endChars, FILE *stream)
{
	char buf[400];
	char buf2[400];
	int ncol, nrow;
	int i, j, k, l;
	int colw;
	int n;
	FileInfoVec itemv;
	FileInfoPtr itemp;
	char *cp1, *cp2, *lim;
	int screenColumns;

	screenColumns = gScreenColumns;
	if (screenColumns > 400)
		screenColumns = 400;
	ncol = (screenColumns - 1) / ((int) dirp->maxFileLen + 2 + /*1or0*/ endChars);
	if (ncol < 1)
		ncol = 1;
	colw = (screenColumns - 1) / ncol;
	n = dirp->nFileInfos;
	nrow = n / ncol;
	if ((n % ncol) != 0)
		nrow++;

	for (i=0; i<(int) sizeof(buf2); i++)
		buf2[i] = ' ';

	itemv = dirp->vec;

	for (j=0; j<nrow; j++) {
		(void) memcpy(buf, buf2, sizeof(buf));
		for (i=0, k=j, l=0; i<ncol; i++, k += nrow, l += colw) {
			if (k >= n)
				continue;
			itemp = itemv[k];
			cp1 = buf + l;
			lim = cp1 + (int) (itemp->relnameLen);
			cp2 = itemp->relname;
			while (cp1 < lim)
				*cp1++ = *cp2++;
			if (endChars != 0) {
				if (itemp->type == 'l') {
					/* Regular ls always uses @
					 * for a symlink tail, even if
					 * the linked item is a directory.
					 */
					*cp1++ = '@';
				} else if (itemp->type == 'd') {
					*cp1++ = '/';
				}
			}
		}
		for (cp1 = buf + sizeof(buf); *--cp1 == ' '; ) {}
		++cp1;
		*cp1++ = '\n';
		*cp1 = '\0';
		(void) fprintf(stream, "%s", buf);
		Trace(0, "%s", buf);
	}
}