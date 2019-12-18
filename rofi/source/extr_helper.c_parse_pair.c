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
struct TYPE_3__ {int start; int stop; } ;
typedef  TYPE_1__ rofi_range_pair ;

/* Variables and functions */
 scalar_t__ isblank (char) ; 
 scalar_t__ strchr (char*,char) ; 
 char* strsep (char**,char const*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_pair ( char  *input, rofi_range_pair  *item )
{
    // Skip leading blanks.
    while ( input != NULL && isblank(*input) )
        ++input;

    const char *sep[] = { "-", ":" };
    int         pythonic = ( strchr(input, ':') || input[0] == '-' ) ? 1 : 0;
    int         index = 0;

    for (  char *token = strsep ( &input, sep[pythonic] ); token != NULL; token = strsep ( &input, sep[pythonic] ) ) {
        if ( index == 0 ) {
            item->start = item->stop = (int) strtol ( token, NULL, 10 );
            index++;
            continue;
        }

        if ( token[0] == '\0' ) {
            item->stop = -1;
            continue;
        }

        item->stop = (int) strtol ( token, NULL, 10 );
        if ( pythonic ) {
            --item->stop;
        }
    }
}