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
typedef  int xmlChar ;

/* Variables and functions */

__attribute__((used)) static xmlChar *
xmlAttrNormalizeSpace(const xmlChar *src, xmlChar *dst)
{
    if ((src == NULL) || (dst == NULL))
        return(NULL);

    while (*src == 0x20) src++;
    while (*src != 0) {
	if (*src == 0x20) {
	    while (*src == 0x20) src++;
	    if (*src != 0)
		*dst++ = 0x20;
	} else {
	    *dst++ = *src++;
	}
    }
    *dst = 0;
    if (dst == src)
       return(NULL);
    return(dst);
}