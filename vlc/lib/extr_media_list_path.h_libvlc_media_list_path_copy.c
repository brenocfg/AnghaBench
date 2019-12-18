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
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;

/* Variables and functions */
 int libvlc_media_list_path_depth (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

__attribute__((used)) static inline libvlc_media_list_path_t libvlc_media_list_path_copy( const libvlc_media_list_path_t path )
{
    libvlc_media_list_path_t ret;
    int depth = libvlc_media_list_path_depth( path );
    ret = xmalloc( sizeof(int)*(depth+1) );
    memcpy( ret, path, sizeof(int)*(depth+1) );
    return ret;
}