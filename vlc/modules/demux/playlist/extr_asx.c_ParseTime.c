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
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int vlc_tick_t ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 scalar_t__ VLC_TICK_FROM_US (int) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isdigit (char) ; 
 char* strdup (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static bool ParseTime(xml_reader_t *p_xml_reader, vlc_tick_t* pi_result )
{
    assert( pi_result );
    char *psz_value = NULL;
    char *psz_start = NULL;

    const char *psz_node = NULL;
    const char *psz_txt = NULL;

    int i_subfractions = -1;

    int i_subresult = 0;
    vlc_tick_t i_result = 0;

    do
    {
        psz_txt = xml_ReaderNextAttr( p_xml_reader, &psz_node );
    }
    while( psz_txt && strncasecmp( psz_txt, "VALUE", 5 ) );

    if( !psz_txt )
        return false;

    psz_value = strdup( psz_node );
    psz_start = psz_value;

    while( *psz_value )
    {
        if( isdigit( *psz_value ) )
        {
            i_subresult = i_subresult * 10;
            i_subresult += *psz_value - '0';
            if( i_subfractions != -1 )
                i_subfractions++;
        }
        else if( *psz_value == ':' )
        {
            i_result += i_subresult;
            i_result = i_result * 60;
            i_subresult = 0;
        }
        else if( *psz_value == '.' )
        {
            i_subfractions = 0;
            i_result += i_subresult;
            i_subresult = 0;
        }
        psz_value++;

    }
    if( i_subfractions == -1)
        i_result += i_subresult;

    /* Convert to microseconds */
    if( i_subfractions == -1)
        i_subfractions = 0;
    while( i_subfractions < 6 )
    {
        i_subresult = i_subresult * 10;
        i_subfractions++;
    }
    i_result = i_result * CLOCK_FREQ;
    if( i_subfractions != -1)
        i_result += VLC_TICK_FROM_US( i_subresult );

    free( psz_start );
    *pi_result = i_result;
    return true;
}