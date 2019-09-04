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
struct TYPE_3__ {scalar_t__ serv_prov; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BindStatusCallback ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IServiceProvider_QueryService (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *get_callback_iface(BindStatusCallback *This, REFIID riid)
{
    void *ret;
    HRESULT hres;

    hres = IBindStatusCallback_QueryInterface(This->callback, riid, (void**)&ret);
    if(FAILED(hres) && This->serv_prov)
        hres = IServiceProvider_QueryService(This->serv_prov, riid, riid, &ret);

    return SUCCEEDED(hres) ? ret : NULL;
}