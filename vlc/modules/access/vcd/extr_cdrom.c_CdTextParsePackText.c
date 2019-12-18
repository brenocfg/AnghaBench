#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  enum cdtext_charset_e { ____Placeholder_cdtext_charset_e } cdtext_charset_e ;

/* Variables and functions */
 int CDTEXT_MAX_TRACKS ; 
 size_t CDTEXT_PACK_HEADER ; 
 int CDTEXT_PACK_PAYLOAD ; 
 size_t CDTEXT_TEXT_BUFFER ; 
 int /*<<< orphan*/  CdTextAppendPayload (char*,size_t,int,char**) ; 
 size_t CdTextPayloadLength (char*,int,int const) ; 
 int __MAX (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,int const*,size_t) ; 

__attribute__((used)) static void CdTextParsePackText( const uint8_t *p_pack,
                                 enum cdtext_charset_e e_charset,
                                 size_t *pi_textbuffer,
                                 size_t *pi_repeatbuffer,
                                 char *textbuffer,
                                 int *pi_last_track,
                                 char *pppsz_info[CDTEXT_MAX_TRACKS + 1][0x10] )
{
    const uint8_t i_pack_type = p_pack[0];
    uint8_t i_track = p_pack[1] & 0x7f;
    const bool b_double_byte = p_pack[3] & 0x80;
    const uint8_t i_char_position = p_pack[3] & 0x0f;

    if( i_char_position == 0 )
        *pi_textbuffer = 0; /* not using remains */

    const uint8_t *p_start = &p_pack[CDTEXT_PACK_HEADER];
    const uint8_t *p_end = p_start + CDTEXT_PACK_PAYLOAD;

    for( const uint8_t *p_readpos = p_start; p_readpos < p_end ; )
    {
        size_t i_payload = CdTextPayloadLength( (char *)p_readpos,
                                                p_end - p_readpos,
                                                b_double_byte );

        /* update max used track # */
        if( i_payload > 0 )
            *pi_last_track = __MAX( *pi_last_track, i_track );

        /* check for repeats */
        if( i_payload == 1 && p_readpos[0] == '\t' &&
            *pi_repeatbuffer && !*pi_textbuffer )
        {
            *pi_textbuffer = *pi_repeatbuffer;
            textbuffer[*pi_textbuffer] = 0;
        }
        else
        {
            /* copy out segment to buffer */
            size_t i_append = i_payload;
            if( *pi_textbuffer + i_payload >= CDTEXT_TEXT_BUFFER )
                i_append = CDTEXT_TEXT_BUFFER - *pi_textbuffer;
            memcpy( &textbuffer[*pi_textbuffer], p_readpos, i_append );
            *pi_textbuffer += i_append;
            *pi_repeatbuffer = 0;
        }

        /* end of pack or just first split ? */
        if( &p_readpos[i_payload] < p_end ) /* not continuing */
        {
            /* commit */
            if(*pi_textbuffer > 0)
            {
                CdTextAppendPayload( textbuffer, *pi_textbuffer, e_charset,
                                     &pppsz_info[i_track][i_pack_type-0x80] );
                *pi_repeatbuffer = *pi_textbuffer;
                *pi_textbuffer = 0;

                if(++i_track > CDTEXT_MAX_TRACKS) /* increment for next part of the split */
                    break;
            }
            /* set read pointer for next track in same pack */
            p_readpos = p_readpos + i_payload + (b_double_byte ? 2 : 1);
        }
        else
        {
            p_readpos = p_end;
        }
    }
}