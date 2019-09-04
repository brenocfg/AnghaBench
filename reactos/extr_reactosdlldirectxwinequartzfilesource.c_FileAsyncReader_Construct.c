#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* DebugInfo; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_5__ csList; scalar_t__ queued_number; int /*<<< orphan*/ * handle_list; int /*<<< orphan*/ * sample_list; int /*<<< orphan*/  bFlushing; int /*<<< orphan*/  hFile; TYPE_1__ IAsyncReader_iface; } ;
struct TYPE_9__ {int /*<<< orphan*/  achName; int /*<<< orphan*/ * pFilter; int /*<<< orphan*/  dir; } ;
struct TYPE_8__ {scalar_t__* Spare; } ;
typedef  TYPE_3__ PIN_INFO ;
typedef  int /*<<< orphan*/  LPCRITICAL_SECTION ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_4__ FileAsyncReader ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BaseOutputPin_Construct (int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileAsyncReaderPin_Vtbl ; 
 int /*<<< orphan*/  FileAsyncReader_Vtbl ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  PINDIR_OUTPUT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_BaseOutputFuncTable ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wszOutputPinName ; 

__attribute__((used)) static HRESULT FileAsyncReader_Construct(HANDLE hFile, IBaseFilter * pBaseFilter, LPCRITICAL_SECTION pCritSec, IPin ** ppPin)
{
    PIN_INFO piOutput;
    HRESULT hr;

    *ppPin = NULL;
    piOutput.dir = PINDIR_OUTPUT;
    piOutput.pFilter = pBaseFilter;
    strcpyW(piOutput.achName, wszOutputPinName);
    hr = BaseOutputPin_Construct(&FileAsyncReaderPin_Vtbl, sizeof(FileAsyncReader), &piOutput, &output_BaseOutputFuncTable, pCritSec, ppPin);

    if (SUCCEEDED(hr))
    {
        FileAsyncReader *pPinImpl =  (FileAsyncReader *)*ppPin;
        pPinImpl->IAsyncReader_iface.lpVtbl = &FileAsyncReader_Vtbl;
        pPinImpl->hFile = hFile;
        pPinImpl->bFlushing = FALSE;
        pPinImpl->sample_list = NULL;
        pPinImpl->handle_list = NULL;
        pPinImpl->queued_number = 0;
        InitializeCriticalSection(&pPinImpl->csList);
        pPinImpl->csList.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": FileAsyncReader.csList");
    }
    return hr;
}