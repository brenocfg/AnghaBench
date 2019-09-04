#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_29__ {int HighPart; int LowPart; } ;
struct TYPE_30__ {int QuadPart; TYPE_7__ u; } ;
typedef  TYPE_8__ ULARGE_INTEGER ;
struct TYPE_28__ {int /*<<< orphan*/  dwLowDateTime; int /*<<< orphan*/  dwHighDateTime; } ;
struct TYPE_27__ {int /*<<< orphan*/  dwLowDateTime; int /*<<< orphan*/  dwHighDateTime; } ;
struct TYPE_26__ {int /*<<< orphan*/  dwLowDateTime; int /*<<< orphan*/  dwHighDateTime; } ;
struct TYPE_24__ {int LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_25__ {TYPE_2__ u; } ;
struct TYPE_31__ {int /*<<< orphan*/  grfStateBits; int /*<<< orphan*/  grfLocksSupported; int /*<<< orphan*/  grfMode; TYPE_6__ atime; TYPE_5__ ctime; TYPE_4__ mtime; TYPE_3__ cbSize; int /*<<< orphan*/  type; int /*<<< orphan*/ * pwcsName; } ;
struct TYPE_23__ {int HighPart; scalar_t__ LowPart; } ;
struct TYPE_22__ {int QuadPart; TYPE_1__ u; } ;
typedef  TYPE_9__ STATSTG ;
typedef  int /*<<< orphan*/  Memory ;
typedef  int /*<<< orphan*/  MemBuf ;
typedef  TYPE_10__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IWICStream ;
typedef  int /*<<< orphan*/  IWICImagingFactory ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  CmpMem ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CUR_POS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WICImagingFactory ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERROR_ARITHMETIC_OVERFLOW ; 
 int E_INVALIDARG ; 
 int E_NOTIMPL ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IWICImagingFactory ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int IWICImagingFactory_CreateStream (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICImagingFactory_Release (int /*<<< orphan*/ *) ; 
 int IWICStream_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IWICStream_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IWICStream_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IWICStream_InitializeFromIStreamRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__,TYPE_8__) ; 
 int IWICStream_InitializeFromMemory (int /*<<< orphan*/ *,int*,int) ; 
 int IWICStream_LockRegion (int /*<<< orphan*/ *,TYPE_8__,TYPE_8__,int /*<<< orphan*/ ) ; 
 int IWICStream_Read (int /*<<< orphan*/ *,int*,int,int*) ; 
 int /*<<< orphan*/  IWICStream_Release (int /*<<< orphan*/ *) ; 
 int IWICStream_Revert (int /*<<< orphan*/ *) ; 
 int IWICStream_Seek (int /*<<< orphan*/ *,TYPE_10__,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int IWICStream_SetSize (int /*<<< orphan*/ *,TYPE_8__) ; 
 int IWICStream_Stat (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int IWICStream_UnlockRegion (int /*<<< orphan*/ *,TYPE_8__,TYPE_8__,int /*<<< orphan*/ ) ; 
 int IWICStream_Write (int /*<<< orphan*/ *,int const*,int,int*) ; 
 int /*<<< orphan*/  STGC_CONSOLIDATE ; 
 int /*<<< orphan*/  STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE ; 
 int /*<<< orphan*/  STGC_DEFAULT ; 
 int /*<<< orphan*/  STGC_ONLYIFCURRENT ; 
 int /*<<< orphan*/  STGC_OVERWRITE ; 
 int /*<<< orphan*/  STGTY_STREAM ; 
 int STG_E_MEDIUMFULL ; 
 int /*<<< orphan*/  STREAM_SEEK_END ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int WINCODEC_ERR_VALUEOUTOFRANGE ; 
 int /*<<< orphan*/  ZeroMemory (int*,int) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*,...) ; 

__attribute__((used)) static void test_StreamOnStreamRange(void)
{
    IWICImagingFactory *pFactory;
    IWICStream *pStream, *pSubStream;
    IStream *CopyStream;
    const BYTE CmpMem[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    };
    BYTE Memory[64], MemBuf[64];
    LARGE_INTEGER LargeNull, LargeInt;
    ULARGE_INTEGER uLargeNull, uNewPos, uSize;
    ULONG uBytesRead, uBytesWritten;
    HRESULT hr;
    STATSTG Stats;

    LargeNull.QuadPart = 0;
    uLargeNull.QuadPart = 0;

    memcpy(Memory, CmpMem, sizeof(CmpMem));

    CoInitialize(NULL);

    hr = CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, &IID_IWICImagingFactory, (void**)&pFactory);
    if(FAILED(hr)) {
        skip("CoCreateInstance returned with %#x, expected %#x\n", hr, S_OK);
        return;
    }

    hr = IWICImagingFactory_CreateStream(pFactory, &pStream);
    ok(hr == S_OK, "CreateStream returned with %#x, expected %#x\n", hr, S_OK);
    if(FAILED(hr)) {
        skip("Failed to create stream\n");
        return;
    }

    hr = IWICStream_InitializeFromMemory(pStream, Memory, sizeof(Memory));
    ok(hr == S_OK, "InitializeFromMemory returned with %#x, expected %#x\n", hr, S_OK);

    hr = IWICImagingFactory_CreateStream(pFactory, &pSubStream);
    ok(hr == S_OK, "CreateStream returned with %#x, expected %#x\n", hr, S_OK);

    uNewPos.QuadPart = 20;
    uSize.QuadPart = 20;
    hr = IWICStream_InitializeFromIStreamRegion(pSubStream, (IStream*)pStream, uNewPos, uSize);
    ok(hr == S_OK, "InitializeFromIStreamRegion returned with %#x, expected %#x\n", hr, S_OK);
    if(FAILED(hr)) {
        skip("InitializeFromIStreamRegion unimplemented\n");
        IWICStream_Release(pSubStream);
        IWICStream_Release(pStream);
        IWICImagingFactory_Release(pFactory);
        CoUninitialize();
        return;
    }

    /* Seek */
    CHECK_CUR_POS(pStream, 0);
    hr = IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_END, &uNewPos);
    ok(uNewPos.u.HighPart == 0 && uNewPos.u.LowPart == 20, "Seek cursor moved to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0, 20);
    ok(hr == S_OK, "Seek returned with %#x, expected %#x\n", hr, S_OK);
    CHECK_CUR_POS(pStream, 0);

    hr = IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, &uNewPos);
    ok(hr == S_OK, "Seek returned with %#x, expected %#x\n", hr, S_OK);
    ok(uNewPos.u.HighPart == 0 && uNewPos.u.LowPart == 0, "Seek cursor moved to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0, 0);
    CHECK_CUR_POS(pStream, 0);

    hr = IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);
    ok(hr == S_OK, "Seek returned with %#x, expected %#x\n", hr, S_OK);

    LargeInt.u.HighPart = 1;
    LargeInt.u.LowPart = 0;
    uNewPos.u.HighPart = 0xdeadbeef;
    uNewPos.u.LowPart = 0xdeadbeef;
    hr = IWICStream_Seek(pSubStream, LargeInt, STREAM_SEEK_SET, &uNewPos);
    ok(hr == WINCODEC_ERR_VALUEOUTOFRANGE, "Seek returned with %#x, expected %#x\n", hr, WINCODEC_ERR_VALUEOUTOFRANGE);
    ok(uNewPos.u.HighPart == 0xdeadbeef && uNewPos.u.LowPart == 0xdeadbeef, "Seek cursor initialized to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0xdeadbeef, 0xdeadbeef);
    CHECK_CUR_POS(pStream, 0);

    LargeInt.QuadPart = 30;
    uNewPos.u.HighPart = 0xdeadbeef;
    uNewPos.u.LowPart = 0xdeadbeef;
    hr = IWICStream_Seek(pSubStream, LargeInt, STREAM_SEEK_SET, &uNewPos);
    ok(hr == WINCODEC_ERR_VALUEOUTOFRANGE, "Seek returned with %#x, expected %#x\n", hr, WINCODEC_ERR_VALUEOUTOFRANGE);
    ok(uNewPos.u.HighPart == 0xdeadbeef && uNewPos.u.LowPart == 0xdeadbeef, "Seek cursor initialized to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0xdeadbeef, 0xdeadbeef);
    CHECK_CUR_POS(pStream, 0);

    LargeInt.QuadPart = 1;
    uNewPos.u.HighPart = 0xdeadbeef;
    uNewPos.u.LowPart = 0xdeadbeef;
    hr = IWICStream_Seek(pSubStream, LargeInt, STREAM_SEEK_END, &uNewPos);
    ok(hr == WINCODEC_ERR_VALUEOUTOFRANGE, "Seek returned with %#x, expected %#x\n", hr, WINCODEC_ERR_VALUEOUTOFRANGE);
    ok(uNewPos.u.HighPart == 0xdeadbeef && uNewPos.u.LowPart == 0xdeadbeef, "Seek cursor initialized to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0xdeadbeef, 0xdeadbeef);
    CHECK_CUR_POS(pStream, 0);

    LargeInt.QuadPart = -1;
    hr = IWICStream_Seek(pSubStream, LargeInt, STREAM_SEEK_END, &uNewPos);
    ok(hr == S_OK, "Seek returned with %#x, expected %#x\n", hr, S_OK);
    ok(uNewPos.u.HighPart == 0 && uNewPos.u.LowPart == 19, "bSeek cursor moved to position (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart);
    CHECK_CUR_POS(pStream, 0);

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, &uNewPos); /* reset seek pointer */
    LargeInt.QuadPart = -25;
    uNewPos.u.HighPart = 0xdeadbeef;
    uNewPos.u.LowPart = 0xdeadbeef;
    hr = IWICStream_Seek(pSubStream, LargeInt, STREAM_SEEK_END, &uNewPos);
    ok(hr == WINCODEC_ERR_VALUEOUTOFRANGE,
       "Seek returned with %#x, expected %#x\n", hr, HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW));
    ok(uNewPos.u.HighPart == 0xdeadbeef && uNewPos.u.LowPart == 0xdeadbeef, "Seek cursor initialized to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0xdeadbeef, 0xdeadbeef);
    CHECK_CUR_POS(pStream, 0);
    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);


    /* Read */
    hr = IWICStream_Read(pSubStream, MemBuf, 12, &uBytesRead);
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ok(uBytesRead == 12, "Read %u bytes, expected %u\n", uBytesRead, 12);
        ok(memcmp(MemBuf, CmpMem+20, 12) == 0, "Read returned invalid data!\n");

        /* check whether the seek pointer has moved correctly */
        CHECK_CUR_POS(pSubStream, uBytesRead);
        CHECK_CUR_POS(pStream, 0);
    }

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);

    hr = IWICStream_Read(pSubStream, Memory, 10, &uBytesRead);   /* source = dest */
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ok(uBytesRead == 10, "Read %u bytes, expected %u\n", uBytesRead, 10);
        ok(memcmp(Memory, CmpMem+20, uBytesRead) == 0, "Read returned invalid data!\n");
    }
    CHECK_CUR_POS(pStream, 0);

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);

    hr = IWICStream_Read(pSubStream, Memory, 30, &uBytesRead);   /* request too many bytes */
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ok(uBytesRead == 20, "Read %u bytes\n", uBytesRead);
        ok(memcmp(Memory, CmpMem+20, uBytesRead) == 0, "Read returned invalid data!\n");
    }
    CHECK_CUR_POS(pStream, 0);

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);
    uBytesRead = 0xdeadbeef;
    hr = IWICStream_Read(pSubStream, NULL, 1, &uBytesRead);    /* destination buffer = NULL */
    ok(hr == E_INVALIDARG, "Read returned with %#x, expected %#x\n", hr, E_INVALIDARG);
    ok(uBytesRead == 0xdeadbeef, "Expected uBytesRead to be unchanged, got %u\n", uBytesRead);

    hr = IWICStream_Read(pSubStream, MemBuf, 0, &uBytesRead);    /* read 0 bytes */
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);

    uBytesRead = 0xdeadbeef;
    hr = IWICStream_Read(pSubStream, NULL, 0, &uBytesRead);
    ok(hr == E_INVALIDARG, "Read returned with %#x, expected %#x\n", hr, E_INVALIDARG);
    ok(uBytesRead == 0xdeadbeef, "Expected uBytesRead to be unchanged, got %u\n", uBytesRead);

    hr = IWICStream_Read(pSubStream, NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "Read returned with %#x, expected %#x\n", hr, E_INVALIDARG);

    hr = IWICStream_Read(pSubStream, MemBuf, 1, NULL);
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);
    ZeroMemory(MemBuf, sizeof(MemBuf));
    hr = IWICStream_Read(pSubStream, MemBuf, 30, &uBytesRead);
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ok(uBytesRead == 20, "Read %u bytes\n", uBytesRead);
        ok(memcmp(Memory, CmpMem+20, 20) == 0, "Read returned invalid data!\n");
    }
    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);


    /* Write */
    MemBuf[0] = CmpMem[0] + 1;
    MemBuf[1] = CmpMem[1] + 1;
    MemBuf[2] = CmpMem[2] + 1;
    hr = IWICStream_Write(pSubStream, MemBuf, 3, &uBytesWritten);
    ok(hr == S_OK, "Write returned with %#x, expected %#x\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ok(uBytesWritten == 3, "Wrote %u bytes, expected %u\n", uBytesWritten, 3);
        ok(memcmp(MemBuf, Memory+20, 3) == 0, "Wrote returned invalid data!\n"); /* make sure we're writing directly */

        /* check whether the seek pointer has moved correctly */
        CHECK_CUR_POS(pSubStream, uBytesWritten);
        CHECK_CUR_POS(pStream, 0);
    }
    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);

    hr = IWICStream_Write(pSubStream, MemBuf, 0, &uBytesWritten);
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);

    uBytesWritten = 0xdeadbeef;
    hr = IWICStream_Write(pSubStream, NULL, 3, &uBytesWritten);
    ok(hr == E_INVALIDARG, "Write returned with %#x, expected %#x\n", hr, E_INVALIDARG);
    ok(uBytesWritten == 0xdeadbeef, "Expected uBytesWritten to be unchanged, got %u\n", uBytesWritten);
    CHECK_CUR_POS(pSubStream, 0);
    CHECK_CUR_POS(pStream, 0);

    uBytesWritten = 0xdeadbeef;
    hr = IWICStream_Write(pSubStream, NULL, 0, &uBytesWritten);
    ok(hr == E_INVALIDARG, "Write returned with %#x, expected %#x\n", hr, E_INVALIDARG);
    ok(uBytesWritten == 0xdeadbeef, "Expected uBytesWritten to be unchanged, got %u\n", uBytesWritten);
    CHECK_CUR_POS(pSubStream, 0);
    CHECK_CUR_POS(pStream, 0);

    hr = IWICStream_Write(pSubStream, CmpMem, 30, &uBytesWritten);
    ok(hr == S_OK, "Write returned with %#x, expected %#x\n", hr, STG_E_MEDIUMFULL);
    ok(uBytesWritten == 20, "Wrote %u bytes, expected %u\n", uBytesWritten, 0);
    CHECK_CUR_POS(pSubStream, uBytesWritten);
    CHECK_CUR_POS(pStream, 0);
    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);


    /* SetSize */
    uNewPos.u.HighPart = 0;
    uNewPos.u.LowPart = sizeof(Memory) + 10;
    hr = IWICStream_SetSize(pSubStream, uNewPos);
    ok(hr == E_NOTIMPL, "SetSize returned %#x, expected %#x\n", hr, E_NOTIMPL);

    uNewPos.u.HighPart = 0;
    uNewPos.u.LowPart = sizeof(Memory);
    hr = IWICStream_SetSize(pSubStream, uNewPos);
    ok(hr == E_NOTIMPL, "SetSize returned %#x, expected %#x\n", hr, E_NOTIMPL);

    uNewPos.u.HighPart = 0;
    uNewPos.u.LowPart = sizeof(Memory) - 10;
    hr = IWICStream_SetSize(pSubStream, uNewPos);
    ok(hr == E_NOTIMPL, "SetSize returned %#x, expected %#x\n", hr, E_NOTIMPL);

    uNewPos.u.HighPart = 0;
    uNewPos.u.LowPart = 0;
    hr = IWICStream_SetSize(pSubStream, uNewPos);
    ok(hr == E_NOTIMPL, "SetSize returned %#x, expected %#x\n", hr, E_NOTIMPL);

    uNewPos.QuadPart = -10;
    hr = IWICStream_SetSize(pSubStream, uNewPos);
    ok(hr == E_NOTIMPL, "SetSize returned %#x, expected %#x\n", hr, E_NOTIMPL);


    /* CopyTo */
    uNewPos.u.HighPart = 0;
    uNewPos.u.LowPart = 30;
    hr = IWICStream_CopyTo(pSubStream, NULL, uNewPos, NULL, NULL);
    ok(hr == E_NOTIMPL, "CopyTo returned %#x, expected %#x\n", hr, E_NOTIMPL);

    hr = CreateStreamOnHGlobal(NULL, TRUE, &CopyStream);
    ok(hr == S_OK, "CreateStream failed with %#x\n", hr);

    hr = IWICStream_CopyTo(pSubStream, CopyStream, uNewPos, NULL, NULL);
    ok(hr == E_NOTIMPL, "CopyTo returned %#x, expected %#x\n", hr, E_NOTIMPL);
    IStream_Release(CopyStream);


    /* Commit */
    hr = IWICStream_Commit(pSubStream, STGC_DEFAULT);
    ok(hr == E_NOTIMPL, "Commit returned %#x, expected %#x\n", hr, E_NOTIMPL);

    hr = IWICStream_Commit(pSubStream, STGC_OVERWRITE);
    ok(hr == E_NOTIMPL, "Commit returned %#x, expected %#x\n", hr, E_NOTIMPL);

    hr = IWICStream_Commit(pSubStream, STGC_ONLYIFCURRENT);
    ok(hr == E_NOTIMPL, "Commit returned %#x, expected %#x\n", hr, E_NOTIMPL);

    hr = IWICStream_Commit(pSubStream, STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE);
    ok(hr == E_NOTIMPL, "Commit returned %#x, expected %#x\n", hr, E_NOTIMPL);

    hr = IWICStream_Commit(pSubStream, STGC_CONSOLIDATE);
    ok(hr == E_NOTIMPL, "Commit returned %#x, expected %#x\n", hr, E_NOTIMPL);


    /* Revert */
    IWICStream_Write(pSubStream, &MemBuf[5], 6, NULL);
    hr = IWICStream_Revert(pSubStream);
    ok(hr == E_NOTIMPL, "Revert returned %#x, expected %#x\n", hr, E_NOTIMPL);
    memcpy(Memory, CmpMem, sizeof(Memory));


    /* LockRegion/UnlockRegion */
    hr = IWICStream_LockRegion(pSubStream, uLargeNull, uLargeNull, 0);
    ok(hr == E_NOTIMPL, "LockRegion returned %#x, expected %#x\n", hr, E_NOTIMPL);

    hr = IWICStream_UnlockRegion(pSubStream, uLargeNull, uLargeNull, 0);
    ok(hr == E_NOTIMPL, "UnlockRegion returned %#x, expected %#x\n", hr, E_NOTIMPL);


    /* Stat */
    hr = IWICStream_Stat(pSubStream, NULL, 0);
    ok(hr == E_INVALIDARG, "Stat returned %#x, expected %#x\n", hr, E_INVALIDARG);

    hr = IWICStream_Stat(pSubStream, &Stats, 0);
    ok(hr == S_OK, "Stat returned %#x, expected %#x\n", hr, S_OK);
    ok(Stats.pwcsName == NULL, "Stat returned name %p, expected %p\n", Stats.pwcsName, NULL);
    ok(Stats.type == STGTY_STREAM, "Stat returned type %d, expected %d\n", Stats.type, STGTY_STREAM);
    ok(Stats.cbSize.u.HighPart == 0 && Stats.cbSize.u.LowPart == 20, "Stat returned size (%u;%u)\n", Stats.cbSize.u.HighPart, Stats.cbSize.u.LowPart);
    ok(Stats.mtime.dwHighDateTime == 0 && Stats.mtime.dwLowDateTime == 0, "Stat returned mtime (%u;%u), expected (%u;%u)\n", Stats.mtime.dwHighDateTime, Stats.mtime.dwLowDateTime, 0, 0);
    ok(Stats.ctime.dwHighDateTime == 0 && Stats.ctime.dwLowDateTime == 0, "Stat returned ctime (%u;%u), expected (%u;%u)\n", Stats.ctime.dwHighDateTime, Stats.ctime.dwLowDateTime, 0, 0);
    ok(Stats.atime.dwHighDateTime == 0 && Stats.atime.dwLowDateTime == 0, "Stat returned atime (%u;%u), expected (%u;%u)\n", Stats.atime.dwHighDateTime, Stats.atime.dwLowDateTime, 0, 0);
    ok(Stats.grfMode == 0, "Stat returned access mode %d, expected %d\n", Stats.grfMode, 0);
    ok(Stats.grfLocksSupported == 0, "Stat returned supported locks %#x, expected %#x\n", Stats.grfLocksSupported, 0);
    ok(Stats.grfStateBits == 0, "Stat returned state bits %#x, expected %#x\n", Stats.grfStateBits, 0);


    /* Clone */
    hr = IWICStream_Clone(pSubStream, &CopyStream);
    ok(hr == E_NOTIMPL, "Clone returned %#x, expected %#x\n", hr, E_NOTIMPL);


    IWICStream_Release(pSubStream);


    /* Recreate, this time larger than the original. */
    hr = IWICImagingFactory_CreateStream(pFactory, &pSubStream);
    ok(hr == S_OK, "CreateStream returned with %#x, expected %#x\n", hr, S_OK);

    uNewPos.QuadPart = 48;
    uSize.QuadPart = 32;
    hr = IWICStream_InitializeFromIStreamRegion(pSubStream, (IStream*)pStream, uNewPos, uSize);
    ok(hr == S_OK, "InitializeFromMemory returned with %#x, expected %#x\n", hr, S_OK);

    hr = IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_END, &uNewPos);
    ok(hr == S_OK, "Seek returned with %#x, expected %#x\n", hr, S_OK);
    ok(uNewPos.u.HighPart == 0 && uNewPos.u.LowPart == 16, "Seek cursor moved to position (%u;%u), expected (%u;%u)\n", uNewPos.u.HighPart, uNewPos.u.LowPart, 0, 16);

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);
    hr = IWICStream_Read(pSubStream, Memory, 48, &uBytesRead);
    ok(hr == S_OK, "Read returned with %#x, expected %#x\n", hr, S_OK);
    if(SUCCEEDED(hr)) {
        ok(uBytesRead == 16, "Read %u bytes\n", uBytesRead);
        ok(memcmp(Memory, CmpMem+48, uBytesRead) == 0, "Read returned invalid data!\n");
    }

    IWICStream_Seek(pSubStream, LargeNull, STREAM_SEEK_SET, NULL);
    uBytesWritten = 0xdeadbeef;
    hr = IWICStream_Write(pSubStream, CmpMem, 32, &uBytesWritten);
    ok(hr == STG_E_MEDIUMFULL, "Write returned with %#x, expected %#x\n", hr, STG_E_MEDIUMFULL);
    ok(uBytesWritten == 0xdeadbeef, "Expected uBytesWritten to be unchanged, got %u\n", uBytesWritten);
    CHECK_CUR_POS(pSubStream, 0);
    CHECK_CUR_POS(pStream, 0);

    IWICStream_Release(pSubStream);
    IWICStream_Release(pStream);
    IWICImagingFactory_Release(pFactory);
    CoUninitialize();
}