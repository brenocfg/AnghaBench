#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ avail_out; scalar_t__ total_out; scalar_t__ opaque; scalar_t__ zfree; scalar_t__ zalloc; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  avail_in; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_5__ z_stream ;
typedef  scalar_t__ voidpf ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ free_func ;
typedef  scalar_t__ alloc_func ;
struct TYPE_19__ {TYPE_10__* p_cmov; TYPE_3__* p_cmvd; TYPE_2__* p_dcom; } ;
struct TYPE_21__ {TYPE_4__ data; TYPE_1__* p_father; } ;
struct TYPE_18__ {scalar_t__ i_uncompressed_size; int /*<<< orphan*/ * p_data; scalar_t__ b_compressed; int /*<<< orphan*/  i_compressed_size; } ;
struct TYPE_17__ {scalar_t__ i_algorithm; } ;
struct TYPE_16__ {scalar_t__ i_type; } ;
struct TYPE_15__ {int /*<<< orphan*/  p_moov; } ;
typedef  TYPE_6__ MP4_Box_t ;
typedef  int /*<<< orphan*/  MP4_Box_data_cmov_t ;

/* Variables and functions */
 scalar_t__ ATOM_foov ; 
 scalar_t__ ATOM_moov ; 
 scalar_t__ ATOM_zlib ; 
 TYPE_6__* MP4_BoxGet (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  MP4_ReadBox (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_ReadBoxContainer (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 scalar_t__ Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 TYPE_10__* calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int inflate (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_5__*) ; 
 int inflateInit (TYPE_5__*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int MP4_ReadBox_cmov( stream_t *p_stream, MP4_Box_t *p_box )
{
    MP4_Box_t *p_dcom;
    MP4_Box_t *p_cmvd;

#ifdef HAVE_ZLIB_H
    stream_t *p_stream_memory;
    z_stream z_data;
    uint8_t *p_data;
    int i_result;
#endif

    if( !( p_box->data.p_cmov = calloc(1, sizeof( MP4_Box_data_cmov_t ) ) ) )
        return 0;

    if( !p_box->p_father ||
        ( p_box->p_father->i_type != ATOM_moov &&
          p_box->p_father->i_type != ATOM_foov ) )
    {
        msg_Warn( p_stream, "Read box: \"cmov\" box alone" );
        return 1;
    }

    if( !MP4_ReadBoxContainer( p_stream, p_box ) )
    {
        return 0;
    }

    if( ( p_dcom = MP4_BoxGet( p_box, "dcom" ) ) == NULL ||
        ( p_cmvd = MP4_BoxGet( p_box, "cmvd" ) ) == NULL ||
        p_cmvd->data.p_cmvd->p_data == NULL )
    {
        msg_Warn( p_stream, "read box: \"cmov\" incomplete" );
        return 0;
    }

    if( p_dcom->data.p_dcom->i_algorithm != ATOM_zlib )
    {
        msg_Dbg( p_stream, "read box: \"cmov\" compression algorithm : %4.4s "
                 "not supported", (char*)&p_dcom->data.p_dcom->i_algorithm );
        return 0;
    }

#ifndef HAVE_ZLIB_H
    msg_Dbg( p_stream, "read box: \"cmov\" zlib unsupported" );
    return 0;

#else
    /* decompress data */
    /* allocate a new buffer */
    if( !( p_data = malloc( p_cmvd->data.p_cmvd->i_uncompressed_size ) ) )
        return 0;
    /* init default structures */
    z_data.next_in   = p_cmvd->data.p_cmvd->p_data;
    z_data.avail_in  = p_cmvd->data.p_cmvd->i_compressed_size;
    z_data.next_out  = p_data;
    z_data.avail_out = p_cmvd->data.p_cmvd->i_uncompressed_size;
    z_data.zalloc    = (alloc_func)Z_NULL;
    z_data.zfree     = (free_func)Z_NULL;
    z_data.opaque    = (voidpf)Z_NULL;

    /* init zlib */
    if( inflateInit( &z_data ) != Z_OK )
    {
        msg_Err( p_stream, "read box: \"cmov\" error while uncompressing" );
        free( p_data );
        return 0;
    }

    /* uncompress */
    i_result = inflate( &z_data, Z_NO_FLUSH );
    if( i_result != Z_OK && i_result != Z_STREAM_END )
    {
        msg_Err( p_stream, "read box: \"cmov\" error while uncompressing" );
        free( p_data );
        return 0;
    }

    if( p_cmvd->data.p_cmvd->i_uncompressed_size != z_data.total_out )
    {
        msg_Warn( p_stream, "read box: \"cmov\" uncompressing data size "
                  "mismatch" );
    }
    p_cmvd->data.p_cmvd->i_uncompressed_size = z_data.total_out;

    /* close zlib */
    if( inflateEnd( &z_data ) != Z_OK )
    {
        msg_Warn( p_stream, "read box: \"cmov\" error while uncompressing "
                  "data (ignored)" );
    }

    free( p_cmvd->data.p_cmvd->p_data );
    p_cmvd->data.p_cmvd->p_data = p_data;
    p_cmvd->data.p_cmvd->b_compressed = 0;

    msg_Dbg( p_stream, "read box: \"cmov\" box successfully uncompressed" );

    /* now create a memory stream */
    p_stream_memory =
        vlc_stream_MemoryNew( VLC_OBJECT(p_stream),
                              p_cmvd->data.p_cmvd->p_data,
                              p_cmvd->data.p_cmvd->i_uncompressed_size, true );

    /* and read uncompressd moov */
    p_box->data.p_cmov->p_moov = MP4_ReadBox( p_stream_memory, NULL );

    vlc_stream_Delete( p_stream_memory );

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"cmov\" compressed movie header completed");
#endif

    return p_box->data.p_cmov->p_moov ? 1 : 0;
#endif /* HAVE_ZLIB_H */
}