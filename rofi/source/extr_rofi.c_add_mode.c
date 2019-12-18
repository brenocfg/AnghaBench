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
typedef  int /*<<< orphan*/  Mode ;

/* Variables and functions */
 scalar_t__ g_realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** modi ; 
 int num_modi ; 
 int /*<<< orphan*/  rofi_collect_modi_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rofi_collect_modi_search (char const*) ; 
 scalar_t__ script_switcher_is_valid (char const*) ; 
 int /*<<< orphan*/ * script_switcher_parse_setup (char const*) ; 

__attribute__((used)) static int add_mode ( const char * token )
{
    unsigned int index = num_modi;
    // Resize and add entry.
    modi = (Mode * *) g_realloc ( modi, sizeof ( Mode* ) * ( num_modi + 1 ) );

    Mode *mode = rofi_collect_modi_search ( token );
    if ( mode ) {
        modi[num_modi] = mode;
        num_modi++;
    }
    else if ( script_switcher_is_valid ( token ) ) {
        // If not build in, use custom modi.
        Mode *sw = script_switcher_parse_setup ( token );
        if ( sw != NULL ) {
            // Add to available list, so combi can find it.
            rofi_collect_modi_add ( sw );
            modi[num_modi] = sw;
            num_modi++;
        }
    }
    return ( index == num_modi ) ? -1 : (int) index;
}