#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ stream_directory_t ;
typedef  int /*<<< orphan*/  private_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CommonOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int DirectoryOpen( vlc_object_t* p_obj )
{
    stream_directory_t* p_directory = (void*)p_obj;
    private_sys_t* p_sys = CommonOpen( p_obj, p_directory->source );

    if( p_sys == NULL )
        return VLC_EGENERIC;

    p_directory->p_sys = p_sys;
    p_directory->pf_readdir = ReadDir;

    return VLC_SUCCESS;
}