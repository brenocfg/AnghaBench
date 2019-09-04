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
typedef  scalar_t__ xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UNRESERVED (scalar_t__) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__* xmlSaveUriRealloc (scalar_t__*,int*) ; 
 int /*<<< orphan*/  xmlStrchr (scalar_t__ const*,scalar_t__) ; 
 scalar_t__* xmlStrdup (scalar_t__ const*) ; 
 int xmlStrlen (scalar_t__ const*) ; 
 int /*<<< orphan*/  xmlURIErrMemory (char*) ; 

xmlChar *
xmlURIEscapeStr(const xmlChar *str, const xmlChar *list) {
    xmlChar *ret, ch;
    xmlChar *temp;
    const xmlChar *in;
    int len, out;

    if (str == NULL)
	return(NULL);
    if (str[0] == 0)
	return(xmlStrdup(str));
    len = xmlStrlen(str);
    if (!(len > 0)) return(NULL);

    len += 20;
    ret = (xmlChar *) xmlMallocAtomic(len);
    if (ret == NULL) {
        xmlURIErrMemory("escaping URI value\n");
	return(NULL);
    }
    in = (const xmlChar *) str;
    out = 0;
    while(*in != 0) {
	if (len - out <= 3) {
            temp = xmlSaveUriRealloc(ret, &len);
	    if (temp == NULL) {
                xmlURIErrMemory("escaping URI value\n");
		xmlFree(ret);
		return(NULL);
	    }
	    ret = temp;
	}

	ch = *in;

	if ((ch != '@') && (!IS_UNRESERVED(ch)) && (!xmlStrchr(list, ch))) {
	    unsigned char val;
	    ret[out++] = '%';
	    val = ch >> 4;
	    if (val <= 9)
		ret[out++] = '0' + val;
	    else
		ret[out++] = 'A' + val - 0xA;
	    val = ch & 0xF;
	    if (val <= 9)
		ret[out++] = '0' + val;
	    else
		ret[out++] = 'A' + val - 0xA;
	    in++;
	} else {
	    ret[out++] = *in++;
	}

    }
    ret[out] = 0;
    return(ret);
}