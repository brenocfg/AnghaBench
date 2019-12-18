#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  psz_line ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_7__ {int* i_page; int i_wanted_magazine; int* b_is_subtitle; int i_wanted_page; int* b_erase; scalar_t__** ppsz_lines; int /*<<< orphan*/  b_ignore_sub_flag; int /*<<< orphan*/ * pi_active_national_set; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int FLAG_ERASE_PAGE ; 
 int FLAG_INHIBIT_DISPLAY ; 
 int FLAG_INTERRUPTED ; 
 int FLAG_MAGAZINE_SERIAL ; 
 int FLAG_NEWSFLASH ; 
 int FLAG_SUBTITLE ; 
 int FLAG_SUPPRESS_HEADER ; 
 int FLAG_UPDATE ; 
 int bytereverse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (TYPE_1__*) ; 
 int /*<<< orphan*/  decode_string (char*,int,TYPE_2__*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hamming_8_4 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * ppi_national_subsets ; 
 scalar_t__ strcmp (char*,scalar_t__*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static bool DecodePageHeaderPacket( decoder_t *p_dec, const uint8_t *packet,
                                    int magazine )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    int flag = 0;
    char psz_line[256];

    for ( int a = 0; a < 6; a++ )
    {
        flag |= (0xF & (bytereverse( hamming_8_4(packet[8 + a]) ) >> 4))
                  << (a * 4);
    }

/*         if (!p_sys->b_ignore_sub_flag && !(flag & FLAG_SUBTITLE)) */
/*           return false; */

    p_sys->i_page[magazine] = (0xF0 & bytereverse( hamming_8_4(packet[7]) )) | /* tens */
                              (0x0F & (bytereverse( hamming_8_4(packet[6]) ) >> 4) ); /* units */

    decode_string( psz_line, sizeof(psz_line), p_sys, magazine,
                   packet + 14, 40 - 14 );

    dbg((p_dec, "mag %d flags %x page %x character set %d subtitles %d %s", magazine, flag,
         p_sys->i_page[magazine],
         7 & flag>>21, !!(flag & FLAG_SUBTITLE), psz_line));

    p_sys->pi_active_national_set[magazine] =
                         ppi_national_subsets[7 & (flag >> 21)];

    int subtitlesflags = FLAG_SUBTITLE;
    if( !p_sys->b_ignore_sub_flag && p_sys->i_wanted_magazine != 0x07 )
        subtitlesflags |= FLAG_SUPPRESS_HEADER;

    p_sys->b_is_subtitle[magazine] = !((flag & subtitlesflags) != subtitlesflags);

    dbg(( p_dec, "FLAGS%s%s%s%s%s%s%s mag_ser %d",
          (flag & FLAG_ERASE_PAGE)     ? " erase" : "",
          (flag & FLAG_NEWSFLASH)      ? " news" : "",
          (flag & FLAG_SUBTITLE)       ? " subtitle" : "",
          (flag & FLAG_SUPPRESS_HEADER)? " suppressed_head" : "",
          (flag & FLAG_UPDATE)         ? " update" : "",
          (flag & FLAG_INTERRUPTED)    ? " interrupt" : "",
          (flag & FLAG_INHIBIT_DISPLAY)? " inhibit" : "",
        !!(flag & FLAG_MAGAZINE_SERIAL) ));

    if ( (p_sys->i_wanted_page != -1
           && p_sys->i_page[magazine] != p_sys->i_wanted_page)
           || !p_sys->b_is_subtitle[magazine] )
        return false;

    p_sys->b_erase[magazine] = !!(flag & FLAG_ERASE_PAGE);

    /* kludge here :
     * we ignore the erase flag if it happens less than 1.5 seconds
     * before last caption
     * TODO   make this time configurable
     * UPDATE the kludge seems to be no more necessary
     *        so it's commented out*/
    if ( /*p_block->i_pts > p_sys->prev_pts + 1500000 && */
         p_sys->b_erase[magazine] )
    {
        dbg((p_dec, "ERASE !"));

        p_sys->b_erase[magazine] = 0;
        for ( int i = 1; i < 32; i++ )
        {
            if ( !p_sys->ppsz_lines[i][0] ) continue;
            /* b_update = true; */
            p_sys->ppsz_lines[i][0] = 0;
        }
    }

    /* replace the row if it's different */
    if ( strcmp(psz_line, p_sys->ppsz_lines[0]) )
    {
        strncpy( p_sys->ppsz_lines[0], psz_line,
                 sizeof(p_sys->ppsz_lines[0]) - 1);
    }

    return true;
}