#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_9__ {scalar_t__ i_size; scalar_t__ i_pos; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BoxFree (TYPE_1__*) ; 
 scalar_t__ MP4_Box_Read_Specific (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* MP4_ReadBoxAllocateCheck (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  MP4_Seek (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ VLC_SUCCESS ; 

__attribute__((used)) static MP4_Box_t *MP4_ReadBox( stream_t *p_stream, MP4_Box_t *p_father )
{
    MP4_Box_t *p_box = MP4_ReadBoxAllocateCheck( p_stream, p_father );
    if( !p_box )
        return NULL;

    if( MP4_Box_Read_Specific( p_stream, p_box, p_father ) != VLC_SUCCESS )
    {
        uint64_t i_end = p_box->i_pos + p_box->i_size;
        MP4_BoxFree( p_box );
        MP4_Seek( p_stream, i_end ); /* Skip the failed box */
        return NULL;
    }
    return p_box;
}