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
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 char* strdup (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
vlc_playlist_item_meta_CopyString(const char **to, const char *from)
{
    if (from)
    {
        *to = strdup(from);
        if (unlikely(!*to))
            return VLC_ENOMEM;
    }
    else
        *to = NULL;
    return VLC_SUCCESS;
}