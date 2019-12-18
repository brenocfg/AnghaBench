#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* pszVal; } ;
struct TYPE_8__ {TYPE_1__ u; void* vt; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IMimeMessage ;
typedef  int /*<<< orphan*/  IMimeBody ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 void* CoTaskMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  HBODY_ROOT ; 
 int /*<<< orphan*/  IID_IMimeBody ; 
 scalar_t__ IMimeBody_DeleteProp (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IMimeBody_GetProp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IMimeBody_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMimeBody_SetProp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IMimeMessage_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMimeMessage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MIME_E_NOT_FOUND ; 
 scalar_t__ MimeOleCreateMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* PIDTOSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PID_HDR_SUBJECT ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 void* VT_LPSTR ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void test_BodyDeleteProp(void)
{
    static const char topic[] = "wine topic";
    HRESULT hr;
    IMimeMessage *msg;
    IMimeBody *body;
    PROPVARIANT prop;

    hr = MimeOleCreateMessage(NULL, &msg);
    ok(hr == S_OK, "ret %08x\n", hr);

    PropVariantInit(&prop);

    hr = IMimeMessage_BindToObject(msg, HBODY_ROOT, &IID_IMimeBody, (void**)&body);
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_DeleteProp(body, "Subject");
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    hr = IMimeBody_DeleteProp(body, PIDTOSTR(PID_HDR_SUBJECT));
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, "Subject", 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    hr = IMimeBody_DeleteProp(body, "Subject");
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_GetProp(body, "Subject", 0, &prop);
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, PIDTOSTR(PID_HDR_SUBJECT), 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    hr = IMimeBody_DeleteProp(body, PIDTOSTR(PID_HDR_SUBJECT));
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_GetProp(body, PIDTOSTR(PID_HDR_SUBJECT), 0, &prop);
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    IMimeBody_Release(body);
    IMimeMessage_Release(msg);
}