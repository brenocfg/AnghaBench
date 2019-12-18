#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int const) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,char const**,int) ; 

__attribute__((used)) static int Validate( demux_t *p_demux, const char *psz_ext )
{
    static const struct
    {
        int i_offset;
        const char *psz_marker;
    } p_marker[] = {
        {  0, "ziRCONia" },             /* MMCMP files */
        {  0, "Extended Module" },      /* XM */
        { 44, "SCRM" },                 /* S3M */
        {  0, "IMPM" },                 /* IT */
        {  0, "GF1PATCH110" },          /* PAT */
        { 20, "!SCREAM!" },             /* STM */
        { 20, "!Scream!" },             /* STM */
        { 20, "BMOD2STM" },             /* STM */
        {  0, "MMD0" },                 /* MED v0 */
        {  0, "MMD1" },                 /* MED v1 */
        {  0, "MMD2" },                 /* MED v2 */
        {  0, "MMD3" },                 /* MED v3 */
        {  0, "MTM" },                  /* MTM */
        {  0, "DMDL" },                 /* MDL */
        {  0, "DBM0" },                 /* DBM */
        {  0, "if" },                   /* 669 */
        {  0, "JN" },                   /* 669 */
        {  0, "FAR\xfe" },              /* FAR */
        {  0, "Extreme" },              /* AMS */
        {  0, "OKTASONGCMOD" },         /* OKT */
        { 44, "PTMF" },                 /* PTM */
        {  0, "MAS_UTrack_V00" },       /* Ult */
        {  0, "DDMF" },                 /* DMF */
        {  8, "DSMFSONG" },             /* DSM */
        {  0, "\xc1\x83\x2a\x9e" },     /* UMX */
        {  0, "ASYLUM Music Format V1.0" }, /* AMF Type 0 */
        {  0, "AMF" },                  /* AMF */
        {  0, "PSM\xfe" },              /* PSM */
        {  0, "PSM " },                 /* PSM */
        {  0, "MT20" },                 /* MT2 */

        { 1080, "M.K." },               /* MOD */
        { 1080, "M!K!" },
        { 1080, "M&K!" },
        { 1080, "N.T." },
        { 1080, "CD81" },
        { 1080, "OKTA" },
        { 1080, "16CN" },
        { 1080, "32CN" },
        { 1080, "FLT4" },
        { 1080, "FLT8" },
        { 1080, "6CHN" },
        { 1080, "8CHN" },
        { 1080, "FLT" },
        { 1080, "TDZ" },
        { 1081, "CHN" },
        { 1082, "CH" },

        {  -1, NULL }
    };
    static const char *ppsz_mod_ext[] =
    {
        "mod", "s3m", "xm",  "it",  "669", "amf", "ams", "dbm", "dmf", "dsm",
        "far", "mdl", "med", "mtm", "okt", "ptm", "stm", "ult", "umx", "mt2",
        "psm", "abc", NULL
    };
    bool has_valid_extension = false;
    if( psz_ext )
    {
        for( int i = 0; ppsz_mod_ext[i] != NULL; i++ )
        {
            has_valid_extension |= !strcasecmp( psz_ext, ppsz_mod_ext[i] );
            if( has_valid_extension )
                break;
        }
    }

    const uint8_t *p_peek;
    const int i_peek = vlc_stream_Peek( p_demux->s, &p_peek, 2048 );
    if( i_peek < 4 )
        return VLC_EGENERIC;

    for( int i = 0; p_marker[i].i_offset >= 0; i++ )
    {
        const char *psz_marker = p_marker[i].psz_marker;
        const int i_size = strlen( psz_marker );
        const int i_offset = p_marker[i].i_offset;

        if( i_peek < i_offset + i_size )
            continue;

        if( !memcmp( &p_peek[i_offset], psz_marker, i_size ) )
        {
            if( i_size >= 4 || has_valid_extension )
                return VLC_SUCCESS;
        }
    }

    /* The only two format left untested are ABC and MOD(old version)
     * ant they are difficult to test :( */

    /* Check for ABC
     * TODO i_peek = 2048 is too big for such files */
    if( psz_ext && !strcasecmp( psz_ext, "abc" ) )
    {
        bool b_k = false;
        bool b_tx = false;

        for( int i = 0; i < i_peek-1; i++ )
        {
            b_k |= p_peek[i+0] == 'K' && p_peek[i+1] == ':';
            b_tx |= ( p_peek[i+0] == 'X' || p_peek[i+0] == 'T') && p_peek[i+1] == ':';
        }
        if( !b_k || !b_tx )
            return VLC_EGENERIC;
        return VLC_SUCCESS;
    }

    /* Check for MOD */
    if( psz_ext && !strcasecmp( psz_ext, "mod" ) && i_peek >= 20 + 15 * 30 )
    {
        /* Check that the name is correctly null padded */
        const uint8_t *p = memchr( p_peek, '\0', 20 );
        if( p )
        {
            for( ; p < &p_peek[20]; p++ )
            {
                if( *p )
                    return VLC_EGENERIC;
            }
        }

        for( int i = 0; i < 15; i++ )
        {
            const uint8_t *p_sample = &p_peek[20 + i*30];

            /* Check correct null padding */
            p = memchr( &p_sample[0], '\0', 22 );
            if( p )
            {
                for( ; p < &p_sample[22]; p++ )
                {
                    if( *p )
                        return VLC_EGENERIC;
                }
            }

            if( p_sample[25] > 64 ) /* Volume value */
                return VLC_EGENERIC;
        }
        return VLC_SUCCESS;
    }
    return VLC_EGENERIC;
}