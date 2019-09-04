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
typedef  char xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (char*) ; 
 char* xmlStrdup (char const*) ; 
 char* xmlStrndup (char const*,int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlChar *
xmlSplitQName2(const xmlChar *name, xmlChar **prefix) {
    int len = 0;
    xmlChar *ret = NULL;

    if (prefix == NULL) return(NULL);
    *prefix = NULL;
    if (name == NULL) return(NULL);

#ifndef XML_XML_NAMESPACE
    /* xml: prefix is not really a namespace */
    if ((name[0] == 'x') && (name[1] == 'm') &&
        (name[2] == 'l') && (name[3] == ':'))
	return(NULL);
#endif

    /* nasty but valid */
    if (name[0] == ':')
	return(NULL);

    /*
     * we are not trying to validate but just to cut, and yes it will
     * work even if this is as set of UTF-8 encoded chars
     */
    while ((name[len] != 0) && (name[len] != ':'))
	len++;

    if (name[len] == 0)
	return(NULL);

    *prefix = xmlStrndup(name, len);
    if (*prefix == NULL) {
	xmlTreeErrMemory("QName split");
	return(NULL);
    }
    ret = xmlStrdup(&name[len + 1]);
    if (ret == NULL) {
	xmlTreeErrMemory("QName split");
	if (*prefix != NULL) {
	    xmlFree(*prefix);
	    *prefix = NULL;
	}
	return(NULL);
    }

    return(ret);
}