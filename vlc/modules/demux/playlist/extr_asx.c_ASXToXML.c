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
struct vlc_memstream {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memstream_puts_xmlencoded (struct vlc_memstream*,char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 char vlc_ascii_toupper (char) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,char) ; 

__attribute__((used)) static char* ASXToXML( char* psz_source )
{
    bool b_in_string= false;
    char *psz_source_cur = psz_source;
    char *psz_source_old = psz_source;
    char c_string_delim;

    struct vlc_memstream stream_out;
    if( vlc_memstream_open( &stream_out ) != 0 )
        return NULL;

    while ( psz_source_cur != NULL && *psz_source_cur != '\0' )
    {
        psz_source_old = psz_source_cur;
        //search tag start
        if( ( psz_source_cur = strchr( psz_source_cur, '<' ) ) == NULL )
        {
            memstream_puts_xmlencoded(&stream_out, psz_source_old, NULL);
            //vlc_memstream_puts( &stream_out, psz_source_old );
            break;
        }

        memstream_puts_xmlencoded(&stream_out, psz_source_old, psz_source_cur);
        psz_source_old = psz_source_cur;

        //skip if comment, no need to copy them to the ouput.
        if( strncmp( psz_source_cur, "<!--", 4 ) == 0 )
        {
            psz_source_cur += 4;
            psz_source_cur =  strstr( psz_source_cur, "-->" );
            if( psz_source_cur == NULL)
                break;
            else
            {
                psz_source_cur += 3;
                continue;
            }
        }
        else
        {
            vlc_memstream_putc( &stream_out, '<' );
            psz_source_cur++;
        }

        for (  ; *psz_source_cur != '\0'; psz_source_cur++ )
        {
            if( b_in_string == false )
            {
                if( *psz_source_cur == '>')
                {
                    vlc_memstream_putc( &stream_out, '>' );
                    psz_source_cur++;
                    break;
                }
                if( *psz_source_cur == '"' || *psz_source_cur == '\'' )
                {
                    c_string_delim = *psz_source_cur;
                    b_in_string = true;
                    vlc_memstream_putc( &stream_out, c_string_delim );
                }
                else
                {
                    //convert tag and attributes to upper case
                    vlc_memstream_putc( &stream_out, vlc_ascii_toupper( *psz_source_cur ) );
                }
            }
            else
            {
                psz_source_old = psz_source_cur;
                psz_source_cur = strchr( psz_source_cur, c_string_delim );
                if( psz_source_cur == NULL )
                    break;

                memstream_puts_xmlencoded(&stream_out, psz_source_old, psz_source_cur);
                vlc_memstream_putc( &stream_out, c_string_delim );
                b_in_string = false;
            }
        }
    }
    if( vlc_memstream_close( &stream_out ) != 0 )
        return NULL;

    return stream_out.ptr;
}