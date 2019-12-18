#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_output; } ;
typedef  TYPE_1__ video_splitter_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ video_splitter_NewPicture (TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int Filter( video_splitter_t *p_splitter,
                   picture_t *pp_dst[], picture_t *p_src )
{
    if( video_splitter_NewPicture( p_splitter, pp_dst ) )
    {
        picture_Release( p_src );
        return VLC_EGENERIC;
    }

    for( int i = 0; i < p_splitter->i_output; i++ )
        picture_Copy( pp_dst[i], p_src );

    picture_Release( p_src );
    return VLC_SUCCESS;
}