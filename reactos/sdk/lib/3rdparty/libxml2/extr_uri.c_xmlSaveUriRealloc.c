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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int MAX_URI_LENGTH ; 
 scalar_t__ xmlRealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlURIErrMemory (char*) ; 

__attribute__((used)) static xmlChar *
xmlSaveUriRealloc(xmlChar *ret, int *max) {
    xmlChar *temp;
    int tmp;

    if (*max > MAX_URI_LENGTH) {
        xmlURIErrMemory("reaching arbitrary MAX_URI_LENGTH limit\n");
        return(NULL);
    }
    tmp = *max * 2;
    temp = (xmlChar *) xmlRealloc(ret, (tmp + 1));
    if (temp == NULL) {
        xmlURIErrMemory("saving URI\n");
        return(NULL);
    }
    *max = tmp;
    return(temp);
}