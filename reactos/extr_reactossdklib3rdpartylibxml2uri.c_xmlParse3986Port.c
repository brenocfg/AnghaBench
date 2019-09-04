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
struct TYPE_3__ {unsigned int port; } ;

/* Variables and functions */
 unsigned int INT_MAX ; 
 scalar_t__ ISA_DIGIT (char const*) ; 

__attribute__((used)) static int
xmlParse3986Port(xmlURIPtr uri, const char **str)
{
    const char *cur = *str;
    unsigned port = 0; /* unsigned for defined overflow behavior */

    if (ISA_DIGIT(cur)) {
	while (ISA_DIGIT(cur)) {
	    port = port * 10 + (*cur - '0');

	    cur++;
	}
	if (uri != NULL)
	    uri->port = port & INT_MAX; /* port value modulo INT_MAX+1 */
	*str = cur;
	return(0);
    }
    return(1);
}