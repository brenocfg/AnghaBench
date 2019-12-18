#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_10__ {TYPE_2__* p_hdlr; } ;
struct TYPE_11__ {int i_size; int i_handler; scalar_t__ i_type; struct TYPE_11__* p_next; TYPE_3__ data; TYPE_1__* p_father; } ;
struct TYPE_9__ {int i_handler_type; } ;
struct TYPE_8__ {TYPE_4__* p_first; } ;
typedef  TYPE_4__ MP4_Box_t ;

/* Variables and functions */
 scalar_t__ ATOM_hdlr ; 
#define  HANDLER_mdir 129 
#define  HANDLER_mdta 128 
 int MP4_ReadBoxContainerChildren (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int MP4_ReadBoxContainerChildrenIndexed (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,...) ; 
 int vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int MP4_ReadBox_ilst( stream_t *p_stream, MP4_Box_t *p_box )
{
    if( p_box->i_size < 8 || vlc_stream_Read( p_stream, NULL, 8 ) < 8 )
        return 0;

    /* Find our handler */
    if ( !p_box->i_handler && p_box->p_father )
    {
        const MP4_Box_t *p_sibling = p_box->p_father->p_first;
        while( p_sibling )
        {
            if ( p_sibling->i_type == ATOM_hdlr && p_sibling->data.p_hdlr )
            {
                p_box->i_handler = p_sibling->data.p_hdlr->i_handler_type;
                break;
            }
            p_sibling = p_sibling->p_next;
        }
    }

    switch( p_box->i_handler )
    {
    case 0:
        msg_Warn( p_stream, "no handler for ilst atom" );
        return 0;
    case HANDLER_mdta:
        return MP4_ReadBoxContainerChildrenIndexed( p_stream, p_box, NULL, NULL, true );
    case HANDLER_mdir:
        return MP4_ReadBoxContainerChildren( p_stream, p_box, NULL );
    default:
        msg_Warn( p_stream, "Unknown ilst handler type '%4.4s'", (char*)&p_box->i_handler );
        return 0;
    }
}