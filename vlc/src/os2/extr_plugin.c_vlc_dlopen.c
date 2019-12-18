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
 int RTLD_LAZY ; 
 int RTLD_NOW ; 
 char* ToLocaleDup (char const*) ; 
 void* dlopen (char*,int const) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void *vlc_dlopen(const char *psz_file, bool lazy )
{
    const int flags = lazy ? RTLD_LAZY : RTLD_NOW;
    char *path = ToLocaleDup( psz_file );
    if (unlikely(path == NULL))
        return NULL;

    void *handle = dlopen( path, flags );
    free( path );
    return handle;
}