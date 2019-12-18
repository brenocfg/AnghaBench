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
 char* FromLocaleDup (char const*) ; 
 char* dlerror () ; 

char *vlc_dlerror(void)
{
    const char *errmsg = dlerror();
    return (errmsg != NULL) ? FromLocaleDup(errmsg) : NULL;
}