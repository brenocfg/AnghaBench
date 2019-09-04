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
struct TYPE_3__ {int /*<<< orphan*/  IWICBitmapDecoder_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BmpDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  BmpDecoder_Create (int,int,TYPE_1__**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT BmpDecoder_Construct(int packed, int icoframe, REFIID iid, void** ppv)
{
    BmpDecoder *This;
    HRESULT ret;

    TRACE("(%s,%p)\n", debugstr_guid(iid), ppv);

    *ppv = NULL;

    ret = BmpDecoder_Create(packed, icoframe, &This);
    if (FAILED(ret)) return ret;

    ret = IWICBitmapDecoder_QueryInterface(&This->IWICBitmapDecoder_iface, iid, ppv);
    IWICBitmapDecoder_Release(&This->IWICBitmapDecoder_iface);

    return ret;
}