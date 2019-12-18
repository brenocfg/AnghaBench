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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_5__ {struct TYPE_5__* p_first; struct TYPE_5__* p_last; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BoxOffsetUp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_ReadBoxContainerChildren (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int MP4_ReadBoxContainerRawInBox( stream_t *p_stream, MP4_Box_t *p_container,
                                         uint8_t *p_buffer, uint64_t i_size, uint64_t i_offset )
{
    if(!p_container)
        return 0;
    stream_t *p_substream = vlc_stream_MemoryNew( p_stream, p_buffer, i_size,
                                                  true );
    if( !p_substream )
        return 0;
    MP4_Box_t *p_last = p_container->p_last;
    MP4_ReadBoxContainerChildren( p_substream, p_container, NULL );
    vlc_stream_Delete( p_substream );
    /* do pos fixup */
    if( p_container )
    {
        MP4_Box_t *p_box = p_last ? p_last : p_container->p_first;
        MP4_BoxOffsetUp(p_box, i_offset);
    }

    return 1;
}