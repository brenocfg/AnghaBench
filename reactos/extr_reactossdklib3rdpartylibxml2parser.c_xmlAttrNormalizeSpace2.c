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
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
typedef  int xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xmlAttrNormalizeSpace (int*,int*) ; 
 int /*<<< orphan*/  xmlErrMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* xmlStrndup (int*,int) ; 

__attribute__((used)) static const xmlChar *
xmlAttrNormalizeSpace2(xmlParserCtxtPtr ctxt, xmlChar *src, int *len)
{
    int i;
    int remove_head = 0;
    int need_realloc = 0;
    const xmlChar *cur;

    if ((ctxt == NULL) || (src == NULL) || (len == NULL))
        return(NULL);
    i = *len;
    if (i <= 0)
        return(NULL);

    cur = src;
    while (*cur == 0x20) {
        cur++;
	remove_head++;
    }
    while (*cur != 0) {
	if (*cur == 0x20) {
	    cur++;
	    if ((*cur == 0x20) || (*cur == 0)) {
	        need_realloc = 1;
		break;
	    }
	} else
	    cur++;
    }
    if (need_realloc) {
        xmlChar *ret;

	ret = xmlStrndup(src + remove_head, i - remove_head + 1);
	if (ret == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    return(NULL);
	}
	xmlAttrNormalizeSpace(ret, ret);
	*len = (int) strlen((const char *)ret);
        return(ret);
    } else if (remove_head) {
        *len -= remove_head;
        memmove(src, src + remove_head, 1 + *len);
	return(src);
    }
    return(NULL);
}