#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlURIPtr ;
struct TYPE_4__ {char* path; } ;
typedef  TYPE_1__ xmlURI ;
typedef  char xmlChar ;
typedef  int /*<<< orphan*/  temp ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* xmlCanonicPath (char const*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlFreeURI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlParseURI (char const*) ; 
 char* xmlSaveUri (TYPE_1__*) ; 
 char* xmlStrdup (char const*) ; 

xmlChar *
xmlPathToURI(const xmlChar *path)
{
    xmlURIPtr uri;
    xmlURI temp;
    xmlChar *ret, *cal;

    if (path == NULL)
        return(NULL);

    if ((uri = xmlParseURI((const char *) path)) != NULL) {
	xmlFreeURI(uri);
	return xmlStrdup(path);
    }
    cal = xmlCanonicPath(path);
    if (cal == NULL)
        return(NULL);
#if defined(_WIN32) && !defined(__CYGWIN__)
    /* xmlCanonicPath can return an URI on Windows (is that the intended behaviour?)
       If 'cal' is a valid URI allready then we are done here, as continuing would make
       it invalid. */
    if ((uri = xmlParseURI((const char *) cal)) != NULL) {
	xmlFreeURI(uri);
	return cal;
    }
    /* 'cal' can contain a relative path with backslashes. If that is processed
       by xmlSaveURI, they will be escaped and the external entity loader machinery
       will fail. So convert them to slashes. Misuse 'ret' for walking. */
    ret = cal;
    while (*ret != '\0') {
	if (*ret == '\\')
	    *ret = '/';
	ret++;
    }
#endif
    memset(&temp, 0, sizeof(temp));
    temp.path = (char *) cal;
    ret = xmlSaveUri(&temp);
    xmlFree(cal);
    return(ret);
}