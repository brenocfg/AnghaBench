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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * strpbrk (char const*,char*) ; 

__attribute__((used)) static bool isXmlEncoded(const char* psz_str)
{
    assert( psz_str != NULL );
    //look for special characters
    if( strpbrk(psz_str, "<>'\"") != NULL )
        return false;

    bool is_escaped = false;
    while( true )
    {
        const char* psz_amp = strchr(psz_str, '&');
        if( psz_amp == NULL )
            break;
        const char* psz_end = strchr(psz_amp, ';');
        if(  psz_end == NULL )
            return false;

        else if(psz_amp[1] == '#')
        {
            if( psz_amp[2] == 'x' )
            {
                const char* psz_ptr = &psz_amp[3];
                if( psz_ptr  ==  psz_end )
                    return false;
                for (  ; psz_ptr < psz_end; psz_ptr++)
                    if( ! isxdigit( *psz_ptr ) )
                        return false;
            }
            else
            {
                const char* psz_ptr = &(psz_amp[2]);
                if( psz_ptr ==  psz_end )
                    return false;
                for (  ; psz_ptr < psz_end; psz_ptr++)
                    if( ! isdigit( *psz_ptr ) )
                        return false;
            }
        }
        else
        {
            const char* psz_ptr = &(psz_amp[1]);
            if( psz_ptr ==  psz_end )
                return false;
            for (  ; psz_ptr < psz_end; psz_ptr++)
                if( ! isalnum( *psz_ptr ) )
                    return false;
        }
        is_escaped = true;
        psz_str = psz_end;
    }
    return is_escaped;
}