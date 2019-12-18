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
struct TYPE_3__ {int invert; int /*<<< orphan*/  regex; } ;
typedef  TYPE_1__ rofi_int_matcher ;

/* Variables and functions */
 int TRUE ; 
 int g_regex_match (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int helper_token_match ( rofi_int_matcher* const *tokens, const char *input )
{
    int match = TRUE;
    // Do a tokenized match.
    if ( tokens ) {
        for ( int j = 0; match && tokens[j]; j++ ) {
            match  = g_regex_match ( tokens[j]->regex, input, 0, NULL );
            match ^= tokens[j]->invert;
        }
    }
    return match;
}