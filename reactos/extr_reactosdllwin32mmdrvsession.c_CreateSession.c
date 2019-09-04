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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  device_id; int /*<<< orphan*/  device_type; } ;
typedef  TYPE_1__ SessionInfo ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DeviceType ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__**) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetSession (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMSYSERR_ALLOCATED ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOMEM ; 
 TYPE_1__* session_list ; 
 int /*<<< orphan*/  session_lock ; 

MMRESULT
CreateSession(
    DeviceType device_type,
    UINT device_id,
    SessionInfo** session_info)
{
    HANDLE heap = GetProcessHeap();

    ASSERT(session_info);

    EnterCriticalSection(&session_lock);

    /* Ensure we're not creating a duplicate session */

    if ( GetSession(device_type, device_id) )
    {
        DPRINT("Already allocated session\n");
        LeaveCriticalSection(&session_lock);
        return MMSYSERR_ALLOCATED;
    }

    *session_info = HeapAlloc(heap, HEAP_ZERO_MEMORY, sizeof(SessionInfo));

    if ( ! *session_info )
    {
        DPRINT("Failed to allocate mem for session info\n");
        LeaveCriticalSection(&session_lock);
        return MMSYSERR_NOMEM;
    }

    (*session_info)->device_type = device_type;
    (*session_info)->device_id = device_id;

    /* Add to the list */

    (*session_info)->next = session_list;
    session_list = *session_info;

    LeaveCriticalSection(&session_lock);

    return MMSYSERR_NOERROR;
}