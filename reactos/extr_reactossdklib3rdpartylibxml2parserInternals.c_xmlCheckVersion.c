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

/* Variables and functions */
 scalar_t__ LIBXML_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlInitParser () ; 

void
xmlCheckVersion(int version) {
    int myversion = (int) LIBXML_VERSION;

    xmlInitParser();

    if ((myversion / 10000) != (version / 10000)) {
	xmlGenericError(xmlGenericErrorContext,
		"Fatal: program compiled against libxml %d using libxml %d\n",
		(version / 10000), (myversion / 10000));
	fprintf(stderr,
		"Fatal: program compiled against libxml %d using libxml %d\n",
		(version / 10000), (myversion / 10000));
    }
    if ((myversion / 100) < (version / 100)) {
	xmlGenericError(xmlGenericErrorContext,
		"Warning: program compiled against libxml %d using older %d\n",
		(version / 100), (myversion / 100));
    }
}