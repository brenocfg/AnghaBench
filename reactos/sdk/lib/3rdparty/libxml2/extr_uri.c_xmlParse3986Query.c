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
struct TYPE_3__ {int cleanup; int /*<<< orphan*/ * query_raw; int /*<<< orphan*/ * query; } ;

/* Variables and functions */
 scalar_t__ ISA_PCHAR (char const*) ; 
 scalar_t__ IS_UNWISE (char const*) ; 
 int /*<<< orphan*/  NEXT (char const*) ; 
 void* STRNDUP (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlURIUnescapeString (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlParse3986Query(xmlURIPtr uri, const char **str)
{
    const char *cur;

    if (str == NULL)
        return (-1);

    cur = *str;

    while ((ISA_PCHAR(cur)) || (*cur == '/') || (*cur == '?') ||
           ((uri != NULL) && (uri->cleanup & 1) && (IS_UNWISE(cur))))
        NEXT(cur);
    if (uri != NULL) {
        if (uri->query != NULL)
            xmlFree(uri->query);
	if (uri->cleanup & 2)
	    uri->query = STRNDUP(*str, cur - *str);
	else
	    uri->query = xmlURIUnescapeString(*str, cur - *str, NULL);

	/* Save the raw bytes of the query as well.
	 * See: http://mail.gnome.org/archives/xml/2007-April/thread.html#00114
	 */
	if (uri->query_raw != NULL)
	    xmlFree (uri->query_raw);
	uri->query_raw = STRNDUP (*str, cur - *str);
    }
    *str = cur;
    return (0);
}