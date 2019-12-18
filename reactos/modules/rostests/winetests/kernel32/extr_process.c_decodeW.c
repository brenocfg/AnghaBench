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

/* Variables and functions */
 int decode_char (char const) ; 
 scalar_t__ grab_memory (size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static WCHAR*   decodeW(const char* str)
{
    size_t      len;
    WCHAR*      ptr;
    int         i;

    len = strlen(str) / 4;
    if (!len--) return NULL;
    ptr = (WCHAR*)grab_memory(len * 2 + 1);
    for (i = 0; i < len; i++)
        ptr[i] = (decode_char(str[4 * i]) << 12) |
            (decode_char(str[4 * i + 1]) << 8) |
            (decode_char(str[4 * i + 2]) << 4) |
            (decode_char(str[4 * i + 3]) << 0);
    ptr[len] = '\0';
    return ptr;
}