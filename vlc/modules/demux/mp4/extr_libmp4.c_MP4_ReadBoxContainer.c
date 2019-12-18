#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_5__ {size_t i_size; scalar_t__ i_pos; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 int MP4_ReadBoxContainerChildren (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MP4_Seek (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mp4_box_headersize (TYPE_1__*) ; 

__attribute__((used)) static int MP4_ReadBoxContainer( stream_t *p_stream, MP4_Box_t *p_container )
{
    if( p_container->i_size &&
        ( p_container->i_size <= (size_t)mp4_box_headersize(p_container ) + 8 ) )
    {
        /* container is empty, 8 stand for the first header in this box */
        return 1;
    }

    /* enter box */
    if ( MP4_Seek( p_stream, p_container->i_pos +
                      mp4_box_headersize( p_container ) ) )
        return 0;
    return MP4_ReadBoxContainerChildren( p_stream, p_container, NULL );
}