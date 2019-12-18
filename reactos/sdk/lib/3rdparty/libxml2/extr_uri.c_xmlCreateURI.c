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
typedef  int /*<<< orphan*/ * xmlURIPtr ;
typedef  int /*<<< orphan*/  xmlURI ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlURIErrMemory (char*) ; 

xmlURIPtr
xmlCreateURI(void) {
    xmlURIPtr ret;

    ret = (xmlURIPtr) xmlMalloc(sizeof(xmlURI));
    if (ret == NULL) {
        xmlURIErrMemory("creating URI structure\n");
	return(NULL);
    }
    memset(ret, 0, sizeof(xmlURI));
    return(ret);
}