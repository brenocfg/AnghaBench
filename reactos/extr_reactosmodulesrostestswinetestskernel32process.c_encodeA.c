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
 char* grab_memory (size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char* encodeA(const char* str)
{
    char*       ptr;
    size_t      len,i;

    if (!str) return "";
    len = strlen(str) + 1;
    ptr = grab_memory(len * 2 + 1);
    for (i = 0; i < len; i++)
        sprintf(&ptr[i * 2], "%02x", (unsigned char)str[i]);
    ptr[2 * len] = '\0';
    return ptr;
}