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
struct HEADER_TYPE {char* value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  all ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ IHTMLXMLHttpRequest_getAllResponseHeaders (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLXMLHttpRequest_getResponseHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * a2bstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhr ; 

__attribute__((used)) static void test_header(const struct HEADER_TYPE expect[], int num)
{
    int i;
    BSTR key, text, all_header;
    HRESULT hres;
    char all[4096], buf[512];

    all_header = NULL;
    hres = IHTMLXMLHttpRequest_getAllResponseHeaders(xhr, &all_header);
    ok(hres == S_OK, "getAllResponseHeader failed: %08x\n", hres);
    ok(all_header != NULL, "all_header == NULL\n");

    WideCharToMultiByte(CP_UTF8, 0, all_header, -1, all, sizeof(all), NULL, NULL);
    SysFreeString(all_header);

    for(i = 0; i < num; ++i) {
        text = NULL;
        key = a2bstr(expect[i].key);
        hres = IHTMLXMLHttpRequest_getResponseHeader(xhr, key, &text);
        ok(hres == S_OK, "getResponseHeader failed, got %08x\n", hres);
        ok(text != NULL, "text == NULL\n");
        ok(!strcmp_wa(text, expect[i].value),
            "Expect %s: %s, got %s\n", expect[i].key, expect[i].value, wine_dbgstr_w(text));
        SysFreeString(key);
        SysFreeString(text);

        strcpy(buf, expect[i].key);
        strcat(buf, ": ");
        strcat(buf, expect[i].value);
        ok(strstr(all, buf) != NULL, "AllResponseHeaders(%s) don't have expected substr(%s)\n", all, buf);
    }
}