#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlURIPtr ;
struct TYPE_10__ {int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 scalar_t__ ISA_PCHAR (char const*) ; 
 int /*<<< orphan*/  xmlCleanURI (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int xmlParse3986Authority (TYPE_1__*,char const**) ; 
 int xmlParse3986Fragment (TYPE_1__*,char const**) ; 
 int xmlParse3986PathAbEmpty (TYPE_1__*,char const**) ; 
 int xmlParse3986PathAbsolute (TYPE_1__*,char const**) ; 
 int xmlParse3986PathNoScheme (TYPE_1__*,char const**) ; 
 int xmlParse3986Query (TYPE_1__*,char const**) ; 

__attribute__((used)) static int
xmlParse3986RelativeRef(xmlURIPtr uri, const char *str) {
    int ret;

    if ((*str == '/') && (*(str + 1) == '/')) {
        str += 2;
	ret = xmlParse3986Authority(uri, &str);
	if (ret != 0) return(ret);
	ret = xmlParse3986PathAbEmpty(uri, &str);
	if (ret != 0) return(ret);
    } else if (*str == '/') {
	ret = xmlParse3986PathAbsolute(uri, &str);
	if (ret != 0) return(ret);
    } else if (ISA_PCHAR(str)) {
        ret = xmlParse3986PathNoScheme(uri, &str);
	if (ret != 0) return(ret);
    } else {
	/* path-empty is effectively empty */
	if (uri != NULL) {
	    if (uri->path != NULL) xmlFree(uri->path);
	    uri->path = NULL;
	}
    }

    if (*str == '?') {
	str++;
	ret = xmlParse3986Query(uri, &str);
	if (ret != 0) return(ret);
    }
    if (*str == '#') {
	str++;
	ret = xmlParse3986Fragment(uri, &str);
	if (ret != 0) return(ret);
    }
    if (*str != 0) {
	xmlCleanURI(uri);
	return(1);
    }
    return(0);
}