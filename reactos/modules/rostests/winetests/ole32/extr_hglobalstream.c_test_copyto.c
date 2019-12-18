#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szHello ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int ULONG ;
struct TYPE_6__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,char const*,int,int*) ; 
 int /*<<< orphan*/  STREAM_SEEK_CUR ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Test_Stream ; 
 char** expected_method_list ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static void test_copyto(void)
{
    IStream *pStream, *pStream2;
    HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    static const char szHello[] = "Hello";
    ULARGE_INTEGER cb;
    static const char *methods_copyto[] =
    {
        "TestStream_Write",
        NULL
    };
    ULONG written;
    ULARGE_INTEGER ullRead;
    ULARGE_INTEGER ullWritten;
    ULARGE_INTEGER libNewPosition;
    static const LARGE_INTEGER llZero;
    char buffer[15];

    ok_ole_success(hr, "CreateStreamOnHGlobal");

    expected_method_list = methods_copyto;

    hr = IStream_Write(pStream, szHello, sizeof(szHello), &written);
    ok_ole_success(hr, "IStream_Write");
    ok(written == sizeof(szHello), "only %d bytes written\n", written);

    hr = IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");

    cb.QuadPart = sizeof(szHello);
    hr = IStream_CopyTo(pStream, &Test_Stream, cb, &ullRead, &ullWritten);
    ok(ullWritten.QuadPart == 5, "ullWritten was %d instead\n", (ULONG)ullWritten.QuadPart);
    ok(ullRead.QuadPart == sizeof(szHello), "only %d bytes read\n", (ULONG)ullRead.QuadPart);
    ok_ole_success(hr, "IStream_CopyTo");

    ok(!*expected_method_list, "Method sequence starting from %s not called\n", *expected_method_list);

    hr = IStream_Clone(pStream, &pStream2);
    ok_ole_success(hr, "IStream_Clone");

    hr = IStream_Seek(pStream2, llZero, STREAM_SEEK_CUR, &libNewPosition);
    ok_ole_success(hr, "IStream_Seek");
    ok(libNewPosition.QuadPart == sizeof(szHello), "libNewPosition wasn't set correctly for the cloned stream\n");

    hr = IStream_Seek(pStream2, llZero, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");

    hr = IStream_Read(pStream2, buffer, sizeof(buffer), NULL);
    ok_ole_success(hr, "IStream_Read");
    ok(!strcmp(buffer, szHello), "read data \"%s\" didn't match originally written data\n", buffer);

    IStream_Release(pStream2);
    IStream_Release(pStream);
}