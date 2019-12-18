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
typedef  char WCHAR ;
struct TYPE_7__ {scalar_t__ pszVal; int /*<<< orphan*/  pwszVal; } ;
struct TYPE_8__ {scalar_t__ vt; TYPE_1__ u; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IMimeMessage ;
typedef  int /*<<< orphan*/  IMimeBody ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 void* CoTaskMemAlloc (scalar_t__) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  HBODY_ROOT ; 
 int /*<<< orphan*/  IID_IMimeBody ; 
 scalar_t__ IMimeBody_GetProp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IMimeBody_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMimeBody_SetProp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IMimeMessage_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMimeMessage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MIME_E_NOT_FOUND ; 
 scalar_t__ MimeOleCreateMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* PIDTOSTR (int) ; 
 int PID_HDR_SUBJECT ; 
 int PID_HDR_TO ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_LPSTR ; 
 scalar_t__ VT_LPWSTR ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_MessageSetProp(void)
{
    static const char topic[] = "wine topic";
    static const WCHAR topicW[] = {'w','i','n','e',' ','t','o','p','i','c',0};
    HRESULT hr;
    IMimeMessage *msg;
    IMimeBody *body;
    PROPVARIANT prop;

    hr = MimeOleCreateMessage(NULL, &msg);
    ok(hr == S_OK, "ret %08x\n", hr);

    PropVariantInit(&prop);

    hr = IMimeMessage_BindToObject(msg, HBODY_ROOT, &IID_IMimeBody, (void**)&body);
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_SetProp(body, NULL, 0, &prop);
    ok(hr == E_INVALIDARG, "ret %08x\n", hr);

    hr = IMimeBody_SetProp(body, "Thread-Topic", 0, NULL);
    ok(hr == E_INVALIDARG, "ret %08x\n", hr);

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, "Thread-Topic", 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    hr = IMimeBody_GetProp(body, NULL, 0, &prop);
    ok(hr == E_INVALIDARG, "ret %08x\n", hr);

    hr = IMimeBody_GetProp(body, "Thread-Topic", 0, NULL);
    ok(hr == E_INVALIDARG, "ret %08x\n", hr);

    hr = IMimeBody_GetProp(body, "Wine-Topic", 0, &prop);
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    prop.vt = VT_LPSTR;
    hr = IMimeBody_GetProp(body, "Thread-Topic", 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    if(hr == S_OK)
    {
        ok(prop.vt == VT_LPSTR, "type %d\n", prop.vt);
        ok(!strcmp(prop.u.pszVal, topic), "got  %s\n", prop.u.pszVal);
        PropVariantClear(&prop);
    }

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, PIDTOSTR(PID_HDR_SUBJECT), 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    prop.vt = VT_LPSTR;
    hr = IMimeBody_GetProp(body, PIDTOSTR(PID_HDR_SUBJECT), 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    if(hr == S_OK)
    {
        ok(prop.vt == VT_LPSTR, "type %d\n", prop.vt);
        ok(!strcmp(prop.u.pszVal, topic), "got  %s\n", prop.u.pszVal);
        PropVariantClear(&prop);
    }

    /* Using the name or PID returns the same result. */
    prop.vt = VT_LPSTR;
    hr = IMimeBody_GetProp(body, "Subject", 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    if(hr == S_OK)
    {
        ok(prop.vt == VT_LPSTR, "type %d\n", prop.vt);
        ok(!strcmp(prop.u.pszVal, topic), "got  %s\n", prop.u.pszVal);
        PropVariantClear(&prop);
    }

    prop.vt = VT_LPWSTR;
    hr = IMimeBody_GetProp(body, "Subject", 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    if(hr == S_OK)
    {
        ok(prop.vt == VT_LPWSTR, "type %d\n", prop.vt);
        ok(!lstrcmpW(prop.u.pwszVal, topicW), "got %s\n", wine_dbgstr_w(prop.u.pwszVal));
        PropVariantClear(&prop);
    }

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, PIDTOSTR(PID_HDR_TO), 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    /* Out of Range PID */
    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, PIDTOSTR(124), 0, &prop);
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);
    PropVariantClear(&prop);

    IMimeBody_Release(body);
    IMimeMessage_Release(msg);
}