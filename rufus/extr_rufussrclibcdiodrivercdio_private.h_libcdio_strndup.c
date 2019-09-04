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
 scalar_t__ malloc (size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static inline char *libcdio_strndup(const char *s, size_t n)
{
    char *result;
    size_t len = strlen (s);
    if (n < len)
        len = n;
    result = (char *) malloc (len + 1);
    if (!result)
        return 0;
    result[len] = '\0';
    return (char *) strncpy (result, s, len);
}