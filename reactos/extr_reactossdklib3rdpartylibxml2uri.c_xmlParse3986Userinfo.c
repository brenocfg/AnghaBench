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
struct TYPE_3__ {int cleanup; int /*<<< orphan*/ * user; } ;

/* Variables and functions */
 scalar_t__ ISA_PCT_ENCODED (char const*) ; 
 scalar_t__ ISA_SUB_DELIM (char const*) ; 
 scalar_t__ ISA_UNRESERVED (char const*) ; 
 int /*<<< orphan*/  NEXT (char const*) ; 
 int /*<<< orphan*/ * STRNDUP (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlURIUnescapeString (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlParse3986Userinfo(xmlURIPtr uri, const char **str)
{
    const char *cur;

    cur = *str;
    while (ISA_UNRESERVED(cur) || ISA_PCT_ENCODED(cur) ||
           ISA_SUB_DELIM(cur) || (*cur == ':'))
	NEXT(cur);
    if (*cur == '@') {
	if (uri != NULL) {
	    if (uri->user != NULL) xmlFree(uri->user);
	    if (uri->cleanup & 2)
		uri->user = STRNDUP(*str, cur - *str);
	    else
		uri->user = xmlURIUnescapeString(*str, cur - *str, NULL);
	}
	*str = cur;
	return(0);
    }
    return(1);
}