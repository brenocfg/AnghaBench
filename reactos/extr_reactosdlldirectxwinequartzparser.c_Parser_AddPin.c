#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  IBaseFilter_iface; int /*<<< orphan*/  csFilter; } ;
struct TYPE_13__ {int cStreams; int /*<<< orphan*/ ** ppPins; TYPE_8__ filter; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pFilter; } ;
struct TYPE_10__ {TYPE_1__ pinInfo; } ;
struct TYPE_11__ {TYPE_2__ pin; } ;
struct TYPE_12__ {int /*<<< orphan*/  allocProps; TYPE_3__ pin; scalar_t__ dwSamplesProcessed; void* pmt; } ;
typedef  TYPE_4__ Parser_OutputPin ;
typedef  TYPE_5__ ParserImpl ;
typedef  int /*<<< orphan*/  PIN_INFO ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  AM_MEDIA_TYPE ;
typedef  int /*<<< orphan*/  ALLOCATOR_PROPERTIES ;

/* Variables and functions */
 int /*<<< orphan*/  BaseFilterImpl_IncrementPinVersion (TYPE_8__*) ; 
 int /*<<< orphan*/  BaseOutputPin_Construct (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CopyMediaType (void*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parser_OutputPin_Vtbl ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  output_BaseOutputFuncTable ; 
 TYPE_4__* unsafe_impl_Parser_OutputPin_from_IPin (int /*<<< orphan*/ *) ; 

HRESULT Parser_AddPin(ParserImpl * This, const PIN_INFO * piOutput, ALLOCATOR_PROPERTIES * props, const AM_MEDIA_TYPE * amt)
{
    IPin ** ppOldPins;
    HRESULT hr;

    ppOldPins = This->ppPins;

    This->ppPins = CoTaskMemAlloc((This->cStreams + 2) * sizeof(IPin *));
    memcpy(This->ppPins, ppOldPins, (This->cStreams + 1) * sizeof(IPin *));

    hr = BaseOutputPin_Construct(&Parser_OutputPin_Vtbl, sizeof(Parser_OutputPin), piOutput, &output_BaseOutputFuncTable, &This->filter.csFilter, This->ppPins + (This->cStreams + 1));

    if (SUCCEEDED(hr))
    {
        IPin *pPin = This->ppPins[This->cStreams + 1];
        Parser_OutputPin *pin = unsafe_impl_Parser_OutputPin_from_IPin(pPin);
        pin->pmt = CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
        CopyMediaType(pin->pmt, amt);
        pin->dwSamplesProcessed = 0;

        pin->pin.pin.pinInfo.pFilter = &This->filter.IBaseFilter_iface;
        pin->allocProps = *props;
        This->cStreams++;
        BaseFilterImpl_IncrementPinVersion(&This->filter);
        CoTaskMemFree(ppOldPins);
    }
    else
    {
        CoTaskMemFree(This->ppPins);
        This->ppPins = ppOldPins;
        ERR("Failed with error %x\n", hr);
    }

    return hr;
}