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
 char* encode_URI_bytes (char const*,size_t*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

char *vlc_uri_encode (const char *str)
{
    size_t len = strlen (str);
    char *ret = encode_URI_bytes (str, &len);
    if (likely(ret != NULL))
        ret[len] = '\0';
    return ret;
}