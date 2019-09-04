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
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  URL_UNESCAPE_INPLACE ; 
 int /*<<< orphan*/  UrlUnescapeW (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gecko_path ; 
 size_t gecko_path_len ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_strdupUtoW (char const*) ; 
 int /*<<< orphan*/  strcmpiW (char*,int /*<<< orphan*/ ) ; 
 size_t strlenW (char*) ; 

BOOL is_gecko_path(const char *path)
{
    WCHAR *buf, *ptr;
    BOOL ret;

    buf = heap_strdupUtoW(path);
    if(!buf || strlenW(buf) < gecko_path_len)
        return FALSE;

    for(ptr = buf; *ptr; ptr++) {
        if(*ptr == '\\')
            *ptr = '/';
    }

    UrlUnescapeW(buf, NULL, NULL, URL_UNESCAPE_INPLACE);
    buf[gecko_path_len] = 0;

    ret = !strcmpiW(buf, gecko_path);
    heap_free(buf);
    return ret;
}