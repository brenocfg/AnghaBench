#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ device_type; scalar_t__ device_id; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SessionInfo ;
typedef  scalar_t__ DeviceType ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__* session_list ; 
 int /*<<< orphan*/  session_lock ; 

SessionInfo*
GetSession(
    DeviceType device_type,
    UINT device_id)
{
    SessionInfo* session_info;

    EnterCriticalSection(&session_lock);
    session_info = session_list;

    while ( session_info )
    {
        if ( ( session_info->device_type == device_type ) &&
             ( session_info->device_id == device_id ) )
        {
            LeaveCriticalSection(&session_lock);
            return session_info;
        }

        session_info = session_info->next;
    }

    LeaveCriticalSection(&session_lock);
    return NULL;
}