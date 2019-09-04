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
struct TYPE_4__ {struct TYPE_4__* time_buffer; struct TYPE_4__* wcserror_buffer; struct TYPE_4__* strerror_buffer; struct TYPE_4__* wasctime_buffer; struct TYPE_4__* asctime_buffer; struct TYPE_4__* efcvt_buffer; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ thread_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* TlsGetValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msvcrt_tls_index ; 

void msvcrt_free_tls_mem(void)
{
  thread_data_t *tls = TlsGetValue(msvcrt_tls_index);

  if (tls)
  {
    CloseHandle(tls->handle);
    HeapFree(GetProcessHeap(),0,tls->efcvt_buffer);
    HeapFree(GetProcessHeap(),0,tls->asctime_buffer);
    HeapFree(GetProcessHeap(),0,tls->wasctime_buffer);
    HeapFree(GetProcessHeap(),0,tls->strerror_buffer);
    HeapFree(GetProcessHeap(),0,tls->wcserror_buffer);
    HeapFree(GetProcessHeap(),0,tls->time_buffer);
    //if(tls->have_locale) {
    //    free_locinfo(tls->locinfo);
    //    free_mbcinfo(tls->mbcinfo);
    //}
  }
  HeapFree(GetProcessHeap(), 0, tls);
}