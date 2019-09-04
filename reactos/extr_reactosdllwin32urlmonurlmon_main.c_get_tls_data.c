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
struct TYPE_6__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ tls_data_t ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedCompareExchange (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 scalar_t__ TlsAlloc () ; 
 int /*<<< orphan*/  TlsFree (scalar_t__) ; 
 TYPE_1__* TlsGetValue (scalar_t__) ; 
 int /*<<< orphan*/  TlsSetValue (scalar_t__,TYPE_1__*) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_cs ; 
 int /*<<< orphan*/  tls_list ; 
 scalar_t__ urlmon_tls ; 

tls_data_t *get_tls_data(void)
{
    tls_data_t *data;

    if(urlmon_tls == TLS_OUT_OF_INDEXES) {
        DWORD tls = TlsAlloc();
        if(tls == TLS_OUT_OF_INDEXES)
            return NULL;

        tls = InterlockedCompareExchange((LONG*)&urlmon_tls, tls, TLS_OUT_OF_INDEXES);
        if(tls != urlmon_tls)
            TlsFree(tls);
    }

    data = TlsGetValue(urlmon_tls);
    if(!data) {
        data = heap_alloc_zero(sizeof(tls_data_t));
        if(!data)
            return NULL;

        EnterCriticalSection(&tls_cs);
        list_add_tail(&tls_list, &data->entry);
        LeaveCriticalSection(&tls_cs);

        TlsSetValue(urlmon_tls, data);
    }

    return data;
}