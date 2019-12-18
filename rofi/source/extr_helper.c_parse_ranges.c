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
struct rofi_range_pair {int dummy; } ;
typedef  int /*<<< orphan*/  rofi_range_pair ;

/* Variables and functions */
 int /*<<< orphan*/ * g_realloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  parse_pair (char*,int /*<<< orphan*/ *) ; 
 char* strtok_r (char*,char const* const,char**) ; 

void parse_ranges ( char *input, rofi_range_pair **list, unsigned int *length )
{
    char *endp;
    if ( input == NULL ) {
        return;
    }
    const char *const sep = ",";
    for ( char *token = strtok_r ( input, sep, &endp ); token != NULL; token = strtok_r ( NULL, sep, &endp ) ) {
        // Make space.
        *list = g_realloc ( ( *list ), ( ( *length ) + 1 ) * sizeof ( struct rofi_range_pair ) );
        // Parse a single pair.
        parse_pair ( token, &( ( *list )[*length] ) );

        ( *length )++;
    }
}