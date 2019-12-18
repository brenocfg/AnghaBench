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
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/ * vlc_uri_decode (char*) ; 

char *vlc_uri_decode_duplicate (const char *str)
{
    char *buf = strdup (str);
    if (vlc_uri_decode (buf) == NULL)
    {
        free (buf);
        buf = NULL;
    }
    return buf;
}