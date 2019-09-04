#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  fmtOffset ;
typedef  int ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_1__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  stm; } ;
typedef  TYPE_2__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  PROPERTYSETHEADER ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FORMATIDOFFSET ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  PropertyStorage_MakeFmtIdOffset (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PropertyStorage_MakeHeader (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STG_E_WRITEFAULT ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT PropertyStorage_WriteHeadersToStream(PropertyStorage_impl *This)
{
    HRESULT hr;
    ULONG count = 0;
    LARGE_INTEGER seek = { {0} };
    PROPERTYSETHEADER hdr;
    FORMATIDOFFSET fmtOffset;

    hr = IStream_Seek(This->stm, seek, STREAM_SEEK_SET, NULL);
    if (FAILED(hr))
        goto end;
    PropertyStorage_MakeHeader(This, &hdr);
    hr = IStream_Write(This->stm, &hdr, sizeof(hdr), &count);
    if (FAILED(hr))
        goto end;
    if (count != sizeof(hdr))
    {
        hr = STG_E_WRITEFAULT;
        goto end;
    }

    PropertyStorage_MakeFmtIdOffset(This, &fmtOffset);
    hr = IStream_Write(This->stm, &fmtOffset, sizeof(fmtOffset), &count);
    if (FAILED(hr))
        goto end;
    if (count != sizeof(fmtOffset))
    {
        hr = STG_E_WRITEFAULT;
        goto end;
    }
    hr = S_OK;

end:
    return hr;
}