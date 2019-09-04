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
typedef  int /*<<< orphan*/  IMimeMessage ;
typedef  int /*<<< orphan*/  IMimeBody ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HBODY ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HBODY_ROOT ; 
 int /*<<< orphan*/  IET_BASE64 ; 
 int /*<<< orphan*/  IET_BINARY ; 
 int /*<<< orphan*/  IET_QP ; 
 int /*<<< orphan*/  IID_IMimeBody ; 
 int IMimeBody_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMimeBody_Release (int /*<<< orphan*/ *) ; 
 int IMimeMessage_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int IMimeMessage_CountBodies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int IMimeMessage_GetAttachments (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **) ; 
 int IMimeMessage_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMimeMessage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int MimeOleCreateMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_stream_from_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mhtml_page1 ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  test_current_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_stream_read (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void test_mhtml_message(void)
{
    IMimeMessage *mime_message;
    IMimeBody *mime_body;
    HBODY *body_list;
    IStream *stream;
    ULONG count;
    HRESULT hres;

    hres = MimeOleCreateMessage(NULL, &mime_message);
    ok(hres == S_OK, "MimeOleCreateMessage failed: %08x\n", hres);

    stream = create_stream_from_string(mhtml_page1);
    hres = IMimeMessage_Load(mime_message, stream);
    IStream_Release(stream);
    ok(hres == S_OK, "Load failed: %08x\n", hres);

    hres = IMimeMessage_CountBodies(mime_message, HBODY_ROOT, TRUE, &count);
    ok(hres == S_OK, "CountBodies failed: %08x\n", hres);
    ok(count == 3, "got %d\n", count);

    hres = IMimeMessage_GetAttachments(mime_message, &count, &body_list);
    ok(hres == S_OK, "GetAttachments failed: %08x\n", hres);
    ok(count == 2, "count = %u\n", count);

    hres = IMimeMessage_BindToObject(mime_message, body_list[0], &IID_IMimeBody, (void**)&mime_body);
    ok(hres == S_OK, "BindToObject failed: %08x\n", hres);

    hres = IMimeBody_GetData(mime_body, IET_BINARY, &stream);
    ok(hres == S_OK, "GetData failed: %08x\n", hres);
    test_stream_read(stream, S_OK, "<HTML></HTML>", -1);
    IStream_Release(stream);

    test_current_encoding(mime_body, IET_QP);

    IMimeBody_Release(mime_body);

    hres = IMimeMessage_BindToObject(mime_message, body_list[1], &IID_IMimeBody, (void**)&mime_body);
    ok(hres == S_OK, "BindToObject failed: %08x\n", hres);

    test_current_encoding(mime_body, IET_BASE64);

    hres = IMimeBody_GetData(mime_body, IET_BINARY, &stream);
    ok(hres == S_OK, "GetData failed: %08x\n", hres);
    test_stream_read(stream, S_OK, "Test", -1);
    IStream_Release(stream);

    IMimeBody_Release(mime_body);

    CoTaskMemFree(body_list);

    IMimeMessage_Release(mime_message);
}