#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hello ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int HRESULT ;
typedef  int HGLOBAL ;

/* Variables and functions */
 int CreateStreamOnHGlobal (int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  GMEM_FIXED ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int GetHGlobalFromStream (int /*<<< orphan*/ *,int*) ; 
 int GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 int IStream_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IStream_Read (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int IStream_Release (int /*<<< orphan*/ *) ; 
 int IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IStream_SetSize (int /*<<< orphan*/ *,TYPE_1__) ; 
 int IStream_Write (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  stream_info (int /*<<< orphan*/ *,int*,int*,int*) ; 

__attribute__((used)) static void test_IStream_Clone(void)
{
    static const char hello[] = "Hello World!";
    char buf[32];
    HRESULT hr;
    IStream *stream, *clone;
    HGLOBAL orig_hmem, hmem, hmem_clone;
    ULARGE_INTEGER newsize;
    LARGE_INTEGER offset;
    int size, pos, ret;

    /* test simple case for Clone */
    orig_hmem = GlobalAlloc(GMEM_MOVEABLE, 0);
    ok(orig_hmem != 0, "unexpected %p\n", orig_hmem);
    hr = CreateStreamOnHGlobal(orig_hmem, TRUE, &stream);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    hr = GetHGlobalFromStream(stream, NULL);
    ok(hr == E_INVALIDARG, "unexpected %#x\n", hr);

    hr = GetHGlobalFromStream(NULL, &hmem);
    ok(hr == E_INVALIDARG, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem == orig_hmem, "handles should match\n");
    ok(size == 0,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    hr = IStream_Clone(stream, &clone);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    hr = IStream_Write(stream, hello, sizeof(hello), NULL);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0, "unexpected %p\n", hmem);
    ok(size == 13,  "unexpected %d\n", size);
    ok(pos == 13,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 13,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    buf[0] = 0;
    hr = IStream_Read(clone, buf, sizeof(buf), NULL);
    ok(hr == S_OK, "unexpected %#x\n", hr);
    ok(!strcmp(buf, hello), "wrong stream contents\n");

    newsize.QuadPart = 0x8000;
    hr = IStream_SetSize(stream, newsize);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0,  "unexpected %p\n", hmem);
    ok(hmem == orig_hmem,  "unexpected %p\n", hmem);
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 13,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 13,  "unexpected %d\n", pos);

    IStream_Release(clone);
    IStream_Release(stream);

    /* exploit GMEM_FIXED forced move for the same base streams */
    orig_hmem = GlobalAlloc(GMEM_FIXED, 1);
    ok(orig_hmem != 0, "unexpected %p\n", orig_hmem);
    hr = CreateStreamOnHGlobal(orig_hmem, TRUE, &stream);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    hr = IStream_Clone(stream, &clone);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0,  "unexpected %p\n", hmem);
    ok(size == 1,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 1,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    newsize.QuadPart = 0x8000;
    hr = IStream_SetSize(stream, newsize);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0,  "unexpected %p\n", hmem);
    ok(hmem != orig_hmem,  "unexpected %p\n", hmem);
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    IStream_Release(stream);
    IStream_Release(clone);

    /* exploit GMEM_FIXED forced move for different base streams */
    orig_hmem = GlobalAlloc(GMEM_FIXED, 1);
    ok(orig_hmem != 0, "unexpected %p\n", orig_hmem);
    hr = CreateStreamOnHGlobal(orig_hmem, TRUE, &stream);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    hr = CreateStreamOnHGlobal(orig_hmem, TRUE, &clone);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0,  "unexpected %p\n", hmem);
    ok(size == 1,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 1,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    newsize.QuadPart = 0x8000;
    hr = IStream_SetSize(stream, newsize);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0,  "unexpected %p\n", hmem);
    ok(hmem != orig_hmem,  "unexpected %p\n", hmem);
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone != hmem, "handles should not match\n");
    ok(size == 1,  "unexpected %#x\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    IStream_Release(stream);
    /* releasing clone leads to test termination under windows
    IStream_Release(clone);
    */

    /* test Release for a being cloned stream */
    hr = CreateStreamOnHGlobal(0, TRUE, &stream);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    hr = IStream_Clone(stream, &clone);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(stream, &hmem, &size, &pos);
    ok(hmem != 0,  "unexpected %p\n", hmem);
    ok(size == 0,  "unexpected %d\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 0,  "unexpected %#x\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    ret = IStream_Release(stream);
    ok(ret == 0, "unexpected %d\n", ret);

    newsize.QuadPart = 0x8000;
    hr = IStream_SetSize(clone, newsize);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 0,  "unexpected %d\n", pos);

    hr = IStream_Write(clone, hello, sizeof(hello), NULL);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 13,  "unexpected %d\n", pos);

    offset.QuadPart = 0;
    hr = IStream_Seek(clone, offset, STREAM_SEEK_SET, NULL);
    ok(hr == S_OK, "unexpected %#x\n", hr);

    buf[0] = 0;
    hr = IStream_Read(clone, buf, sizeof(buf), NULL);
    ok(hr == S_OK, "unexpected %#x\n", hr);
    ok(!strcmp(buf, hello), "wrong stream contents\n");

    stream_info(clone, &hmem_clone, &size, &pos);
    ok(hmem_clone == hmem, "handles should match\n");
    ok(size == 0x8000,  "unexpected %#x\n", size);
    ok(pos == 32,  "unexpected %d\n", pos);

    ret = IStream_Release(clone);
    ok(ret == 0, "unexpected %d\n", ret);
}