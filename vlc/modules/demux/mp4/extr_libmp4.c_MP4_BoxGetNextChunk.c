#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {int i_shortsize; struct TYPE_6__* p_next; scalar_t__ i_size; struct TYPE_6__* p_first; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  const ATOM_moof ; 
 int /*<<< orphan*/  const ATOM_moov ; 
 int /*<<< orphan*/  ATOM_root ; 
 int /*<<< orphan*/  MP4_BoxFree (TYPE_1__*) ; 
 TYPE_1__* MP4_BoxNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_ReadBoxContainerChildren (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

MP4_Box_t *MP4_BoxGetNextChunk( stream_t *s )
{
    /* p_chunk is a virtual root container for the moof and mdat boxes */
    MP4_Box_t *p_fakeroot;
    MP4_Box_t *p_tmp_box;

    p_fakeroot = MP4_BoxNew( ATOM_root );
    if( unlikely( p_fakeroot == NULL ) )
        return NULL;
    p_fakeroot->i_shortsize = 1;

    const uint32_t stoplist[] = { ATOM_moov, ATOM_moof, 0 };
    MP4_ReadBoxContainerChildren( s, p_fakeroot, stoplist );

    p_tmp_box = p_fakeroot->p_first;
    if( p_tmp_box == NULL )
    {
        MP4_BoxFree( p_fakeroot );
        return NULL;
    }
    else while( p_tmp_box )
    {
        p_fakeroot->i_size += p_tmp_box->i_size;
        p_tmp_box = p_tmp_box->p_next;
    }

    return p_fakeroot;
}