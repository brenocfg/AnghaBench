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
 scalar_t__ SubsdelayGetWordRank (int) ; 

__attribute__((used)) static int SubsdelayGetTextRank( char *psz_text )
{
    bool b_skip_esc;
    bool b_skip_tag;
    char c;

    int i, i_word_length, i_rank;

    i = 0;
    i_word_length = 0;
    i_rank = 0;

    b_skip_esc = false;
    b_skip_tag = false;

    while ( psz_text[i] != '\0' )
    {
        c = psz_text[i];
        i++;

        if( c == '\\' && !b_skip_esc )
        {
            b_skip_esc = true;
            continue;
        }

        if( psz_text[i] == '<' )
        {
            b_skip_tag = true;
            continue;
        }

        if( !b_skip_esc && !b_skip_tag )
        {
            if( c == ' ' || c == ',' || c == '.' || c == '-' || c == '?' || c == '!' ) /* common delimiters */
            {
                if( i_word_length > 0 )
                {
                    i_rank += SubsdelayGetWordRank( i_word_length );
                }

                i_word_length = 0;
            }
            else
            {
                i_word_length++;
            }
        }

        b_skip_esc = false;

        if( c == '>' )
        {
            b_skip_tag = false;
        }

    }

    if( i_word_length > 0 )
    {
        i_rank += SubsdelayGetWordRank( i_word_length );
    }

    return i_rank;
}