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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 char* FromCharset (char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ load_byte (unsigned char,unsigned char*,char**,unsigned char*,unsigned char*) ; 
 unsigned char* malloc (unsigned int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *nscdec( vlc_object_t *p_demux, char* p_encoded )
{
    unsigned int i;
    unsigned char tmp;
    unsigned char j, k;
    unsigned int length;
    unsigned char encoding_type;

    unsigned char *buf16;
    char *buf8;

    char *p_input = p_encoded;

    if( strlen( p_input ) < 15 )
    {
        msg_Err( p_demux, "input string less than 15 characters" );
        return NULL;
    }

    if( load_byte( 1, &encoding_type, &p_input, NULL, NULL ) )
    {
        msg_Err( p_demux, "unable to get NSC encoding type" );
        return NULL;
    }

    if( encoding_type != 1 && encoding_type != 2 )
    {
        msg_Err( p_demux, "encoding type %d is not supported",
                 encoding_type );
        return NULL;
    }

    j = k = 0;

    if( load_byte( encoding_type, &tmp, &p_input, &j, &k ) )
    {
        msg_Err( p_demux, "load_byte failed" );
        return NULL;
    }

    for( i = 0; i < 4; i++ )
    {
        if( load_byte( encoding_type, &tmp, &p_input, &j, &k ) )
        {
            msg_Err( p_demux, "load_byte failed" );
            return NULL;
        }
    }

    length = 0;
    for( i = 4; i; i-- )
    {
        if( load_byte( encoding_type, &tmp, &p_input, &j, &k ) )
        {
            msg_Err( p_demux, "load_byte failed" );
            return NULL;
        }
        length |= (unsigned int)tmp << ((i - 1) * 8);
    }

    if( length == 0 )
    {
        msg_Err( p_demux, "Length is 0" );
        return NULL;
    }

    buf16 = malloc( length );
    if( buf16 == NULL )
        return NULL;

    for( i = 0; i < length; i++ )
    {
        if( load_byte( encoding_type, &buf16[ i ], &p_input, &j, &k ) )
        {
            msg_Err( p_demux, "load_byte failed" );
            free( buf16 );
            return NULL;
        }
    }

    buf8 = FromCharset( "UTF-16LE", buf16, length );
    free( buf16 );
    if( buf8 == NULL )
    {
        msg_Err( p_demux, "iconv failed" );
        return NULL;
    }
    return buf8;
}