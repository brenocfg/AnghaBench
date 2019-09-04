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
typedef  int /*<<< orphan*/  urlW ;
typedef  unsigned char WCHAR ;
typedef  unsigned char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 unsigned char* heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strchrW (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strncmpW (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static LPWSTR fix_url_value(LPCWSTR val)
{
    WCHAR *ret, *ptr;

    static const WCHAR urlW[] = {'u','r','l','('};

    if(strncmpW(val, urlW, sizeof(urlW)/sizeof(WCHAR)) || !strchrW(val, '\\'))
        return NULL;

    ret = heap_strdupW(val);

    for(ptr = ret; *ptr; ptr++) {
        if(*ptr == '\\')
            *ptr = '/';
    }

    return ret;
}