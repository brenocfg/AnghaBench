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
 int /*<<< orphan*/  scan_token_strip (char const**,size_t*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static bool scan_list_token_split( const char *psz_line, size_t i_len,
                                   const char **ppsz_key, size_t *pi_keylen,
                                   const char **ppsz_value, size_t *pi_valuelen )
{
    const char *p_split = strchr( psz_line, '=' );
    if( !p_split )
        return false;

    size_t i_keylen = p_split - psz_line;
    p_split++;
    size_t i_valuelen = &psz_line[i_len] - p_split;

    scan_token_strip( &psz_line, &i_keylen );
    scan_token_strip( &p_split, &i_valuelen );

    if( !i_keylen || !i_valuelen )
        return false;

    *ppsz_key = psz_line;
    *pi_keylen = i_keylen;

    *ppsz_value = p_split;
    *pi_valuelen = i_valuelen;

    return true;
}