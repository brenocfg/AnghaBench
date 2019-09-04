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
struct TYPE_3__ {int /*<<< orphan*/ * scheme; } ;

/* Variables and functions */
 scalar_t__ ISA_ALPHA (char const*) ; 
 scalar_t__ ISA_DIGIT (char const*) ; 
 int /*<<< orphan*/ * STRNDUP (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlParse3986Scheme(xmlURIPtr uri, const char **str) {
    const char *cur;

    if (str == NULL)
	return(-1);

    cur = *str;
    if (!ISA_ALPHA(cur))
	return(2);
    cur++;
    while (ISA_ALPHA(cur) || ISA_DIGIT(cur) ||
           (*cur == '+') || (*cur == '-') || (*cur == '.')) cur++;
    if (uri != NULL) {
	if (uri->scheme != NULL) xmlFree(uri->scheme);
	uri->scheme = STRNDUP(*str, cur - *str);
    }
    *str = cur;
    return(0);
}