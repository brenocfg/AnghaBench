#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlURIPtr ;
struct TYPE_3__ {int cleanup; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int /*<<< orphan*/ * STRNDUP (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int xmlParse3986Segment (char const**,char,int) ; 
 int /*<<< orphan*/ * xmlURIUnescapeString (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlParse3986PathNoScheme(xmlURIPtr uri, const char **str)
{
    const char *cur;
    int ret;

    cur = *str;

    ret = xmlParse3986Segment(&cur, ':', 0);
    if (ret != 0) return(ret);
    while (*cur == '/') {
        cur++;
	ret = xmlParse3986Segment(&cur, 0, 1);
	if (ret != 0) return(ret);
    }
    if (uri != NULL) {
	if (uri->path != NULL) xmlFree(uri->path);
        if (cur != *str) {
            if (uri->cleanup & 2)
                uri->path = STRNDUP(*str, cur - *str);
            else
                uri->path = xmlURIUnescapeString(*str, cur - *str, NULL);
        } else {
            uri->path = NULL;
        }
    }
    *str = cur;
    return (0);
}