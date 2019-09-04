#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  hMetaFilePict; int /*<<< orphan*/  hGlobal; } ;
struct TYPE_8__ {int /*<<< orphan*/  hMF; } ;
struct TYPE_7__ {scalar_t__ tymed; int /*<<< orphan*/  hGlobal; int /*<<< orphan*/  hEnhMetaFile; } ;
typedef  TYPE_1__ const STGMEDIUM ;
typedef  TYPE_2__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ GetEnhMetaFileBits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GetMetaFileBitsEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 scalar_t__ GlobalSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TYMED_ENHMF ; 
 scalar_t__ TYMED_HGLOBAL ; 
 scalar_t__ TYMED_MFPICT ; 
 TYPE_5__* U (TYPE_1__ const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static HRESULT stgmedium_cmp(const STGMEDIUM *med1, STGMEDIUM *med2)
{
    BYTE *data1, *data2;
    ULONG datasize1, datasize2;

    if (med1->tymed != med2->tymed)
        return E_FAIL;

    if (med1->tymed == TYMED_MFPICT)
    {
        METAFILEPICT *mfpict1 = GlobalLock(U(med1)->hMetaFilePict);
        METAFILEPICT *mfpict2 = GlobalLock(U(med2)->hMetaFilePict);

        datasize1 = GetMetaFileBitsEx(mfpict1->hMF, 0, NULL);
        datasize2 = GetMetaFileBitsEx(mfpict2->hMF, 0, NULL);
        if (datasize1 == datasize2)
        {
            data1 = HeapAlloc(GetProcessHeap(), 0, datasize1);
            data2 = HeapAlloc(GetProcessHeap(), 0, datasize2);
            GetMetaFileBitsEx(mfpict1->hMF, datasize1, data1);
            GetMetaFileBitsEx(mfpict2->hMF, datasize2, data2);
        }
        else return E_FAIL;
    }
    else if (med1->tymed == TYMED_ENHMF)
    {
        datasize1 = GetEnhMetaFileBits(med1->hEnhMetaFile, 0, NULL);
        datasize2 = GetEnhMetaFileBits(med2->hEnhMetaFile, 0, NULL);
        if (datasize1 == datasize2)
        {
            data1 = HeapAlloc(GetProcessHeap(), 0, datasize1);
            data2 = HeapAlloc(GetProcessHeap(), 0, datasize2);
            GetEnhMetaFileBits(med1->hEnhMetaFile, datasize1, data1);
            GetEnhMetaFileBits(med2->hEnhMetaFile, datasize2, data2);
        }
        else return E_FAIL;
    }
    else if (med1->tymed == TYMED_HGLOBAL)
    {
        datasize1 = GlobalSize(med1->hGlobal);
        datasize2 = GlobalSize(med2->hGlobal);

        if (datasize1 == datasize2)
        {
            data1 = GlobalLock(med1->hGlobal);
            data2 = GlobalLock(med2->hGlobal);
        }
        else
            return E_FAIL;
    }
    else
        return E_NOTIMPL;

    if (memcmp(data1, data2, datasize1) != 0)
        return E_FAIL;

    if (med1->tymed == TYMED_HGLOBAL)
    {
        GlobalUnlock(U(med1)->hGlobal);
        GlobalUnlock(U(med2)->hGlobal);
    }
    else if (med1->tymed == TYMED_MFPICT)
    {
        HeapFree(GetProcessHeap(), 0, data1);
        HeapFree(GetProcessHeap(), 0, data2);
        GlobalUnlock(U(med1)->hMetaFilePict);
        GlobalUnlock(U(med2)->hMetaFilePict);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, data1);
        HeapFree(GetProcessHeap(), 0, data2);
    }

    return S_OK;
}