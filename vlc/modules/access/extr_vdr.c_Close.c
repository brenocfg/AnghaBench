#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_4__ {int fd; int /*<<< orphan*/  p_marks; int /*<<< orphan*/  offsets; scalar_t__ p_meta; int /*<<< orphan*/  file_sizes; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Delete (scalar_t__) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    stream_t *p_access = (stream_t*)p_this;
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->fd != -1 )
        vlc_close( p_sys->fd );
    ARRAY_RESET( p_sys->file_sizes );

    if( p_sys->p_meta )
        vlc_meta_Delete( p_sys->p_meta );

    free( p_sys->offsets );
    vlc_input_title_Delete( p_sys->p_marks );
}