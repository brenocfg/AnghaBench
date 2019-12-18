#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {int /*<<< orphan*/ * meta; } ;
typedef  TYPE_2__ demux_sys_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  avi_chunk_list_t ;
struct TYPE_9__ {int i_flags; } ;
typedef  TYPE_3__ avi_chunk_avih_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_type; int /*<<< orphan*/  p_str; } ;
typedef  TYPE_4__ avi_chunk_STRING_t ;

/* Variables and functions */
#define  AVIFOURCC_IARL 180 
#define  AVIFOURCC_IART 179 
#define  AVIFOURCC_ICDS 178 
#define  AVIFOURCC_ICMS 177 
#define  AVIFOURCC_ICMT 176 
#define  AVIFOURCC_ICNM 175 
#define  AVIFOURCC_ICNT 174 
#define  AVIFOURCC_ICOP 173 
#define  AVIFOURCC_ICRD 172 
#define  AVIFOURCC_ICRP 171 
#define  AVIFOURCC_IDIM 170 
#define  AVIFOURCC_IDIT 169 
#define  AVIFOURCC_IDPI 168 
#define  AVIFOURCC_IDST 167 
#define  AVIFOURCC_IEDT 166 
#define  AVIFOURCC_IENG 165 
#define  AVIFOURCC_IFRM 164 
#define  AVIFOURCC_IGNR 163 
#define  AVIFOURCC_IKEY 162 
#define  AVIFOURCC_ILGT 161 
#define  AVIFOURCC_ILNG 160 
#define  AVIFOURCC_IMED 159 
#define  AVIFOURCC_IMUS 158 
#define  AVIFOURCC_INAM 157 
 scalar_t__ const AVIFOURCC_INFO ; 
#define  AVIFOURCC_IPDS 156 
#define  AVIFOURCC_IPLT 155 
#define  AVIFOURCC_IPRD 154 
#define  AVIFOURCC_IPRO 153 
#define  AVIFOURCC_IPRT 152 
#define  AVIFOURCC_IRTD 151 
#define  AVIFOURCC_ISBJ 150 
#define  AVIFOURCC_ISFT 149 
#define  AVIFOURCC_ISGN 148 
#define  AVIFOURCC_ISHP 147 
#define  AVIFOURCC_ISMP 146 
#define  AVIFOURCC_ISRC 145 
#define  AVIFOURCC_ISRF 144 
#define  AVIFOURCC_ISTD 143 
#define  AVIFOURCC_ISTR 142 
#define  AVIFOURCC_ITCH 141 
#define  AVIFOURCC_IWEB 140 
#define  AVIFOURCC_IWRI 139 
 int AVIF_HASINDEX ; 
 int AVIF_ISINTERLEAVED ; 
 int AVIF_MUSTUSEINDEX ; 
 int AVIF_TRUSTCKTYPE ; 
 void* AVI_ChunkFind (int /*<<< orphan*/ *,scalar_t__ const,int /*<<< orphan*/ ,int) ; 
 char* FromACP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  vlc_meta_AddExtra (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
#define  vlc_meta_Artist 138 
#define  vlc_meta_Copyright 137 
#define  vlc_meta_Date 136 
#define  vlc_meta_Description 135 
#define  vlc_meta_Genre 134 
#define  vlc_meta_Language 133 
 int /*<<< orphan*/ * vlc_meta_New () ; 
#define  vlc_meta_Rating 132 
 int /*<<< orphan*/  vlc_meta_Set (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_meta_SetSetting (int /*<<< orphan*/ *,char*) ; 
#define  vlc_meta_Title 131 
#define  vlc_meta_TrackNumber 130 
#define  vlc_meta_TrackTotal 129 
#define  vlc_meta_URL 128 

__attribute__((used)) static void AVI_MetaLoad( demux_t *p_demux,
                          avi_chunk_list_t *p_riff, avi_chunk_avih_t *p_avih )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    vlc_meta_t *p_meta = p_sys->meta = vlc_meta_New();
    if( !p_meta )
        return;

    char buffer[200];
    snprintf( buffer, sizeof(buffer), "%s%s%s%s",
              p_avih->i_flags&AVIF_HASINDEX      ? " HAS_INDEX"      : "",
              p_avih->i_flags&AVIF_MUSTUSEINDEX  ? " MUST_USE_INDEX" : "",
              p_avih->i_flags&AVIF_ISINTERLEAVED ? " IS_INTERLEAVED" : "",
              p_avih->i_flags&AVIF_TRUSTCKTYPE   ? " TRUST_CKTYPE"   : "" );
    vlc_meta_SetSetting( p_meta, buffer );

    avi_chunk_list_t *p_info = AVI_ChunkFind( p_riff, AVIFOURCC_INFO, 0, true );
    if( !p_info )
        return;

    static const struct {
        vlc_fourcc_t i_id;
        int          i_type;
    } p_dsc[] = {
        { AVIFOURCC_IART, vlc_meta_Artist },
        { AVIFOURCC_ICMT, vlc_meta_Description },
        { AVIFOURCC_ICOP, vlc_meta_Copyright },
        { AVIFOURCC_IGNR, vlc_meta_Genre },
        { AVIFOURCC_INAM, vlc_meta_Title },
        { AVIFOURCC_ICRD, vlc_meta_Date },
        { AVIFOURCC_ILNG, vlc_meta_Language },
        { AVIFOURCC_IRTD, vlc_meta_Rating },
        { AVIFOURCC_IWEB, vlc_meta_URL },
        { AVIFOURCC_IPRT, vlc_meta_TrackNumber },
        { AVIFOURCC_IFRM, vlc_meta_TrackTotal },
        { 0, -1 }
    };
    for( int i = 0; p_dsc[i].i_id != 0; i++ )
    {
        avi_chunk_STRING_t *p_strz = AVI_ChunkFind( p_info, p_dsc[i].i_id, 0, false );
        if( !p_strz || !p_strz->p_str )
            continue;
        char *psz_value = FromACP( p_strz->p_str );
        if( !psz_value )
            continue;

        if( *psz_value )
            vlc_meta_Set( p_meta, p_dsc[i].i_type, psz_value );
        free( psz_value );
    }

    static const vlc_fourcc_t p_extra[] = {
        AVIFOURCC_IARL, AVIFOURCC_ICMS, AVIFOURCC_ICRP, AVIFOURCC_IDIM, AVIFOURCC_IDPI,
        AVIFOURCC_IENG, AVIFOURCC_IKEY, AVIFOURCC_ILGT, AVIFOURCC_IMED, AVIFOURCC_IPLT,
        AVIFOURCC_IPRD, AVIFOURCC_ISBJ, AVIFOURCC_ISFT, AVIFOURCC_ISHP, AVIFOURCC_ISRC,
        AVIFOURCC_ISRF, AVIFOURCC_ITCH, AVIFOURCC_ISMP, AVIFOURCC_IDIT, AVIFOURCC_ISGN,
        AVIFOURCC_IWRI, AVIFOURCC_IPRO, AVIFOURCC_ICNM, AVIFOURCC_IPDS, AVIFOURCC_IEDT,
        AVIFOURCC_ICDS, AVIFOURCC_IMUS, AVIFOURCC_ISTD, AVIFOURCC_IDST, AVIFOURCC_ICNT,
        AVIFOURCC_ISTR, 0,
    };

    for( int i = 0; p_extra[i] != 0; i++ )
    {
        avi_chunk_STRING_t *p_strz = AVI_ChunkFind( p_info, p_extra[i], 0, false );
        if( !p_strz || !p_strz->p_str )
            continue;
        char *psz_value = FromACP( p_strz->p_str );
        if( !psz_value )
            continue;

        if( *psz_value )
            vlc_meta_AddExtra( p_meta, p_strz->p_type, psz_value );
        free( psz_value );
    }
}