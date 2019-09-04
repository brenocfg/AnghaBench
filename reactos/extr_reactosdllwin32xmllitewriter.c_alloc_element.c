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
typedef  int /*<<< orphan*/  xmlwriter ;
struct element {int len; scalar_t__* qname; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  strcatW (scalar_t__*,char const*) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,char const*) ; 
 int strlenW (char const*) ; 
 void* writer_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct element *alloc_element(xmlwriter *writer, const WCHAR *prefix, const WCHAR *local)
{
    struct element *ret;
    int len;

    ret = writer_alloc(writer, sizeof(*ret));
    if (!ret) return ret;

    len = prefix ? strlenW(prefix) + 1 /* ':' */ : 0;
    len += strlenW(local);

    ret->qname = writer_alloc(writer, (len + 1)*sizeof(WCHAR));
    ret->len = len;
    if (prefix) {
        static const WCHAR colonW[] = {':',0};
        strcpyW(ret->qname, prefix);
        strcatW(ret->qname, colonW);
    }
    else
        ret->qname[0] = 0;
    strcatW(ret->qname, local);

    return ret;
}