#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int ULONG ;
struct TYPE_13__ {int HighPart; int LowPart; } ;
struct TYPE_14__ {int QuadPart; TYPE_2__ u; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_12__ {int HighPart; int LowPart; } ;
struct TYPE_16__ {TYPE_1__ u; scalar_t__ QuadPart; } ;
struct TYPE_15__ {int type; } ;
typedef  TYPE_4__ STATSTG ;
typedef  TYPE_5__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int E_OUTOFMEMORY ; 
 int IStream_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IStream_LockRegion (int /*<<< orphan*/ *,TYPE_3__,TYPE_3__,int /*<<< orphan*/ ) ; 
 int IStream_Read (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int IStream_Revert (int /*<<< orphan*/ *) ; 
 int IStream_Seek (int /*<<< orphan*/ *,TYPE_5__,scalar_t__,TYPE_3__*) ; 
 int IStream_SetSize (int /*<<< orphan*/ *,TYPE_3__) ; 
 int IStream_Stat (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int IStream_Write (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCK_WRITE ; 
 int /*<<< orphan*/  STATFLAG_DEFAULT ; 
 int /*<<< orphan*/  STGC_DEFAULT ; 
 int STGTY_STREAM ; 
 int STG_E_INVALIDFUNCTION ; 
 int STG_E_SEEKERROR ; 
 scalar_t__ STREAM_SEEK_CUR ; 
 scalar_t__ STREAM_SEEK_END ; 
 scalar_t__ STREAM_SEEK_SET ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int,char*) ; 

__attribute__((used)) static void test_streamonhglobal(void)
{
    const char data[] = "Test String";
    ULARGE_INTEGER ull;
    IStream *pStream;
    LARGE_INTEGER ll;
    char buffer[128];
    ULONG read;
    STATSTG statstg;
    HRESULT hr;

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    ok(hr == S_OK, "Failed to create a stream, hr %#x.\n", hr);

    ull.QuadPart = sizeof(data);
    hr = IStream_SetSize(pStream, ull);
    ok_ole_success(hr, "IStream_SetSize");

    hr = IStream_Write(pStream, data, sizeof(data), NULL);
    ok_ole_success(hr, "IStream_Write");

    ll.QuadPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");

    /* should return S_OK, not S_FALSE */
    hr = IStream_Read(pStream, buffer, sizeof(buffer), &read);
    ok_ole_success(hr, "IStream_Read");
    ok(read == sizeof(data), "IStream_Read returned read %d\n", read);

    /* ignores HighPart */
    ull.u.HighPart = -1;
    ull.u.LowPart = 0;
    hr = IStream_SetSize(pStream, ull);
    ok_ole_success(hr, "IStream_SetSize");

    /* IStream_Seek -- NULL position argument */
    ll.u.HighPart = 0;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, NULL);
    ok_ole_success(hr, "IStream_Seek");

    /* IStream_Seek -- valid position argument (seek from current position) */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == sizeof(data), "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- invalid seek argument */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 123;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_END+1, &ull);
    ok(hr == STG_E_SEEKERROR, "IStream_Seek should have returned STG_E_SEEKERROR instead of 0x%08x\n", hr);
    ok(ull.u.LowPart == sizeof(data), "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should not have changed HighPart, got %d\n", ull.u.HighPart);

    /* IStream_Seek -- valid position argument (seek to beginning) */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0, "should have set LowPart to 0 instead of %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- valid position argument (seek to end) */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_END, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0, "should have set LowPart to 0 instead of %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- ignore HighPart in the move value (seek from current position) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = -1;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == sizeof(data), "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- ignore HighPart in the move value (seek to beginning) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = -1;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0, "should have set LowPart to 0 instead of %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- invalid LowPart value (seek before start of stream) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0x80000000;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok(hr == STG_E_SEEKERROR, "IStream_Seek should have returned STG_E_SEEKERROR instead of 0x%08x\n", hr);
    ok(ull.u.LowPart == sizeof(data), "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- valid LowPart value (seek to start of stream) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = -(DWORD)sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0, "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- invalid LowPart value (seek to start of stream-1) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = -(DWORD)sizeof(data)-1;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok(hr == STG_E_SEEKERROR, "IStream_Seek should have returned STG_E_SEEKERROR instead of 0x%08x\n", hr);
    ok(ull.u.LowPart == sizeof(data), "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- valid LowPart value (seek forward to 0x80000000) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0x80000000 - sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0x80000000, "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- invalid LowPart value (seek to beginning) */
    ll.u.HighPart = 0;
    ll.u.LowPart = sizeof(data);
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0x80000000;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok(hr == STG_E_SEEKERROR, "IStream_Seek should have returned STG_E_SEEKERROR instead of 0x%08x\n", hr);
    ok(ull.u.LowPart == sizeof(data), "LowPart set to %d\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- valid LowPart value (seek to beginning) */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0x7FFFFFFF;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0x7FFFFFFF, "should have set LowPart to 0x7FFFFFFF instead of %08x\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- valid LowPart value (seek from current position) */
    ll.u.HighPart = 0;
    ll.u.LowPart = 0;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_SET, &ull);
    ok_ole_success(hr, "IStream_Seek");

    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0x7FFFFFFF;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0x7FFFFFFF, "should have set LowPart to 0x7FFFFFFF instead of %08x\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- second seek allows you to go past 0x7FFFFFFF size */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 9;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok_ole_success(hr, "IStream_Seek");
    ok(ull.u.LowPart == 0x80000008, "should have set LowPart to 0x80000008 instead of %08x\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    /* IStream_Seek -- seek wraps position/size on integer overflow, but not on win8 */
    ull.u.HighPart = 0xCAFECAFE;
    ull.u.LowPart = 0xCAFECAFE;
    ll.u.HighPart = 0;
    ll.u.LowPart = 0x7FFFFFFF;
    hr = IStream_Seek(pStream, ll, STREAM_SEEK_CUR, &ull);
    ok(hr == S_OK || hr == STG_E_SEEKERROR /* win8 */, "IStream_Seek\n");
    if (SUCCEEDED(hr))
        ok(ull.u.LowPart == 0x00000007, "should have set LowPart to 0x00000007 instead of %08x\n", ull.u.LowPart);
    else
        ok(ull.u.LowPart == 0x80000008, "should have set LowPart to 0x80000008 instead of %08x\n", ull.u.LowPart);
    ok(ull.u.HighPart == 0, "should have set HighPart to 0 instead of %d\n", ull.u.HighPart);

    hr = IStream_Commit(pStream, STGC_DEFAULT);
    ok_ole_success(hr, "IStream_Commit");

    hr = IStream_Revert(pStream);
    ok_ole_success(hr, "IStream_Revert");

    hr = IStream_LockRegion(pStream, ull, ull, LOCK_WRITE);
    ok(hr == STG_E_INVALIDFUNCTION, "IStream_LockRegion should have returned STG_E_INVALIDFUNCTION instead of 0x%08x\n", hr);

    hr = IStream_Stat(pStream, &statstg, STATFLAG_DEFAULT);
    ok_ole_success(hr, "IStream_Stat");
    ok(statstg.type == STGTY_STREAM, "statstg.type should have been STGTY_STREAM instead of %d\n", statstg.type);

    /* test OOM condition */
    ull.u.HighPart = -1;
    ull.u.LowPart = -1;
    hr = IStream_SetSize(pStream, ull);
    ok(hr == E_OUTOFMEMORY || broken(hr == S_OK), /* win9x */
       "IStream_SetSize with large size should have returned E_OUTOFMEMORY instead of 0x%08x\n", hr);

    IStream_Release(pStream);
}