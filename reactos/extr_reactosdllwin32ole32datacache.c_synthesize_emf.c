#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  hMF; } ;
struct TYPE_7__ {int /*<<< orphan*/  hEnhMetaFile; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  TYPE_3__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HMETAFILEPICT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GetMetaFileBitsEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetWinMetaFileBits (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  TYMED_ENHMF ; 

__attribute__((used)) static HRESULT synthesize_emf( HMETAFILEPICT data, STGMEDIUM *med )
{
    METAFILEPICT *pict;
    HRESULT hr = E_FAIL;
    UINT size;
    void *bits;

    if (!(pict = GlobalLock( data ))) return hr;

    size = GetMetaFileBitsEx( pict->hMF, 0, NULL );
    if ((bits = HeapAlloc( GetProcessHeap(), 0, size )))
    {
        GetMetaFileBitsEx( pict->hMF, size, bits );
        med->u.hEnhMetaFile = SetWinMetaFileBits( size, bits, NULL, pict );
        HeapFree( GetProcessHeap(), 0, bits );
        med->tymed = TYMED_ENHMF;
        med->pUnkForRelease = NULL;
        hr = S_OK;
    }

    GlobalUnlock( data );
    return hr;
}