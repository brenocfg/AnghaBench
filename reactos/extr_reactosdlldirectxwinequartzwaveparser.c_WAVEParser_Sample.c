#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ llStop; } ;
struct TYPE_11__ {unsigned int cStreams; int /*<<< orphan*/ * ppPins; TYPE_1__ sourceSeeking; TYPE_4__* pInputPin; } ;
struct TYPE_12__ {scalar_t__ EndOfFile; TYPE_2__ Parser; } ;
typedef  TYPE_3__ WAVEParserImpl ;
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  dwSamplesProcessed; } ;
struct TYPE_13__ {scalar_t__ rtNext; scalar_t__ rtStop; scalar_t__ rtCurrent; int /*<<< orphan*/  pReader; int /*<<< orphan*/  cbAlign; int /*<<< orphan*/  pAlloc; } ;
typedef  scalar_t__ REFERENCE_TIME ;
typedef  TYPE_4__ PullPin ;
typedef  TYPE_5__ Parser_OutputPin ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONGLONG ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 scalar_t__ ALIGNUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BYTES_FROM_MEDIATIME (scalar_t__) ; 
 scalar_t__ BaseOutputPinImpl_Deliver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IAsyncReader_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IMediaSample_GetActualDataLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_GetPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IMediaSample_GetSize (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSample_GetTime (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  IMediaSample_SetDiscontinuity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMediaSample_SetPreroll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMediaSample_SetSyncPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMediaSample_SetTime (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ IMemAllocator_GetBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IPin_ConnectedTo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IPin_EndOfStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MEDIATIME_FROM_BYTES (scalar_t__) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VFW_E_NOT_CONNECTED ; 
 scalar_t__ VFW_E_WRONG_STATE ; 
 scalar_t__ bytepos_to_duration (TYPE_3__*,scalar_t__) ; 
 TYPE_5__* unsafe_impl_Parser_OutputPin_from_IPin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT WAVEParser_Sample(LPVOID iface, IMediaSample * pSample, DWORD_PTR cookie)
{
    WAVEParserImpl *This = iface;
    LPBYTE pbSrcStream = NULL;
    ULONG cbSrcStream = 0;
    REFERENCE_TIME tStart, tStop;
    HRESULT hr;
    IMediaSample *newsample = NULL;
    Parser_OutputPin *pOutputPin;
    PullPin *pin = This->Parser.pInputPin;

    IMediaSample_GetPointer(pSample, &pbSrcStream);
    hr = IMediaSample_GetTime(pSample, &tStart, &tStop);

    cbSrcStream = IMediaSample_GetActualDataLength(pSample);

    /* Flush occurring */
    if (cbSrcStream == 0)
    {
        TRACE(".. Why do I need you?\n");
        return S_OK;
    }

    pOutputPin = unsafe_impl_Parser_OutputPin_from_IPin(This->Parser.ppPins[1]);

    if (SUCCEEDED(hr))
        hr = IMemAllocator_GetBuffer(pin->pAlloc, &newsample, NULL, NULL, 0);

    if (SUCCEEDED(hr))
    {
        LONGLONG rtSampleStart = pin->rtNext;
        /* Add 4 for the next header, which should hopefully work */
        LONGLONG rtSampleStop = rtSampleStart + MEDIATIME_FROM_BYTES(IMediaSample_GetSize(newsample));

        if (rtSampleStop > pin->rtStop)
            rtSampleStop = MEDIATIME_FROM_BYTES(ALIGNUP(BYTES_FROM_MEDIATIME(pin->rtStop), pin->cbAlign));

        IMediaSample_SetTime(newsample, &rtSampleStart, &rtSampleStop);

        pin->rtCurrent = pin->rtNext;
        pin->rtNext = rtSampleStop;

        IMediaSample_SetPreroll(newsample, FALSE);
        IMediaSample_SetDiscontinuity(newsample, FALSE);
        IMediaSample_SetSyncPoint(newsample, TRUE);

        hr = IAsyncReader_Request(pin->pReader, newsample, 0);
    }

    if (SUCCEEDED(hr))
    {
        REFERENCE_TIME tAviStart, tAviStop;

        IMediaSample_SetSyncPoint(pSample, TRUE);
        pOutputPin->dwSamplesProcessed++;

        tAviStart = bytepos_to_duration(This, tStart);
        tAviStop = bytepos_to_duration(This, tStart + MEDIATIME_FROM_BYTES(IMediaSample_GetActualDataLength(pSample)));

        IMediaSample_SetTime(pSample, &tAviStart, &tAviStop);

        hr = BaseOutputPinImpl_Deliver(&pOutputPin->pin, pSample);
        if (hr != S_OK && hr != S_FALSE && hr != VFW_E_WRONG_STATE)
            ERR("Error sending sample (%x)\n", hr);
        else if (hr != S_OK)
            /* Unset progression if denied! */
            This->Parser.pInputPin->rtCurrent = tStart;
    }

    if (tStop >= This->EndOfFile || (bytepos_to_duration(This, tStop) >= This->Parser.sourceSeeking.llStop) || hr == VFW_E_NOT_CONNECTED)
    {
        unsigned int i;

        TRACE("End of file reached\n");

        for (i = 0; i < This->Parser.cStreams; i++)
        {
            IPin* ppin;
            HRESULT hr;

            TRACE("Send End Of Stream to output pin %u\n", i);

            hr = IPin_ConnectedTo(This->Parser.ppPins[i+1], &ppin);
            if (SUCCEEDED(hr))
            {
                hr = IPin_EndOfStream(ppin);
                IPin_Release(ppin);
            }
            if (FAILED(hr))
            {
                ERR("%x\n", hr);
                break;
            }
        }

        /* Force the pullpin thread to stop */
        hr = S_FALSE;
    }

    return hr;
}