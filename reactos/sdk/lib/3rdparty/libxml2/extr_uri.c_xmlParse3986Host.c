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
struct TYPE_3__ {int cleanup; int /*<<< orphan*/ * server; int /*<<< orphan*/ * authority; } ;

/* Variables and functions */
 scalar_t__ ISA_DIGIT (char const*) ; 
 scalar_t__ ISA_PCT_ENCODED (char const*) ; 
 scalar_t__ ISA_SUB_DELIM (char const*) ; 
 scalar_t__ ISA_UNRESERVED (char const*) ; 
 int /*<<< orphan*/  NEXT (char const*) ; 
 int /*<<< orphan*/ * STRNDUP (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlParse3986DecOctet (char const**) ; 
 int /*<<< orphan*/ * xmlURIUnescapeString (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlParse3986Host(xmlURIPtr uri, const char **str)
{
    const char *cur = *str;
    const char *host;

    host = cur;
    /*
     * IPv6 and future adressing scheme are enclosed between brackets
     */
    if (*cur == '[') {
        cur++;
	while ((*cur != ']') && (*cur != 0))
	    cur++;
	if (*cur != ']')
	    return(1);
	cur++;
	goto found;
    }
    /*
     * try to parse an IPv4
     */
    if (ISA_DIGIT(cur)) {
        if (xmlParse3986DecOctet(&cur) != 0)
	    goto not_ipv4;
	if (*cur != '.')
	    goto not_ipv4;
	cur++;
        if (xmlParse3986DecOctet(&cur) != 0)
	    goto not_ipv4;
	if (*cur != '.')
	    goto not_ipv4;
        if (xmlParse3986DecOctet(&cur) != 0)
	    goto not_ipv4;
	if (*cur != '.')
	    goto not_ipv4;
        if (xmlParse3986DecOctet(&cur) != 0)
	    goto not_ipv4;
	goto found;
not_ipv4:
        cur = *str;
    }
    /*
     * then this should be a hostname which can be empty
     */
    while (ISA_UNRESERVED(cur) || ISA_PCT_ENCODED(cur) || ISA_SUB_DELIM(cur))
        NEXT(cur);
found:
    if (uri != NULL) {
	if (uri->authority != NULL) xmlFree(uri->authority);
	uri->authority = NULL;
	if (uri->server != NULL) xmlFree(uri->server);
	if (cur != host) {
	    if (uri->cleanup & 2)
		uri->server = STRNDUP(host, cur - host);
	    else
		uri->server = xmlURIUnescapeString(host, cur - host, NULL);
	} else
	    uri->server = NULL;
    }
    *str = cur;
    return(0);
}