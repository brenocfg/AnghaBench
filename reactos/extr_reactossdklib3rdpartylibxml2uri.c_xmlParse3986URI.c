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
 int xmlParse3986Fragment (int /*<<< orphan*/ ,char const**) ; 
 int xmlParse3986HierPart (int /*<<< orphan*/ ,char const**) ; 
 int xmlParse3986Query (int /*<<< orphan*/ ,char const**) ; 
 int xmlParse3986Scheme (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
xmlParse3986URI(xmlURIPtr uri, const char *str) {
    int ret;

    ret = xmlParse3986Scheme(uri, &str);
    if (ret != 0) return(ret);
    if (*str != ':') {
	return(1);
    }
    str++;
    ret = xmlParse3986HierPart(uri, &str);
    if (ret != 0) return(ret);
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