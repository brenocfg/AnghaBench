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
 int* xmalloc (int) ; 

__attribute__((used)) static inline libvlc_media_list_path_t libvlc_media_list_path_with_root_index( int index )
{
    libvlc_media_list_path_t ret = xmalloc(sizeof(int)*2);
    ret[0] = index;
    ret[1] = -1;
    return ret;
}