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
typedef  scalar_t__ vlc_iconv_t ;
typedef  enum cdtext_charset_e { ____Placeholder_cdtext_charset_e } cdtext_charset_e ;

/* Variables and functions */
#define  CDTEXT_CHARSET_ASCII7BIT 130 
#define  CDTEXT_CHARSET_ISO88591 129 
#define  CDTEXT_CHARSET_MSJIS 128 
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 scalar_t__ VLC_ICONV_ERR ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (char*) ; 
 scalar_t__ vlc_iconv (scalar_t__,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  vlc_iconv_close (scalar_t__) ; 
 scalar_t__ vlc_iconv_open (char*,char const*) ; 

__attribute__((used)) static void CdTextAppendPayload( const char *buffer, size_t i_len,
                                 enum cdtext_charset_e e_charset, char **ppsz_text )
{
    size_t i_alloc = *ppsz_text ? strlen( *ppsz_text ) : 0;
    size_t i_extend;
    const char *from_charset;
    switch( e_charset )
    {
        case CDTEXT_CHARSET_ASCII7BIT:
            i_extend = i_len;
            from_charset = NULL;
            break;
        case CDTEXT_CHARSET_ISO88591:
            i_extend = i_len * 2;
            from_charset = "ISO-8859-1";
            break;
        case CDTEXT_CHARSET_MSJIS:
            i_extend = i_len * 4;
            from_charset = "SHIFT-JIS";
            break;
        default: /* no known conversion */
            return;
    }
    size_t i_newsize = i_alloc + i_extend * 2 + 1;

    char *psz_realloc = realloc( *ppsz_text, i_newsize );
    if( !psz_realloc )
        return;
    *ppsz_text = psz_realloc;

    /* copy/convert result */
    if ( from_charset == NULL )
    {
        memcpy( &psz_realloc[i_alloc], buffer, i_len );
        psz_realloc[i_alloc + i_len] = 0;
        EnsureUTF8( psz_realloc );
    }
    else
    {
        vlc_iconv_t ic = vlc_iconv_open( "UTF-8", from_charset );
        if( ic != (vlc_iconv_t) -1 )
        {
            const char *psz_in = buffer;
            size_t i_in = i_len;
            char *psz_out = &psz_realloc[i_alloc];
            size_t i_out = i_extend;
            if( VLC_ICONV_ERR != vlc_iconv( ic, &psz_in, &i_in, &psz_out, &i_out ) )
                psz_realloc[i_alloc + i_extend - i_out] = 0;
            vlc_iconv_close( ic );
        }
    }
}