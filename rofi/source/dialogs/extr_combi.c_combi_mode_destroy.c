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
struct TYPE_3__ {unsigned int num_switchers; struct TYPE_3__* switchers; int /*<<< orphan*/  mode; struct TYPE_3__* lengths; struct TYPE_3__* starts; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ CombiModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mode_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void combi_mode_destroy ( Mode *sw )
{
    CombiModePrivateData *pd = (CombiModePrivateData *) mode_get_private_data ( sw );
    if ( pd != NULL ) {
        g_free ( pd->starts );
        g_free ( pd->lengths );
        // Cleanup switchers.
        for ( unsigned int i = 0; i < pd->num_switchers; i++ ) {
            mode_destroy ( pd->switchers[i].mode );
        }
        g_free ( pd->switchers );
        g_free ( pd );
        mode_set_private_data ( sw, NULL );
    }
}