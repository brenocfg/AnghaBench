#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int random_seed; int /*<<< orphan*/  mbcinfo; int /*<<< orphan*/  locinfo; int /*<<< orphan*/  handle; int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ thread_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  mbcinfo; int /*<<< orphan*/  locinfo; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 TYPE_5__* MSVCRT_locale ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 TYPE_1__* TlsGetValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _RT_THREAD ; 
 int /*<<< orphan*/  _amsg_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msvcrt_tls_index ; 

thread_data_t *msvcrt_get_thread_data(void)
{
    thread_data_t *ptr;
    DWORD err = GetLastError();  /* need to preserve last error */

    if (!(ptr = TlsGetValue( msvcrt_tls_index )))
    {
        if (!(ptr = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ptr) )))
            _amsg_exit( _RT_THREAD );
        if (!TlsSetValue( msvcrt_tls_index, ptr )) _amsg_exit( _RT_THREAD );
        ptr->tid = GetCurrentThreadId();
        ptr->handle = INVALID_HANDLE_VALUE;
        ptr->random_seed = 1;
        ptr->locinfo = MSVCRT_locale->locinfo;
        ptr->mbcinfo = MSVCRT_locale->mbcinfo;
    }
    SetLastError( err );
    return ptr;
}