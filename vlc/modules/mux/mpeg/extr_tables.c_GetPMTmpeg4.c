#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int uint8_t ;
struct TYPE_14__ {TYPE_3__* fmt; TYPE_2__* ts; TYPE_1__* pes; } ;
typedef  TYPE_4__ pes_mapped_stream_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_t ;
struct TYPE_15__ {int i_data; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_5__ bits_buffer_t ;
struct TYPE_13__ {scalar_t__ i_codec; scalar_t__ i_extra; scalar_t__ p_extra; } ;
struct TYPE_12__ {int i_stream_type; } ;
struct TYPE_11__ {int i_stream_id; int i_es_id; } ;

/* Variables and functions */
 int GetDescriptorLength24b (int) ; 
 int /*<<< orphan*/  Mpeg4SUBTDecoderSpecific_55 (TYPE_5__*) ; 
 scalar_t__ VLC_CODEC_SUBT ; 
 int /*<<< orphan*/  bits_align (TYPE_5__*) ; 
 int /*<<< orphan*/  bits_initwrite (TYPE_5__*,int,int*) ; 
 int /*<<< orphan*/  bits_write (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  dvbpsi_pmt_descriptor_add (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void GetPMTmpeg4( vlc_object_t *p_object, dvbpsi_pmt_t *p_dvbpmt,
                         unsigned i_mapped_streams, const pes_mapped_stream_t *p_mapped_streams )
{
    uint8_t iod[4096];
    bits_buffer_t bits, bits_fix_IOD;

    /* Make valgrind happy : it works at byte level not bit one so
     * bit_write confuse it (but DON'T CHANGE the way that bit_write is
     * working (needed when fixing some bits) */
    memset( iod, 0, 4096 );

    bits_initwrite( &bits, 4096, iod );
    /* IOD_label_scope */
    bits_write( &bits, 8,   0x11 );
    /* IOD_label */
    bits_write( &bits, 8,   0x01 );
    /* InitialObjectDescriptor */
    bits_align( &bits );
    bits_write( &bits, 8,   0x02 );     /* tag */
    bits_fix_IOD = bits;    /* save states to fix length later */
    bits_write( &bits, 24,
        GetDescriptorLength24b( 0 ) );  /* variable length (fixed later) */
    bits_write( &bits, 10,  0x01 );     /* ObjectDescriptorID */
    bits_write( &bits, 1,   0x00 );     /* URL Flag */
    bits_write( &bits, 1,   0x00 );     /* includeInlineProfileLevelFlag */
    bits_write( &bits, 4,   0x0f );     /* reserved */
    bits_write( &bits, 8,   0xff );     /* ODProfile (no ODcapability ) */
    bits_write( &bits, 8,   0xff );     /* sceneProfile */
    bits_write( &bits, 8,   0xfe );     /* audioProfile (unspecified) */
    bits_write( &bits, 8,   0xfe );     /* visualProfile( // ) */
    bits_write( &bits, 8,   0xff );     /* graphicProfile (no ) */
    for (unsigned i = 0; i < i_mapped_streams; i++ )
    {
        const pes_mapped_stream_t *p_stream = &p_mapped_streams[i];

        if( p_stream->pes->i_stream_id != 0xfa && p_stream->pes->i_stream_id != 0xfb &&
            p_stream->pes->i_stream_id != 0xfe )
            continue;

        bits_buffer_t bits_fix_ESDescr, bits_fix_Decoder;
        /* ES descriptor */
        bits_align( &bits );
        bits_write( &bits, 8,   0x03 );     /* ES_DescrTag */
        bits_fix_ESDescr = bits;
        bits_write( &bits, 24,
                    GetDescriptorLength24b( 0 ) ); /* variable size */
        bits_write( &bits, 16,  p_stream->pes->i_es_id );
        bits_write( &bits, 1,   0x00 );     /* streamDependency */
        bits_write( &bits, 1,   0x00 );     /* URL Flag */
        bits_write( &bits, 1,   0x00 );     /* OCRStreamFlag */
        bits_write( &bits, 5,   0x1f );     /* streamPriority */

        /* DecoderConfigDesciptor */
        bits_align( &bits );
        bits_write( &bits, 8,   0x04 ); /* DecoderConfigDescrTag */
        bits_fix_Decoder = bits;
        bits_write( &bits, 24,  GetDescriptorLength24b( 0 ) );
        if( p_stream->ts->i_stream_type == 0x10 )
        {
            bits_write( &bits, 8, 0x20 );   /* Visual 14496-2 */
            bits_write( &bits, 6, 0x04 );   /* VisualStream */
        }
        else if( p_stream->ts->i_stream_type == 0x1b )
        {
            bits_write( &bits, 8, 0x21 );   /* Visual 14496-2 */
            bits_write( &bits, 6, 0x04 );   /* VisualStream */
        }
        else if( p_stream->ts->i_stream_type == 0x11 ||
                 p_stream->ts->i_stream_type == 0x0f )
        {
            bits_write( &bits, 8, 0x40 );   /* Audio 14496-3 */
            bits_write( &bits, 6, 0x05 );   /* AudioStream */
        }
        else if( p_stream->ts->i_stream_type == 0x12 &&
                 p_stream->fmt->i_codec == VLC_CODEC_SUBT )
        {
            bits_write( &bits, 8, 0x0B );   /* Text Stream */
            bits_write( &bits, 6, 0x04 );   /* VisualStream */
        }
        else
        {
            bits_write( &bits, 8, 0x00 );
            bits_write( &bits, 6, 0x00 );

            msg_Err( p_object, "Unsupported stream_type => broken IOD" );
        }
        bits_write( &bits, 1,   0x00 );         /* UpStream */
        bits_write( &bits, 1,   0x01 );         /* reserved */
        bits_write( &bits, 24,  1024 * 1024 );  /* bufferSizeDB */
        bits_write( &bits, 32,  0x7fffffff );   /* maxBitrate */
        bits_write( &bits, 32,  0 );            /* avgBitrate */

        /* DecoderSpecificInfo */
        if( p_stream->fmt->i_codec == VLC_CODEC_SUBT )
        {
            bits_align( &bits );
            bits_write( &bits, 8,   0x05 ); /* tag */
            bits_write( &bits, 24,  55 );
            /* Create decoder specific info for subt */
            Mpeg4SUBTDecoderSpecific_55( &bits );
        }
        else if( p_stream->fmt->i_extra > 0 )
        {
            /* DecoderSpecificInfo */
            bits_align( &bits );
            bits_write( &bits, 8,   0x05 ); /* tag */
            bits_write( &bits, 24, GetDescriptorLength24b(
                        p_stream->fmt->i_extra ) );
            for (int j = 0; j < p_stream->fmt->i_extra; j++ )
            {
                bits_write( &bits, 8,
                    ((uint8_t*)p_stream->fmt->p_extra)[j] );
            }
        }

        /* fix Decoder length */
        bits_write( &bits_fix_Decoder, 24,
                    GetDescriptorLength24b( bits.i_data -
                    bits_fix_Decoder.i_data - 3 ) );

        /* SLConfigDescriptor : predefined (0x01) */
        bits_align( &bits );
        bits_write( &bits, 8,   0x06 ); /* tag */
        bits_write( &bits, 24,  GetDescriptorLength24b( 8 ) );
        bits_write( &bits, 8,   0x01 );/* predefined */
        bits_write( &bits, 1,   0 );   /* durationFlag */
        bits_write( &bits, 32,  0 );   /* OCRResolution */
        bits_write( &bits, 8,   0 );   /* OCRLength */
        bits_write( &bits, 8,   0 );   /* InstantBitrateLength */
        bits_align( &bits );

        /* fix ESDescr length */
        bits_write( &bits_fix_ESDescr, 24,
                    GetDescriptorLength24b( bits.i_data -
                    bits_fix_ESDescr.i_data - 3 ) );
    }
    bits_align( &bits );
    /* fix IOD length */
    bits_write( &bits_fix_IOD, 24,
                GetDescriptorLength24b(bits.i_data - bits_fix_IOD.i_data - 3 ));

    dvbpsi_pmt_descriptor_add(&p_dvbpmt[0], 0x1d, bits.i_data, bits.p_data);
}