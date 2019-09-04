#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ llStop; } ;
struct TYPE_10__ {unsigned int cStreams; int /*<<< orphan*/ * ppPins; TYPE_2__ sourceSeeking; TYPE_1__* pInputPin; } ;
struct TYPE_11__ {scalar_t__ position; scalar_t__ EndOfFile; TYPE_3__ Parser; int /*<<< orphan*/  header; } ;
struct TYPE_8__ {void* rtCurrent; } ;
typedef  void* REFERENCE_TIME ;
typedef  TYPE_4__ MPEGSplitterImpl ;
typedef  TYPE_4__* LPVOID ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ BYTES_FROM_MEDIATIME (void*) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ FillBuffer (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSample_GetActualDataLength (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSample_GetPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IMediaSample_GetTime (int /*<<< orphan*/ *,void**,void**) ; 
 scalar_t__ IPin_ConnectedTo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IPin_EndOfStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ VFW_E_WRONG_STATE ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT MPEGSplitter_process_sample(LPVOID iface, IMediaSample * pSample, DWORD_PTR cookie)
{
    MPEGSplitterImpl *This = iface;
    BYTE *pbSrcStream;
    DWORD cbSrcStream = 0;
    REFERENCE_TIME tStart, tStop, tAviStart = This->position;
    HRESULT hr;

    hr = IMediaSample_GetTime(pSample, &tStart, &tStop);
    if (SUCCEEDED(hr))
    {
        cbSrcStream = IMediaSample_GetActualDataLength(pSample);
        hr = IMediaSample_GetPointer(pSample, &pbSrcStream);
    }

    /* Flush occurring */
    if (cbSrcStream == 0)
    {
        FIXME(".. Why do I need you?\n");
        return S_OK;
    }

    /* trace removed for performance reasons */
    /* TRACE("(%p), %llu -> %llu\n", pSample, tStart, tStop); */

    /* Now, try to find a new header */
    hr = FillBuffer(This, pSample);
    if (hr != S_OK)
    {
        WARN("Failed with hres: %08x!\n", hr);

        /* Unset progression if denied! */
        if (hr == VFW_E_WRONG_STATE || hr == S_FALSE)
        {
            memcpy(This->header, pbSrcStream, 4);
            This->Parser.pInputPin->rtCurrent = tStart;
            This->position = tAviStart;
        }
    }

    if (BYTES_FROM_MEDIATIME(tStop) >= This->EndOfFile || This->position >= This->Parser.sourceSeeking.llStop)
    {
        unsigned int i;

        TRACE("End of file reached\n");

        for (i = 0; i < This->Parser.cStreams; i++)
        {
            IPin* ppin;

            hr = IPin_ConnectedTo(This->Parser.ppPins[i+1], &ppin);
            if (SUCCEEDED(hr))
            {
                hr = IPin_EndOfStream(ppin);
                IPin_Release(ppin);
            }
            if (FAILED(hr))
                WARN("Error sending EndOfStream to pin %u (%x)\n", i, hr);
        }

        /* Force the pullpin thread to stop */
        hr = S_FALSE;
    }

    return hr;
}