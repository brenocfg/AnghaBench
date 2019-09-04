#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int string_len; int /*<<< orphan*/  cookies; scalar_t__ cnt; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ cookie_set_t ;
typedef  int /*<<< orphan*/  cookieW ;
typedef  char WCHAR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTERNET_COOKIE_HTTPONLY ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cookie_cs ; 
 int /*<<< orphan*/  cookie_set_to_string (TYPE_1__*,char*) ; 
 scalar_t__ get_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  substrz (char const*) ; 

DWORD get_cookie_header(const WCHAR *host, const WCHAR *path, WCHAR **ret)
{
    cookie_set_t cookie_set = {0};
    DWORD res;

    static const WCHAR cookieW[] = {'C','o','o','k','i','e',':',' '};

    EnterCriticalSection(&cookie_cs);

    res = get_cookie(substrz(host), substrz(path), INTERNET_COOKIE_HTTPONLY, &cookie_set);
    if(res != ERROR_SUCCESS) {
        LeaveCriticalSection(&cookie_cs);
        return res;
    }

    if(cookie_set.cnt) {
        WCHAR *header, *ptr;

        ptr = header = heap_alloc(sizeof(cookieW) + (cookie_set.string_len + 3 /* crlf0 */) * sizeof(WCHAR));
        if(header) {
            memcpy(ptr, cookieW, sizeof(cookieW));
            ptr += sizeof(cookieW)/sizeof(*cookieW);

            cookie_set_to_string(&cookie_set, ptr);
            heap_free(cookie_set.cookies);
            ptr += cookie_set.string_len;

            *ptr++ = '\r';
            *ptr++ = '\n';
            *ptr++ = 0;

            *ret = header;
        }else {
            res = ERROR_NOT_ENOUGH_MEMORY;
        }
    }else {
        *ret = NULL;
    }

    LeaveCriticalSection(&cookie_cs);
    return res;
}