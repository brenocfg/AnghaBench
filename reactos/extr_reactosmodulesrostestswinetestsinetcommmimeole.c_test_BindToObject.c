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
typedef  int /*<<< orphan*/  IMimeMessage ;
typedef  int /*<<< orphan*/  IMimeBody ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  HBODY_ROOT ; 
 int /*<<< orphan*/  IID_IMimeBody ; 
 int /*<<< orphan*/  IMimeBody_Release (int /*<<< orphan*/ *) ; 
 int IMimeMessage_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int IMimeMessage_CountBodies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IMimeMessage_Release (int /*<<< orphan*/ *) ; 
 int MimeOleCreateMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_BindToObject(void)
{
    HRESULT hr;
    IMimeMessage *msg;
    IMimeBody *body;
    ULONG count;

    hr = MimeOleCreateMessage(NULL, &msg);
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeMessage_CountBodies(msg, HBODY_ROOT, TRUE, &count);
    ok(hr == S_OK, "ret %08x\n", hr);
    ok(count == 1, "got %d\n", count);

    hr = IMimeMessage_BindToObject(msg, HBODY_ROOT, &IID_IMimeBody, (void**)&body);
    ok(hr == S_OK, "ret %08x\n", hr);
    IMimeBody_Release(body);

    IMimeMessage_Release(msg);
}