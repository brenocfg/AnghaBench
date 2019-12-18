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
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void *vlc_dlsym(void *handle, const char *psz_function)
{
    char buf[strlen(psz_function) + 2];
    buf[0] = '_';
    strcpy(buf + 1, psz_function);
    return dlsym( handle, buf );
}