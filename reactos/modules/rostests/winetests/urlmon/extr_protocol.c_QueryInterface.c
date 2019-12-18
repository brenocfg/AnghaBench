#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_9__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_2__ IID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 TYPE_2__ const IID_IInternetProtocolSink ; 
 TYPE_2__ const IID_IServiceProvider ; 
 TYPE_2__ const IID_IUnknown ; 
 TYPE_2__ const IID_IUriContainer ; 
 scalar_t__ IsEqualGUID (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocol_sink ; 
 int /*<<< orphan*/  service_provider ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT QueryInterface(REFIID riid, void **ppv)
{
    static const IID IID_undocumented = {0x58DFC7D0,0x5381,0x43E5,{0x9D,0x72,0x4C,0xDD,0xE4,0xCB,0x0F,0x1A}};
    static const IID IID_undocumentedIE10 = {0xc28722e5,0xbc1a,0x4c55,{0xa6,0x8d,0x33,0x21,0x9f,0x69,0x89,0x10}};

    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid) || IsEqualGUID(&IID_IInternetProtocolSink, riid))
        *ppv = &protocol_sink;
    if(IsEqualGUID(&IID_IServiceProvider, riid))
        *ppv = &service_provider;
    if(IsEqualGUID(&IID_IUriContainer, riid))
        return E_NOINTERFACE; /* TODO */

    /* NOTE: IE8 queries for undocumented {58DFC7D0-5381-43E5-9D72-4CDDE4CB0F1A} interface. */
    if(IsEqualGUID(&IID_undocumented, riid))
        return E_NOINTERFACE;
    /* NOTE: IE10 queries for undocumented {c28722e5-bc1a-4c55-a68d-33219f698910} interface. */
    if(IsEqualGUID(&IID_undocumentedIE10, riid))
        return E_NOINTERFACE;

    if(*ppv)
        return S_OK;

    ok(0, "unexpected call %s\n", wine_dbgstr_guid(riid));
    return E_NOINTERFACE;
}