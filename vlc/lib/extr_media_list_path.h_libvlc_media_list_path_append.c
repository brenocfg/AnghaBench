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
typedef  int* libvlc_media_list_path_t ;

/* Variables and functions */
 int libvlc_media_list_path_depth (int*) ; 
 int* xrealloc (int*,int) ; 

__attribute__((used)) static inline void libvlc_media_list_path_append( libvlc_media_list_path_t * p_path, int index )
{
    int old_depth = libvlc_media_list_path_depth( *p_path );
    *p_path = xrealloc( *p_path, sizeof(int)*(old_depth+2));
    *p_path[old_depth] = index;
    *p_path[old_depth+1] = -1;
}