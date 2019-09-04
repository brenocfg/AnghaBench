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

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static inline void stabbuf_append(char **buf, unsigned *buf_size, const char *str)
{
    unsigned str_len, buf_len;

    str_len = strlen(str);
    buf_len = strlen(*buf);

    if(str_len+buf_len >= *buf_size) {
        *buf_size += buf_len + str_len;
        *buf = HeapReAlloc(GetProcessHeap(), 0, *buf, *buf_size);
    }

    strcpy(*buf+buf_len, str);
}