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
 int xmlParse3986Host (int /*<<< orphan*/ ,char const**) ; 
 int xmlParse3986Port (int /*<<< orphan*/ ,char const**) ; 
 int xmlParse3986Userinfo (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
xmlParse3986Authority(xmlURIPtr uri, const char **str)
{
    const char *cur;
    int ret;

    cur = *str;
    /*
     * try to parse an userinfo and check for the trailing @
     */
    ret = xmlParse3986Userinfo(uri, &cur);
    if ((ret != 0) || (*cur != '@'))
        cur = *str;
    else
        cur++;
    ret = xmlParse3986Host(uri, &cur);
    if (ret != 0) return(ret);
    if (*cur == ':') {
        cur++;
        ret = xmlParse3986Port(uri, &cur);
	if (ret != 0) return(ret);
    }
    *str = cur;
    return(0);
}