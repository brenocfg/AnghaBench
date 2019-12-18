#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* starts; int num_switchers; unsigned int* lengths; scalar_t__ cmd_list_length; TYPE_1__* switchers; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_2__ CombiModePrivateData ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  combi_mode_parse_switchers (int /*<<< orphan*/ *) ; 
 void* g_malloc0 (int) ; 
 unsigned int mode_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int combi_mode_init ( Mode *sw )
{
    if ( mode_get_private_data ( sw ) == NULL ) {
        CombiModePrivateData *pd = g_malloc0 ( sizeof ( *pd ) );
        mode_set_private_data ( sw, (void *) pd );
        combi_mode_parse_switchers ( sw );
        pd->starts  = g_malloc0 ( sizeof ( int ) * pd->num_switchers );
        pd->lengths = g_malloc0 ( sizeof ( int ) * pd->num_switchers );
        for ( unsigned int i = 0; i < pd->num_switchers; i++ ) {
            if ( !mode_init ( pd->switchers[i].mode ) ) {
                return FALSE;
            }
        }
        if ( pd->cmd_list_length == 0 ) {
            pd->cmd_list_length = 0;
            for ( unsigned int i = 0; i < pd->num_switchers; i++ ) {
                unsigned int length = mode_get_num_entries ( pd->switchers[i].mode );
                pd->starts[i]        = pd->cmd_list_length;
                pd->lengths[i]       = length;
                pd->cmd_list_length += length;
            }
        }
    }
    return TRUE;
}