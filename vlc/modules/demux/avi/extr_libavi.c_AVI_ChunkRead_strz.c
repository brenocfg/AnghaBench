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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  avi_chunk_t ;
struct TYPE_3__ {scalar_t__ i_chunk_fourcc; int i_chunk_size; scalar_t__* p_str; scalar_t__* p_type; } ;
typedef  TYPE_1__ avi_chunk_STRING_t ;
struct TYPE_4__ {scalar_t__ i_fourcc; int /*<<< orphan*/  psz_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_READCHUNK_ENTER ; 
 int /*<<< orphan*/  AVI_READCHUNK_EXIT (int /*<<< orphan*/ ) ; 
 TYPE_2__* AVI_strz_type ; 
 int /*<<< orphan*/  VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  p_read ; 
 scalar_t__* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AVI_ChunkRead_strz( stream_t *s, avi_chunk_t *p_chk )
{
    int i_index;
    avi_chunk_STRING_t *p_strz = (avi_chunk_STRING_t*)p_chk;
    AVI_READCHUNK_ENTER;

    for( i_index = 0;; i_index++)
    {
        if( !AVI_strz_type[i_index].i_fourcc ||
            AVI_strz_type[i_index].i_fourcc == p_strz->i_chunk_fourcc )
        {
            break;
        }
    }
    p_strz->p_type = strdup( AVI_strz_type[i_index].psz_type );
    p_strz->p_str = malloc( p_strz->i_chunk_size + 1 );
    if( !p_strz->p_type || !p_strz->p_str )
    {
        free( p_strz->p_type );
        free( p_strz->p_str );
        AVI_READCHUNK_EXIT( VLC_EGENERIC );
    }
    memcpy( p_strz->p_str, p_read, p_strz->i_chunk_size );
    p_strz->p_str[p_strz->i_chunk_size] = 0;

#ifdef AVI_DEBUG
    msg_Dbg( (vlc_object_t*)s, "%4.4s: %s : %s",
             (char*)&p_strz->i_chunk_fourcc, p_strz->p_type, p_strz->p_str);
#endif
    AVI_READCHUNK_EXIT( VLC_SUCCESS );
}