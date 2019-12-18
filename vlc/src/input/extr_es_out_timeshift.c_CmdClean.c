#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_type; } ;
typedef  TYPE_1__ ts_cmd_t ;

/* Variables and functions */
#define  C_ADD 131 
#define  C_CONTROL 130 
#define  C_DEL 129 
#define  C_SEND 128 
 int /*<<< orphan*/  CmdCleanAdd (TYPE_1__*) ; 
 int /*<<< orphan*/  CmdCleanControl (TYPE_1__*) ; 
 int /*<<< orphan*/  CmdCleanSend (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void CmdClean( ts_cmd_t *p_cmd )
{
    switch( p_cmd->i_type )
    {
    case C_ADD:
        CmdCleanAdd( p_cmd );
        break;
    case C_SEND:
        CmdCleanSend( p_cmd );
        break;
    case C_CONTROL:
        CmdCleanControl( p_cmd );
        break;
    case C_DEL:
        break;
    default:
        vlc_assert_unreachable();
        break;
    }
}