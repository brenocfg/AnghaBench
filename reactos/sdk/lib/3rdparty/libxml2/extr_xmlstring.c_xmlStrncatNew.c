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
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__* xmlStrdup (scalar_t__ const*) ; 
 int xmlStrlen (scalar_t__ const*) ; 
 scalar_t__* xmlStrndup (scalar_t__ const*,int) ; 

xmlChar *
xmlStrncatNew(const xmlChar *str1, const xmlChar *str2, int len) {
    int size;
    xmlChar *ret;

    if (len < 0) {
        len = xmlStrlen(str2);
        if (len < 0)
            return(NULL);
    }
    if ((str2 == NULL) || (len == 0))
        return(xmlStrdup(str1));
    if (str1 == NULL)
        return(xmlStrndup(str2, len));

    size = xmlStrlen(str1);
    if (size < 0)
        return(NULL);
    ret = (xmlChar *) xmlMalloc((size + len + 1) * sizeof(xmlChar));
    if (ret == NULL) {
        xmlErrMemory(NULL, NULL);
        return(xmlStrndup(str1, size));
    }
    memcpy(ret, str1, size * sizeof(xmlChar));
    memcpy(&ret[size], str2, len * sizeof(xmlChar));
    ret[size + len] = 0;
    return(ret);
}