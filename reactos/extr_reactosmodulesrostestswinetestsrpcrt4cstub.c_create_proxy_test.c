#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_2__ {int ref; int /*<<< orphan*/  IUnknown_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRpcProxyBuffer ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  int HRESULT ;

/* Variables and functions */
 int IPSFactoryBuffer_CreateProxy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,void**) ; 
 int IRpcProxyBuffer_Release (int /*<<< orphan*/ *) ; 
 int IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 TYPE_1__ dummy_unknown ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void create_proxy_test( IPSFactoryBuffer *ppsf, REFIID iid, const void *expected_vtbl )
{
    IRpcProxyBuffer *proxy = NULL;
    IUnknown *iface = NULL;
    HRESULT r;
    ULONG count;

    r = IPSFactoryBuffer_CreateProxy(ppsf, NULL, iid, &proxy, (void **)&iface);
    ok( r == S_OK, "IPSFactoryBuffer_CreateProxy failed %x\n", r );
    ok( *(void **)iface == expected_vtbl, "wrong iface pointer %p/%p\n", *(void **)iface, expected_vtbl );
    count = IUnknown_Release( iface );
    ok( count == 1, "wrong refcount %u\n", count );
    count = IRpcProxyBuffer_Release( proxy );
    ok( count == 0, "wrong refcount %u\n", count );

    dummy_unknown.ref = 4;
    r = IPSFactoryBuffer_CreateProxy(ppsf, &dummy_unknown.IUnknown_iface, iid, &proxy,
            (void **)&iface);
    ok( r == S_OK, "IPSFactoryBuffer_CreateProxy failed %x\n", r );
    ok( dummy_unknown.ref == 5, "wrong refcount %u\n", dummy_unknown.ref );
    ok( *(void **)iface == expected_vtbl, "wrong iface pointer %p/%p\n", *(void **)iface, expected_vtbl );
    count = IUnknown_Release( iface );
    ok( count == 4, "wrong refcount %u\n", count );
    ok( dummy_unknown.ref == 4, "wrong refcount %u\n", dummy_unknown.ref );
    count = IRpcProxyBuffer_Release( proxy );
    ok( count == 0, "wrong refcount %u\n", count );
    ok( dummy_unknown.ref == 4, "wrong refcount %u\n", dummy_unknown.ref );
}