#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_iconv_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pf_block; int /*<<< orphan*/ * pf_read; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_11__ {scalar_t__ conv; int little_endian; int char_width; } ;
struct TYPE_13__ {TYPE_1__ text; } ;
typedef  TYPE_3__ stream_priv_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int STREAM_LINE_MAX ; 
 int STREAM_PROBE_LINE ; 
 int U16_AT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* memchr (int /*<<< orphan*/  const*,char,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 char* realloc_or_free (char*,int) ; 
 scalar_t__ unlikely (int) ; 
 size_t vlc_iconv (scalar_t__,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  vlc_iconv_close (scalar_t__) ; 
 scalar_t__ vlc_iconv_open (char*,char const*) ; 
 int vlc_stream_Peek (TYPE_2__*,int /*<<< orphan*/  const**,int) ; 
 int vlc_stream_Read (TYPE_2__*,char*,int) ; 
 scalar_t__ vlc_stream_Tell (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

char *vlc_stream_ReadLine( stream_t *s )
{
    stream_priv_t *priv = (stream_priv_t *)s;
    char *p_line = NULL;
    int i_line = 0, i_read = 0;

    /* Let's fail quickly if this is a readdir access */
    if( s->pf_read == NULL && s->pf_block == NULL )
        return NULL;

    for( ;; )
    {
        char *psz_eol;
        const uint8_t *p_data;
        int i_data;
        int64_t i_pos;

        /* Probe new data */
        i_data = vlc_stream_Peek( s, &p_data, STREAM_PROBE_LINE );
        if( i_data <= 0 ) break; /* No more data */

        /* BOM detection */
        i_pos = vlc_stream_Tell( s );
        if( i_pos == 0 && i_data >= 2 )
        {
            const char *psz_encoding = NULL;

            if( unlikely(priv->text.conv != (vlc_iconv_t)-1) )
            {   /* seek back to beginning? reset */
                vlc_iconv_close( priv->text.conv );
                priv->text.conv = (vlc_iconv_t)-1;
            }

            if( !memcmp( p_data, "\xFF\xFE", 2 ) )
            {
                psz_encoding = "UTF-16LE";
                priv->text.little_endian = true;
            }
            else if( !memcmp( p_data, "\xFE\xFF", 2 ) )
            {
                psz_encoding = "UTF-16BE";
            }

            /* Open the converter if we need it */
            if( psz_encoding != NULL )
            {
                msg_Dbg( s, "UTF-16 BOM detected" );
                priv->text.conv = vlc_iconv_open( "UTF-8", psz_encoding );
                if( unlikely(priv->text.conv == (vlc_iconv_t)-1) )
                {
                    msg_Err( s, "iconv_open failed" );
                    goto error;
                }
                priv->text.char_width = 2;
            }
        }

        if( i_data % priv->text.char_width )
        {
            /* keep i_char_width boundary */
            i_data = i_data - ( i_data % priv->text.char_width );
            msg_Warn( s, "the read is not i_char_width compatible");
        }

        if( i_data == 0 )
            break;

        /* Check if there is an EOL */
        if( priv->text.char_width == 1 )
        {
            /* UTF-8: 0A <LF> */
            psz_eol = memchr( p_data, '\n', i_data );
            if( psz_eol == NULL )
                /* UTF-8: 0D <CR> */
                psz_eol = memchr( p_data, '\r', i_data );
        }
        else
        {
            const uint8_t *p_last = p_data + i_data - priv->text.char_width;
            uint16_t eol = priv->text.little_endian ? 0x0A00 : 0x00A0;

            assert( priv->text.char_width == 2 );
            psz_eol = NULL;
            /* UTF-16: 000A <LF> */
            for( const uint8_t *p = p_data; p <= p_last; p += 2 )
            {
                if( U16_AT( p ) == eol )
                {
                     psz_eol = (char *)p + 1;
                     break;
                }
            }

            if( psz_eol == NULL )
            {   /* UTF-16: 000D <CR> */
                eol = priv->text.little_endian ? 0x0D00 : 0x00D0;
                for( const uint8_t *p = p_data; p <= p_last; p += 2 )
                {
                    if( U16_AT( p ) == eol )
                    {
                        psz_eol = (char *)p + 1;
                        break;
                    }
                }
            }
        }

        if( psz_eol )
        {
            i_data = (psz_eol - (char *)p_data) + 1;
            p_line = realloc_or_free( p_line,
                        i_line + i_data + priv->text.char_width ); /* add \0 */
            if( !p_line )
                goto error;
            i_data = vlc_stream_Read( s, &p_line[i_line], i_data );
            if( i_data <= 0 ) break; /* Hmmm */
            i_line += i_data - priv->text.char_width; /* skip \n */;
            i_read += i_data;

            /* We have our line */
            break;
        }

        /* Read data (+1 for easy \0 append) */
        p_line = realloc_or_free( p_line,
                          i_line + STREAM_PROBE_LINE + priv->text.char_width );
        if( !p_line )
            goto error;
        i_data = vlc_stream_Read( s, &p_line[i_line], STREAM_PROBE_LINE );
        if( i_data <= 0 ) break; /* Hmmm */
        i_line += i_data;
        i_read += i_data;

        if( i_read >= STREAM_LINE_MAX )
            goto error; /* line too long */
    }

    if( i_read > 0 )
    {
        if( priv->text.char_width > 1 )
        {
            int i_new_line = 0;
            size_t i_in = 0, i_out = 0;
            const char * p_in = NULL;
            char * p_out = NULL;
            char * psz_new_line = NULL;

            /* iconv */
            /* UTF-8 needs at most 150% of the buffer as many as UTF-16 */
            i_new_line = i_line * 3 / 2 + 1;
            psz_new_line = malloc( i_new_line );
            if( psz_new_line == NULL )
                goto error;
            i_in = (size_t)i_line;
            i_out = (size_t)i_new_line;
            p_in = p_line;
            p_out = psz_new_line;

            if( vlc_iconv( priv->text.conv, &p_in, &i_in, &p_out, &i_out ) == (size_t)-1 )
            {
                msg_Err( s, "conversion error: %s", vlc_strerror_c( errno ) );
                msg_Dbg( s, "original: %d, in %zu, out %zu", i_line, i_in, i_out );
            }
            free( p_line );
            p_line = psz_new_line;
            i_line = (size_t)i_new_line - i_out; /* does not include \0 */
        }

        /* Remove trailing LF/CR */
        while( i_line >= 1 &&
               (p_line[i_line - 1] == '\r' || p_line[i_line - 1] == '\n') )
            i_line--;

        /* Make sure the \0 is there */
        p_line[i_line] = '\0';

        return p_line;
    }

error:
    /* We failed to read any data, probably EOF */
    free( p_line );

    /* */
    if( priv->text.conv != (vlc_iconv_t)(-1) )
    {
        vlc_iconv_close( priv->text.conv );
        priv->text.conv = (vlc_iconv_t)(-1);
    }
    return NULL;
}