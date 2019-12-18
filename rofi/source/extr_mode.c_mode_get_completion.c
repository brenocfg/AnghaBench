#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* (* _get_completion ) (TYPE_1__ const*,unsigned int) ;char* (* _get_display_value ) (TYPE_1__ const*,unsigned int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 char* stub1 (TYPE_1__ const*,unsigned int) ; 
 char* stub2 (TYPE_1__ const*,unsigned int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char * mode_get_completion ( const Mode *mode, unsigned int selected_line )
{
    g_assert ( mode != NULL );
    if ( mode->_get_completion != NULL ) {
        return mode->_get_completion ( mode, selected_line );
    }
    else {
        int state;
        g_assert ( mode->_get_display_value != NULL );
        return mode->_get_display_value ( mode, selected_line, &state, NULL, TRUE );
    }
}