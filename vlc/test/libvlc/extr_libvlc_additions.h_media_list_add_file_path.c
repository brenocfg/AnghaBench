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
typedef  void libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_list_add_media (int /*<<< orphan*/ *,void*) ; 
 void* libvlc_media_new_location (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  libvlc_media_release (void*) ; 

__attribute__((used)) static void* media_list_add_file_path(libvlc_instance_t *vlc, libvlc_media_list_t *ml, const char * file_path)
{
    libvlc_media_t *md = libvlc_media_new_location (vlc, file_path);
    libvlc_media_list_add_media (ml, md);
    libvlc_media_release (md);
    return md;
}