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
struct TYPE_3__ {scalar_t__ version; int flags; } ;
typedef  TYPE_1__ ole_stream_header_t ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DefaultHandler ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DV_E_CLIPFORMAT ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleStream ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STORAGE_CreateOleStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ ole_stream_version ; 

__attribute__((used)) static HRESULT load_ole_stream(DefaultHandler *This, IStorage *storage)
{
    IStream *stream;
    HRESULT hr;

    hr = IStorage_OpenStream(storage, OleStream, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &stream);

    if(SUCCEEDED(hr))
    {
        DWORD read;
        ole_stream_header_t header;

        hr = IStream_Read(stream, &header, sizeof(header), &read);
        if(hr == S_OK && read == sizeof(header) && header.version == ole_stream_version)
        {
            if(header.flags & 1)
            {
                /* FIXME: Read the moniker and deal with the link */
                FIXME("Linked objects are not supported yet\n");
            }
        }
        else
        {
            WARN("Incorrect OleStream header\n");
            hr = DV_E_CLIPFORMAT;
        }
        IStream_Release(stream);
    }
    else
        hr = STORAGE_CreateOleStream(storage, 0);

    return hr;
}