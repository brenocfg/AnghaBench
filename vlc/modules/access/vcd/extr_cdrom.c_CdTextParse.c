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
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  pppsz_info ;
typedef  enum cdtext_charset_e { ____Placeholder_cdtext_charset_e } cdtext_charset_e ;

/* Variables and functions */
 int CDTEXT_CHARSET_ASCII7BIT ; 
 int CDTEXT_CHARSET_ISO88591 ; 
 int CDTEXT_MAX_TRACKS ; 
 size_t CDTEXT_PACK_HEADER ; 
 int CDTEXT_PACK_SIZE ; 
 int CDTEXT_TEXT_BUFFER ; 
 int /*<<< orphan*/  CdTextParsePackText (int const*,int,size_t*,size_t*,char*,int*,char***) ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (char***,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 
 int /*<<< orphan*/  vlc_meta_SetAlbum (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_SetArtist (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_SetDescription (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_SetGenre (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_SetTitle (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int CdTextParse( vlc_meta_t ***ppp_tracks, int *pi_tracks,
                        const uint8_t *p_buffer, int i_buffer )
{
    char *pppsz_info[CDTEXT_MAX_TRACKS + 1][0x10];
    int i_track_last = -1;
    if( i_buffer < 4 )
        return -1;

    p_buffer += 4;
    i_buffer -= 4;

    /* block size information is split in a sequence of 3 */
    const uint8_t *bsznfopayl[3] = { NULL, NULL, NULL };
    for( int i = 0; i < i_buffer/CDTEXT_PACK_SIZE; i++ )
    {
        const uint8_t *p_pack = &p_buffer[CDTEXT_PACK_SIZE*i];
        const uint8_t i_block_number = (p_pack[3] >> 4) & 0x07;
        if( i_block_number > 0 )
            continue;
        if( p_pack[0] == 0x8f )
        {
            const int i_track = p_pack[1] & 0x7f;
            /* can't be higher than 3 blocks */
            if( i_track > 2 )
                return -1;
            /* duplicate should not happen */
            if( bsznfopayl[i_track] != NULL )
                return -1;
            /* point to payload (12) */
            bsznfopayl[i_track] = &p_pack[CDTEXT_PACK_HEADER];
        }
    }
    /* incomplete ? */
    if( (!bsznfopayl[0] ^ !bsznfopayl[1]) ||
        (!bsznfopayl[1] ^ !bsznfopayl[2]) )
        return -1;

    memset( pppsz_info, 0, sizeof(pppsz_info) );

    enum cdtext_charset_e e_textpackcharset;
    if( bsznfopayl[0] )
    {
        e_textpackcharset = bsznfopayl[0][0];
        /* use superset to fix broken decl */
        if( e_textpackcharset == CDTEXT_CHARSET_ASCII7BIT )
            e_textpackcharset = CDTEXT_CHARSET_ISO88591;
    }
    else e_textpackcharset = CDTEXT_CHARSET_ASCII7BIT;

    /* capture buffer */
    char textbuffer[CDTEXT_TEXT_BUFFER];
    size_t i_textbuffer = 0;
    size_t i_repeatbuffer = 0;
    uint8_t i_prev_pack_type = 0x00;

    for( int i = 0; i < i_buffer/CDTEXT_PACK_SIZE; i++ )
    {
        const uint8_t *p_pack = &p_buffer[CDTEXT_PACK_SIZE*i];
        const uint8_t i_pack_type = p_pack[0];
        //const int i_sequence_number = p_block[2];
        const uint8_t i_block_number = (p_pack[3] >> 4) & 0x07;
        //const int i_crc = (p_block[4+12] << 8) | (p_block[4+13] << 0);

        /* non flushed text buffer */
        if(i_textbuffer && i_pack_type != i_prev_pack_type)
        {
            i_textbuffer = 0;
            i_repeatbuffer = 0;
        }
        i_prev_pack_type = i_pack_type;

        uint8_t i_track = p_pack[1] & 0x7f;
        if( i_track > CDTEXT_MAX_TRACKS ||
            (p_pack[1] & 0x80) /* extension flag */ ||
            i_block_number > 0 /* support only first language */
           )
        {
            i_prev_pack_type = 0x00;
            continue;
        }

        /* */
        switch( i_pack_type )
        {
            case 0x80:
            case 0x81:
            case 0x85:
            case 0x87:
            {
                CdTextParsePackText( p_pack, e_textpackcharset,
                                     &i_textbuffer, &i_repeatbuffer, textbuffer,
                                     &i_track_last, pppsz_info );
                break;
            }
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x86:
            case 0x8d:
            case 0x8e:
            default:
                continue;
        }
    }

    if( i_track_last < 0 )
        return -1;

    vlc_meta_t **pp_tracks = calloc( i_track_last+1, sizeof(*pp_tracks) );
    if( !pp_tracks )
        goto exit;

    for( int j = 0; j < 0x10; j++ )
    {
        for( int i = 0; i <= i_track_last; i++ )
        {
            /* */
            const char *psz_default = pppsz_info[0][j];
            const char *psz_value = pppsz_info[i][j];

            if( !psz_value && !psz_default )
                continue;
            vlc_meta_t *p_track = pp_tracks[i];
            if( !p_track )
            {
                p_track = pp_tracks[i] = vlc_meta_New();
                if( !p_track )
                    continue;
            }
            switch( 0x80 + j )
            {
            case 0x80: /* Album/Title */
                if( i == 0 )
                {
                    vlc_meta_SetAlbum( p_track, psz_value );
                }
                else
                {
                    if( psz_value )
                        vlc_meta_SetTitle( p_track, psz_value );
                    if( psz_default )
                        vlc_meta_SetAlbum( p_track, psz_default );
                }
                break;
            case 0x81: /* Performer */
                vlc_meta_SetArtist( p_track,
                                    psz_value ? psz_value : psz_default );
                break;
            case 0x85: /* Messages */
                vlc_meta_SetDescription( p_track,
                                         psz_value ? psz_value : psz_default );
                break;
            case 0x87: /* Genre */
                vlc_meta_SetGenre( p_track,
                                   psz_value ? psz_value : psz_default );
                break;
            /* FIXME unsupported:
             * 0x82: songwriter
             * 0x83: composer
             * 0x84: arrenger
             * 0x86: disc id */
            }
        }
    }
    /* */
exit:
    for( int j = 0; j < 0x10; j++ )
        for( int i = 0; i <= i_track_last; i++ )
            free( pppsz_info[i][j] );

    *ppp_tracks = pp_tracks;
    *pi_tracks = i_track_last+1;
    return pp_tracks ? 0 : -1;
}