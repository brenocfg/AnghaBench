#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stub_manager {TYPE_1__* apt; } ;
typedef  void* USHORT ;
struct TYPE_7__ {void* Data3; void* Data2; int /*<<< orphan*/  Data1; } ;
struct TYPE_6__ {scalar_t__ tid; int /*<<< orphan*/  ipidc; } ;
typedef  TYPE_2__ IPID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,struct stub_manager*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentProcessId () ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  UuidCreate (TYPE_2__*) ; 
 int /*<<< orphan*/  UuidCreateNil (TYPE_2__*) ; 

__attribute__((used)) static inline HRESULT generate_ipid(struct stub_manager *m, IPID *ipid)
{
    HRESULT hr;
    hr = UuidCreate(ipid);
    if (FAILED(hr))
    {
        ERR("couldn't create IPID for stub manager %p\n", m);
        UuidCreateNil(ipid);
        return hr;
    }

    ipid->Data1 = InterlockedIncrement(&m->apt->ipidc);
    ipid->Data2 = (USHORT)m->apt->tid;
    ipid->Data3 = (USHORT)GetCurrentProcessId();
    return S_OK;
}