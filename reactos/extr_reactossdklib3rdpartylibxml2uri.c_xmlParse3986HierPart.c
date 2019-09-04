#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlURIPtr ;
struct TYPE_7__ {int port; int /*<<< orphan*/ * path; int /*<<< orphan*/ * server; } ;

/* Variables and functions */
 scalar_t__ ISA_PCHAR (char const*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int xmlParse3986Authority (TYPE_1__*,char const**) ; 
 int xmlParse3986PathAbEmpty (TYPE_1__*,char const**) ; 
 int xmlParse3986PathAbsolute (TYPE_1__*,char const**) ; 
 int xmlParse3986PathRootless (TYPE_1__*,char const**) ; 

__attribute__((used)) static int
xmlParse3986HierPart(xmlURIPtr uri, const char **str)
{
    const char *cur;
    int ret;

    cur = *str;

    if ((*cur == '/') && (*(cur + 1) == '/')) {
        cur += 2;
	ret = xmlParse3986Authority(uri, &cur);
	if (ret != 0) return(ret);
	if (uri->server == NULL)
	    uri->port = -1;
	ret = xmlParse3986PathAbEmpty(uri, &cur);
	if (ret != 0) return(ret);
	*str = cur;
	return(0);
    } else if (*cur == '/') {
        ret = xmlParse3986PathAbsolute(uri, &cur);
	if (ret != 0) return(ret);
    } else if (ISA_PCHAR(cur)) {
        ret = xmlParse3986PathRootless(uri, &cur);
	if (ret != 0) return(ret);
    } else {
	/* path-empty is effectively empty */
	if (uri != NULL) {
	    if (uri->path != NULL) xmlFree(uri->path);
	    uri->path = NULL;
	}
    }
    *str = cur;
    return (0);
}