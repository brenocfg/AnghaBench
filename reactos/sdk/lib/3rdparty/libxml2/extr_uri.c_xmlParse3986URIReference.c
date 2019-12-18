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
typedef  int /*<<< orphan*/  xmlURIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  xmlCleanURI (int /*<<< orphan*/ ) ; 
 int xmlParse3986RelativeRef (int /*<<< orphan*/ ,char const*) ; 
 int xmlParse3986URI (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
xmlParse3986URIReference(xmlURIPtr uri, const char *str) {
    int ret;

    if (str == NULL)
	return(-1);
    xmlCleanURI(uri);

    /*
     * Try first to parse absolute refs, then fallback to relative if
     * it fails.
     */
    ret = xmlParse3986URI(uri, str);
    if (ret != 0) {
	xmlCleanURI(uri);
        ret = xmlParse3986RelativeRef(uri, str);
	if (ret != 0) {
	    xmlCleanURI(uri);
	    return(ret);
	}
    }
    return(0);
}