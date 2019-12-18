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
struct TYPE_2__ {int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_read; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  identifier; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ stream_extractor_t ;
typedef  int /*<<< orphan*/  private_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommonClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CommonOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  Seek ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ archive_seek_subentry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ExtractorOpen( vlc_object_t* p_obj )
{
    stream_extractor_t* p_extractor = (void*)p_obj;
    private_sys_t* p_sys = CommonOpen( p_obj, p_extractor->source );

    if( p_sys == NULL )
        return VLC_EGENERIC;

    if( archive_seek_subentry( p_sys, p_extractor->identifier ) )
    {
        CommonClose( p_sys );
        return VLC_EGENERIC;
    }

    p_extractor->p_sys = p_sys;
    p_extractor->pf_read = Read;
    p_extractor->pf_control = Control;
    p_extractor->pf_seek = Seek;

    return VLC_SUCCESS;
}