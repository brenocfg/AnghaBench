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
 int libvlc_media_list_path_depth (int* const) ; 
 int /*<<< orphan*/  memcpy (int*,int* const,int) ; 
 int* xmalloc (int) ; 

__attribute__((used)) static inline libvlc_media_list_path_t libvlc_media_list_path_copy_by_appending( const libvlc_media_list_path_t path, int index )
{
    libvlc_media_list_path_t ret;
    int old_depth = libvlc_media_list_path_depth( path );
    ret = xmalloc( sizeof(int) * (old_depth + 2) );
    memcpy( ret, path, sizeof(int) * old_depth );
    ret[old_depth] = index;
    ret[old_depth+1] = -1;
    return ret;
}