#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlURIPtr ;
struct TYPE_6__ {int cleanup; } ;

/* Variables and functions */
 TYPE_1__* xmlCreateURI () ; 
 int /*<<< orphan*/  xmlFreeURI (TYPE_1__*) ; 
 int xmlParseURIReference (TYPE_1__*,char const*) ; 

xmlURIPtr
xmlParseURIRaw(const char *str, int raw) {
    xmlURIPtr uri;
    int ret;

    if (str == NULL)
	return(NULL);
    uri = xmlCreateURI();
    if (uri != NULL) {
        if (raw) {
	    uri->cleanup |= 2;
	}
	ret = xmlParseURIReference(uri, str);
        if (ret) {
	    xmlFreeURI(uri);
	    return(NULL);
	}
    }
    return(uri);
}