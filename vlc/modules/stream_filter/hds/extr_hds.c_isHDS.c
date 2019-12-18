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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 char* FromCharset (char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 char* strndup (char const*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static bool isHDS( stream_t *s )
{
    const uint8_t *peek;
    int i_size = vlc_stream_Peek( s->s, &peek, 200 );
    if( i_size < 200 )
        return false;

    char *str;

    if( !memcmp( peek, "\xFF\xFE", 2 ) )
    {
        str = FromCharset( "UTF-16LE", peek, i_size );
    }
    else if( !memcmp( peek, "\xFE\xFF", 2 ) )
    {
        str = FromCharset( "UTF-16BE", peek, i_size );
    }
    else
        str = strndup( (const char *)peek, i_size );

    if( str == NULL )
        return false;

    bool ret = strstr( str, "<manifest" ) != NULL;
    free( str );
    return ret;
}