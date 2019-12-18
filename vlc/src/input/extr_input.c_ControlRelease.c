#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_5__ {int /*<<< orphan*/ ** ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_address; } ;
struct TYPE_7__ {TYPE_1__ list; int /*<<< orphan*/ * id; TYPE_2__ val; } ;
typedef  TYPE_3__ input_control_param_t ;

/* Variables and functions */
#define  INPUT_CONTROL_ADD_SLAVE 133 
#define  INPUT_CONTROL_RESTART_ES 132 
#define  INPUT_CONTROL_SET_ES 131 
#define  INPUT_CONTROL_SET_ES_LIST 130 
#define  INPUT_CONTROL_SET_RENDERER 129 
#define  INPUT_CONTROL_UNSET_ES 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  input_item_slave_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_es_id_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_renderer_item_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ControlRelease( int i_type, const input_control_param_t *p_param )
{
    if( p_param == NULL )
        return;

    switch( i_type )
    {
    case INPUT_CONTROL_ADD_SLAVE:
        if( p_param->val.p_address )
            input_item_slave_Delete( p_param->val.p_address );
        break;
    case INPUT_CONTROL_SET_RENDERER:
        if( p_param->val.p_address )
            vlc_renderer_item_release( p_param->val.p_address );
        break;
    case INPUT_CONTROL_SET_ES:
    case INPUT_CONTROL_UNSET_ES:
    case INPUT_CONTROL_RESTART_ES:
        vlc_es_id_Release( p_param->id );
        break;
    case INPUT_CONTROL_SET_ES_LIST:
    {
        for (size_t i = 0; ; i++)
        {
            vlc_es_id_t *es_id = p_param->list.ids[i];
            if (es_id == NULL)
                break;
            vlc_es_id_Release(es_id);
        }
        free(p_param->list.ids);
        break;
    }

    default:
        break;
    }
}