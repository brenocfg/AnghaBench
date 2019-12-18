#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_service; } ;
typedef  TYPE_1__ vdr_info_t ;
typedef  int uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_2__ demux_t ;

/* Variables and functions */
 int DetectPacketSize (TYPE_2__*,unsigned int*,scalar_t__) ; 
 int GetWBE (int const*) ; 
 scalar_t__ TOPFIELD_HEADER_SIZE ; 
 scalar_t__ TS_PACKET_SIZE_MAX ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int const*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,...) ; 
 scalar_t__ vlc_stream_Peek (int /*<<< orphan*/ ,int const**,scalar_t__) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static int DetectPVRHeadersAndHeaderSize( demux_t *p_demux, unsigned *pi_header_size, vdr_info_t *p_vdr )
{
    const uint8_t *p_peek;
    *pi_header_size = 0;
    int i_packet_size = -1;

    if( vlc_stream_Peek( p_demux->s,
                     &p_peek, TS_PACKET_SIZE_MAX ) < TS_PACKET_SIZE_MAX )
        return -1;

    if( memcmp( p_peek, "TFrc", 4 ) == 0 && p_peek[6] == 0 &&
        vlc_stream_Peek( p_demux->s, &p_peek, TOPFIELD_HEADER_SIZE + TS_PACKET_SIZE_MAX )
            == TOPFIELD_HEADER_SIZE + TS_PACKET_SIZE_MAX )
    {
        const int i_service = GetWBE(&p_peek[18]);
        i_packet_size = DetectPacketSize( p_demux, pi_header_size, TOPFIELD_HEADER_SIZE );
        if( i_packet_size != -1 )
        {
            msg_Dbg( p_demux, "this is a topfield file" );
#if 0
            /* I used the TF5000PVR 2004 Firmware .doc header documentation,
             * /doc/Structure%20of%20Recorded%20File%20in%20TF5000PVR%20(Feb%2021%202004).doc on streams.vo
             * but after the filename the offsets seem to be incorrect.  - DJ */
            int i_duration, i_name;
            char *psz_name = xmalloc(25);
            char *psz_event_name;
            char *psz_event_text = xmalloc(130);
            char *psz_ext_text = xmalloc(1025);

            // 2 bytes version Uimsbf (4,5)
            // 2 bytes reserved (6,7)
            // 2 bytes duration in minutes Uimsbf (8,9(
            i_duration = (int) (p_peek[8] << 8) | p_peek[9];
            msg_Dbg( p_demux, "Topfield recording length: +/- %d minutes", i_duration);
            // 2 bytes service number in channel list (10, 11)
            // 2 bytes service type Bslbf 0=TV 1=Radio Bslb (12, 13)
            // 4 bytes of reserved + tuner info (14,15,16,17)
            // 2 bytes of Service ID  Bslbf (18,19)
            // 2 bytes of PMT PID  Uimsbf (20,21)
            // 2 bytes of PCR PID  Uimsbf (22,23)
            // 2 bytes of Video PID  Uimsbf (24,25)
            // 2 bytes of Audio PID  Uimsbf (26,27)
            // 24 bytes filename Bslbf
            memcpy( psz_name, &p_peek[28], 24 );
            psz_name[24] = '\0';
            msg_Dbg( p_demux, "recordingname=%s", psz_name );
            // 1 byte of sat index Uimsbf  (52)
            // 3 bytes (1 bit of polarity Bslbf +23 bits reserved)
            // 4 bytes of freq. Uimsbf (56,57,58,59)
            // 2 bytes of symbol rate Uimsbf (60,61)
            // 2 bytes of TS stream ID Uimsbf (62,63)
            // 4 bytes reserved
            // 2 bytes reserved
            // 2 bytes duration Uimsbf (70,71)
            //i_duration = (int) (p_peek[70] << 8) | p_peek[71];
            //msg_Dbg( p_demux, "Topfield 2nd duration field: +/- %d minutes", i_duration);
            // 4 bytes EventID Uimsbf (72-75)
            // 8 bytes of Start and End time info (76-83)
            // 1 byte reserved (84)
            // 1 byte event name length Uimsbf (89)
            i_name = (int)(p_peek[89]&~0x81);
            msg_Dbg( p_demux, "event name length = %d", i_name);
            psz_event_name = xmalloc( i_name+1 );
            // 1 byte parental rating (90)
            // 129 bytes of event text
            memcpy( psz_event_name, &p_peek[91], i_name );
            psz_event_name[i_name] = '\0';
            memcpy( psz_event_text, &p_peek[91+i_name], 129-i_name );
            psz_event_text[129-i_name] = '\0';
            msg_Dbg( p_demux, "event name=%s", psz_event_name );
            msg_Dbg( p_demux, "event text=%s", psz_event_text );
            // 12 bytes reserved (220)
            // 6 bytes reserved
            // 2 bytes Event Text Length Uimsbf
            // 4 bytes EventID Uimsbf
            // FIXME We just have 613 bytes. not enough for this entire text
            // 1024 bytes Extended Event Text Bslbf
            memcpy( psz_ext_text, p_peek+372, 1024 );
            psz_ext_text[1024] = '\0';
            msg_Dbg( p_demux, "extended event text=%s", psz_ext_text );
            // 52 bytes reserved Bslbf
#endif
            p_vdr->i_service = i_service;

            return i_packet_size;
            //return TS_PACKET_SIZE_188;
        }
    }

    return DetectPacketSize( p_demux, pi_header_size, 0 );
}