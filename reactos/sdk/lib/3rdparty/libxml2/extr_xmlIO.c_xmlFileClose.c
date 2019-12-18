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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  xmlIOErr (int /*<<< orphan*/ ,char*) ; 

int
xmlFileClose (void * context) {
    FILE *fil;
    int ret;

    if (context == NULL)
        return(-1);
    fil = (FILE *) context;
    if ((fil == stdout) || (fil == stderr)) {
        ret = fflush(fil);
	if (ret < 0)
	    xmlIOErr(0, "fflush()");
	return(0);
    }
    if (fil == stdin)
	return(0);
    ret = ( fclose((FILE *) context) == EOF ) ? -1 : 0;
    if (ret < 0)
        xmlIOErr(0, "fclose()");
    return(ret);
}