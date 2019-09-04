#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_14__ {int /*<<< orphan*/  hEnhMetaFile; int /*<<< orphan*/  hMetaFilePict; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; TYPE_3__ u; } ;
struct TYPE_17__ {scalar_t__ load_stream_num; TYPE_4__ stgmedium; } ;
struct TYPE_12__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_13__ {TYPE_1__ u; } ;
struct TYPE_16__ {TYPE_2__ cbSize; } ;
typedef  TYPE_4__ STGMEDIUM ;
typedef  TYPE_5__ STATSTG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  ENHMETAHEADER ;
typedef  TYPE_6__ DataCacheEntry ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IStream_Stat (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_4__*) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 scalar_t__ STREAM_NUMBER_CONTENTS ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetEnhMetaFileBits (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYMED_ENHMF ; 
 int /*<<< orphan*/  load_mf_pict (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synthesize_emf (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static HRESULT load_emf( DataCacheEntry *cache_entry, IStream *stm )
{
    HRESULT hr;

    if (cache_entry->load_stream_num != STREAM_NUMBER_CONTENTS)
    {
        STGMEDIUM stgmed;

        hr = load_mf_pict( cache_entry, stm );
        if (SUCCEEDED( hr ))
        {
            hr = synthesize_emf( cache_entry->stgmedium.u.hMetaFilePict, &stgmed );
            ReleaseStgMedium( &cache_entry->stgmedium );
        }
        if (SUCCEEDED( hr ))
            cache_entry->stgmedium = stgmed;
    }
    else
    {
        STATSTG stat;
        BYTE *data;
        ULONG read, size_bits;

        hr = IStream_Stat( stm, &stat, STATFLAG_NONAME );

        if (SUCCEEDED( hr ))
        {
            data = HeapAlloc( GetProcessHeap(), 0, stat.cbSize.u.LowPart );
            if (!data) return E_OUTOFMEMORY;

            hr = IStream_Read( stm, data, stat.cbSize.u.LowPart, &read );
            if (hr != S_OK)
            {
                HeapFree( GetProcessHeap(), 0, data );
                return hr;
            }

            if (read <= sizeof(DWORD) + sizeof(ENHMETAHEADER))
            {
                HeapFree( GetProcessHeap(), 0, data );
                return E_FAIL;
            }
            size_bits = read - sizeof(DWORD) - sizeof(ENHMETAHEADER);
            cache_entry->stgmedium.u.hEnhMetaFile = SetEnhMetaFileBits( size_bits, data + (read - size_bits) );
            cache_entry->stgmedium.tymed = TYMED_ENHMF;
            cache_entry->stgmedium.pUnkForRelease = NULL;

            HeapFree( GetProcessHeap(), 0, data );
        }
    }

    return hr;
}