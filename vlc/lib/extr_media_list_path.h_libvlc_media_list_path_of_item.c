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
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_path_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_path_empty () ; 

__attribute__((used)) static inline libvlc_media_list_path_t libvlc_media_list_path_of_item( libvlc_media_list_t * p_mlist, libvlc_media_t * p_md )
{
    libvlc_media_list_path_t path = libvlc_media_list_path_empty();
    libvlc_media_list_path_t ret;
    ret = get_path_rec( path, p_mlist, p_md );
    free( path );
    return ret;
}