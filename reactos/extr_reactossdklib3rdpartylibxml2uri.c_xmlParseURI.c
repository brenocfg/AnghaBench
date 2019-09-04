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

/* Variables and functions */
 int /*<<< orphan*/ * xmlCreateURI () ; 
 int /*<<< orphan*/  xmlFreeURI (int /*<<< orphan*/ *) ; 
 int xmlParse3986URIReference (int /*<<< orphan*/ *,char const*) ; 

xmlURIPtr
xmlParseURI(const char *str) {
    xmlURIPtr uri;
    int ret;

    if (str == NULL)
	return(NULL);
    uri = xmlCreateURI();
    if (uri != NULL) {
	ret = xmlParse3986URIReference(uri, str);
        if (ret) {
	    xmlFreeURI(uri);
	    return(NULL);
	}
    }
    return(uri);
}