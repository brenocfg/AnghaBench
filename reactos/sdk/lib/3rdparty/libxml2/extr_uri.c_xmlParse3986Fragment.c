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
struct TYPE_3__ {int cleanup; int /*<<< orphan*/ * fragment; } ;

/* Variables and functions */
 scalar_t__ ISA_PCHAR (char const*) ; 
 scalar_t__ IS_UNWISE (char const*) ; 
 int /*<<< orphan*/  NEXT (char const*) ; 
 int /*<<< orphan*/ * STRNDUP (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlURIUnescapeString (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlParse3986Fragment(xmlURIPtr uri, const char **str)
{
    const char *cur;

    if (str == NULL)
        return (-1);

    cur = *str;

    while ((ISA_PCHAR(cur)) || (*cur == '/') || (*cur == '?') ||
           (*cur == '[') || (*cur == ']') ||
           ((uri != NULL) && (uri->cleanup & 1) && (IS_UNWISE(cur))))
        NEXT(cur);
    if (uri != NULL) {
        if (uri->fragment != NULL)
            xmlFree(uri->fragment);
	if (uri->cleanup & 2)
	    uri->fragment = STRNDUP(*str, cur - *str);
	else
	    uri->fragment = xmlURIUnescapeString(*str, cur - *str, NULL);
    }
    *str = cur;
    return (0);
}