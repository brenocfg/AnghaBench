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
typedef  scalar_t__ xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  xmlErrMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlMallocAtomic (int) ; 

xmlChar *
xmlStrndup(const xmlChar *cur, int len) {
    xmlChar *ret;

    if ((cur == NULL) || (len < 0)) return(NULL);
    ret = (xmlChar *) xmlMallocAtomic((len + 1) * sizeof(xmlChar));
    if (ret == NULL) {
        xmlErrMemory(NULL, NULL);
        return(NULL);
    }
    memcpy(ret, cur, len * sizeof(xmlChar));
    ret[len] = 0;
    return(ret);
}