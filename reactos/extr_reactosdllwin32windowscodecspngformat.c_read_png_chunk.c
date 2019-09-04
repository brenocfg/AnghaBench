#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int read_ulong_be (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT read_png_chunk(IStream *stream, BYTE *type, BYTE **data, ULONG *data_size)
{
    BYTE header[8];
    HRESULT hr;
    ULONG bytesread;

    hr = IStream_Read(stream, header, 8, &bytesread);
    if (FAILED(hr) || bytesread < 8)
    {
        if (SUCCEEDED(hr))
            hr = E_FAIL;
        return hr;
    }

    *data_size = read_ulong_be(&header[0]);

    memcpy(type, &header[4], 4);

    if (data)
    {
        *data = HeapAlloc(GetProcessHeap(), 0, *data_size);
        if (!*data)
            return E_OUTOFMEMORY;

        hr = IStream_Read(stream, *data, *data_size, &bytesread);

        if (FAILED(hr) || bytesread < *data_size)
        {
            if (SUCCEEDED(hr))
                hr = E_FAIL;
            HeapFree(GetProcessHeap(), 0, *data);
            *data = NULL;
            return hr;
        }

        /* Windows ignores CRC of the chunk */
    }

    return S_OK;
}