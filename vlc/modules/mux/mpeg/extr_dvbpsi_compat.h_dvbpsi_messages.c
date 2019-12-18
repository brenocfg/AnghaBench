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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ dvbpsi_t ;
typedef  int dvbpsi_msg_level_t ;

/* Variables and functions */
#define  DVBPSI_MSG_DEBUG 131 
#define  DVBPSI_MSG_ERROR 130 
#define  DVBPSI_MSG_NONE 129 
#define  DVBPSI_MSG_WARN 128 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static inline void dvbpsi_messages(dvbpsi_t *p_dvbpsi, const dvbpsi_msg_level_t level, const char* msg)
{
    vlc_object_t *obj = (vlc_object_t *)p_dvbpsi->p_sys;

    /* See dvbpsi.h for the definition of these log levels.*/
    switch(level)
    {
        case DVBPSI_MSG_ERROR:
        {
#if DVBPSI_VERSION_INT <= ((1 << 16) + (2 << 8))
            if( strncmp( msg, "libdvbpsi (PMT decoder): ", 25 ) ||
                ( strncmp( &msg[25], "invalid section", 15 ) &&
                  strncmp( &msg[25], "'program_number' don't match", 28 ) ) )
#endif
            msg_Err( obj, "%s", msg ); break;
        }
        case DVBPSI_MSG_WARN:  msg_Warn( obj, "%s", msg ); break;
        case DVBPSI_MSG_NONE:
        case DVBPSI_MSG_DEBUG:
#ifdef DVBPSI_DEBUG
            msg_Dbg( obj, "%s", msg );
#endif
            break;
    }
}