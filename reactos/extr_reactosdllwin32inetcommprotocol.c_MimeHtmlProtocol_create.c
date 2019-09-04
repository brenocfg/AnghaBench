#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; TYPE_4__ IUnknown_inner; int /*<<< orphan*/ * sink; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * location; TYPE_4__* outer_unk; TYPE_2__ IInternetProtocolInfo_iface; TYPE_1__ IInternetProtocol_iface; } ;
typedef  TYPE_3__ MimeHtmlProtocol ;
typedef  TYPE_4__ IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  MimeHtmlProtocolInfoVtbl ; 
 int /*<<< orphan*/  MimeHtmlProtocolInnerVtbl ; 
 int /*<<< orphan*/  MimeHtmlProtocolVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* heap_alloc (int) ; 

HRESULT MimeHtmlProtocol_create(IUnknown *outer, void **obj)
{
    MimeHtmlProtocol *protocol;

    protocol = heap_alloc(sizeof(*protocol));
    if(!protocol)
        return E_OUTOFMEMORY;

    protocol->IUnknown_inner.lpVtbl = &MimeHtmlProtocolInnerVtbl;
    protocol->IInternetProtocol_iface.lpVtbl = &MimeHtmlProtocolVtbl;
    protocol->IInternetProtocolInfo_iface.lpVtbl = &MimeHtmlProtocolInfoVtbl;
    protocol->ref = 1;
    protocol->outer_unk = outer ? outer : &protocol->IUnknown_inner;
    protocol->location = NULL;
    protocol->stream = NULL;
    protocol->sink = NULL;

    *obj = &protocol->IUnknown_inner;
    return S_OK;
}