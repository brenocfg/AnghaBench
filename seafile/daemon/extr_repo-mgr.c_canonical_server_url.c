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
 char* g_strdup (char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
canonical_server_url (const char *url_in)
{
    char *url = g_strdup(url_in);
    int len = strlen(url);

    if (url[len - 1] == '/')
        url[len - 1] = 0;

    return url;
}