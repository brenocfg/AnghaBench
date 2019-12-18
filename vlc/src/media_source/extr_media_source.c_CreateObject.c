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
typedef  char const vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 void* malloc (size_t) ; 
 void* vlc_custom_create (char const*,size_t,char const*) ; 

__attribute__((used)) static void *
CreateObject(vlc_object_t *parent, size_t length, const char *typename)
{
#ifdef TEST_MEDIA_SOURCE
    VLC_UNUSED(parent);
    VLC_UNUSED(typename);
    return malloc(length);
#else
    return vlc_custom_create(parent, length, typename);
#endif
}