#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {char* mime; int broken_failure; char* broken_mime; int hres; char* mime_pjpeg; int /*<<< orphan*/  size; int /*<<< orphan*/ * data; int /*<<< orphan*/  proposed_mime; int /*<<< orphan*/  url; } ;
typedef  char* LPWSTR ;
typedef  int HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 int E_FAIL ; 
 int E_INVALIDARG ; 
 int S_OK ; 
 char* a2w (int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * data1 ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 TYPE_1__* mime_tests ; 
 TYPE_1__* mime_tests2 ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pFindMimeFromData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp_wa (char*,char*) ; 
 char* url1 ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_FindMimeFromData(void)
{
    WCHAR *mime, *proposed_mime, *url;
    HRESULT hres;
    BYTE b;
    int i;

    static const WCHAR app_octet_streamW[] =
        {'a','p','p','l','i','c','a','t','i','o','n','/','o','c','t','e','t','-','s','t','r','e','a','m',0};
    static const WCHAR image_pjpegW[] = {'i','m','a','g','e','/','p','j','p','e','g',0};
    static const WCHAR text_htmlW[] = {'t','e','x','t','/','h','t','m','l',0};
    static const WCHAR text_plainW[] = {'t','e','x','t','/','p','l','a','i','n',0};

    for(i = 0; i < ARRAY_SIZE(mime_tests); i++) {
        mime = (LPWSTR)0xf0f0f0f0;
        url = a2w(mime_tests[i].url);
        hres = pFindMimeFromData(NULL, url, NULL, 0, NULL, 0, &mime, 0);
        if(mime_tests[i].mime) {
            ok(hres == S_OK || broken(mime_tests[i].broken_failure), "[%d] FindMimeFromData failed: %08x\n", i, hres);
            if(hres == S_OK) {
                ok(!strcmp_wa(mime, mime_tests[i].mime)
                   || broken(mime_tests[i].broken_mime && !strcmp_wa(mime, mime_tests[i].broken_mime)),
                   "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
                CoTaskMemFree(mime);
            }
        }else {
            ok(hres == E_FAIL || hres == mime_tests[i].hres,
               "[%d] FindMimeFromData failed: %08x, expected %08x\n",
               i, hres, mime_tests[i].hres);
            ok(mime == (LPWSTR)0xf0f0f0f0, "[%d] mime != 0xf0f0f0f0\n", i);
        }

        mime = (LPWSTR)0xf0f0f0f0;
        hres = pFindMimeFromData(NULL, url, NULL, 0, text_plainW, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        ok(!strcmp_wa(mime, "text/plain"), "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        CoTaskMemFree(mime);

        mime = (LPWSTR)0xf0f0f0f0;
        hres = pFindMimeFromData(NULL, url, NULL, 0, app_octet_streamW, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        ok(!strcmp_wa(mime, "application/octet-stream"), "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        CoTaskMemFree(mime);
        heap_free(url);
    }

    for(i = 0; i < ARRAY_SIZE(mime_tests2); i++) {
        url = a2w(mime_tests2[i].url);
        proposed_mime = a2w(mime_tests2[i].proposed_mime);
        hres = pFindMimeFromData(NULL, url, mime_tests2[i].data, mime_tests2[i].size,
                proposed_mime, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        b = !strcmp_wa(mime, mime_tests2[i].mime);
        ok(b || broken(mime_tests2[i].broken_mime && !strcmp_wa(mime, mime_tests2[i].broken_mime)),
            "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        heap_free(proposed_mime);
        heap_free(url);
        CoTaskMemFree(mime);
        if(!b || url || proposed_mime)
            continue;

        hres = pFindMimeFromData(NULL, NULL, mime_tests2[i].data, mime_tests2[i].size,
                app_octet_streamW, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        ok(!strcmp_wa(mime, mime_tests2[i].mime) || broken(mime_tests2[i].broken_mime
                        && !strcmp_wa(mime, mime_tests2[i].broken_mime)),
                    "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        CoTaskMemFree(mime);

        hres = pFindMimeFromData(NULL, NULL, mime_tests2[i].data, mime_tests2[i].size,
                text_plainW, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        ok(!strcmp_wa(mime, mime_tests2[i].mime) || broken(mime_tests2[i].broken_mime
                    && !strcmp_wa(mime, mime_tests2[i].broken_mime)),
                "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        CoTaskMemFree(mime);

        hres = pFindMimeFromData(NULL, NULL, mime_tests2[i].data, mime_tests2[i].size,
                text_htmlW, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        if(!strcmp("application/octet-stream", mime_tests2[i].mime)
           || !strcmp("text/plain", mime_tests2[i].mime) || i==92)
            ok(!strcmp_wa(mime, "text/html"), "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        else
            ok(!strcmp_wa(mime, mime_tests2[i].mime), "[%d] wrong mime: %s\n", i, wine_dbgstr_w(mime));
        CoTaskMemFree(mime);

        hres = pFindMimeFromData(NULL, NULL, mime_tests2[i].data, mime_tests2[i].size,
                image_pjpegW, 0, &mime, 0);
        ok(hres == S_OK, "[%d] FindMimeFromData failed: %08x\n", i, hres);
        ok(!strcmp_wa(mime, mime_tests2[i].mime_pjpeg ? mime_tests2[i].mime_pjpeg : mime_tests2[i].mime)
           || broken(!strcmp_wa(mime, mime_tests2[i].mime)),
           "[%d] wrong mime, got %s\n", i, wine_dbgstr_w(mime));
        CoTaskMemFree(mime);
    }

    hres = pFindMimeFromData(NULL, NULL, NULL, 0, NULL, 0, &mime, 0);
    ok(hres == E_INVALIDARG, "FindMimeFromData failed: %08x, expected E_INVALIDARG\n", hres);

    hres = pFindMimeFromData(NULL, NULL, NULL, 0, text_plainW, 0, &mime, 0);
    ok(hres == E_INVALIDARG, "FindMimeFromData failed: %08x, expected E_INVALIDARG\n", hres);

    hres = pFindMimeFromData(NULL, NULL, data1, 0, NULL, 0, &mime, 0);
    ok(hres == E_FAIL, "FindMimeFromData failed: %08x, expected E_FAIL\n", hres);

    hres = pFindMimeFromData(NULL, url1, data1, 0, NULL, 0, &mime, 0);
    ok(hres == E_FAIL, "FindMimeFromData failed: %08x, expected E_FAIL\n", hres);

    hres = pFindMimeFromData(NULL, NULL, data1, 0, text_plainW, 0, &mime, 0);
    ok(hres == S_OK, "FindMimeFromData failed: %08x\n", hres);
    ok(!strcmp_wa(mime, "text/plain"), "wrong mime: %s\n", wine_dbgstr_w(mime));
    CoTaskMemFree(mime);

    hres = pFindMimeFromData(NULL, NULL, data1, 0, text_plainW, 0, NULL, 0);
    ok(hres == E_INVALIDARG, "FindMimeFromData failed: %08x, expected E_INVALIDARG\n", hres);
}