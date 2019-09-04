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
typedef  int /*<<< orphan*/  invariate ;
typedef  int /*<<< orphan*/  dest ;
typedef  char WCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pConvertINetUnicodeToMultiByte (int /*<<< orphan*/ *,int,char*,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void test_ConvertINetUnicodeToMultiByte(void)
{
    CHAR dest[MAX_PATH];
    CHAR invariate[MAX_PATH];
    INT srcsz, destsz;
    HRESULT hr;

    static WCHAR src[] = {'a','b','c',0};

    memset(invariate, 'x', sizeof(invariate));

    /* lpSrcStr NULL */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src) + 1;
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, NULL, &srcsz, dest, &destsz);
    ok(hr == S_OK || hr == E_FAIL, "Expected S_OK or E_FAIL, got %08x\n", hr);
    if (hr == S_OK)
        ok(srcsz == lstrlenW(src) + 1,
           "Expected %u, got %u\n", lstrlenW(src) + 1, srcsz);
    else if (hr == E_FAIL)
        ok(srcsz == 0,
           "Expected %u, got %u\n", 0, srcsz);
    ok(!memcmp(dest, invariate, sizeof(dest)),
       "Expected dest to be unchanged, got %s\n", dest);
    ok(destsz == 0, "Expected 0, got %u\n", destsz);

    /* lpnWideCharCount NULL */
    memset(dest, 'x', sizeof(dest));
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, NULL, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!strncmp(dest, "abc", 3),
       "Expected first three chars to be \"abc\"\n");
    ok(!memcmp(&dest[3], invariate, sizeof(dest) - 3),
       "Expected rest of dest to be unchanged, got %s\n", dest);
    ok(destsz == lstrlenW(src),
       "Expected %u, got %u\n", lstrlenW(src), destsz);

    /* both lpSrcStr and lpnWideCharCount NULL */
    memset(dest, 'x', sizeof(dest));
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, NULL, NULL, dest, &destsz);
    ok(hr == S_OK || hr == E_FAIL, "Expected S_OK or E_FAIL, got %08x\n", hr);
    ok(!memcmp(dest, invariate, sizeof(dest)),
       "Expected dest to be unchanged, got %s\n", dest);
    ok(destsz == 0, "Expected 0, got %u\n", destsz);

    /* lpDstStr NULL */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src) + 1;
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, NULL, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, srcsz);
    ok(destsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, srcsz);

    /* lpnMultiCharCount NULL */
    memset(dest, 'x', sizeof(dest));
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, srcsz);
    ok(!memcmp(dest, invariate, sizeof(dest)),
       "Expected dest to be unchanged, got %s\n", dest);

    /* lpnWideCharCount is 0 */
    memset(dest, 'x', sizeof(dest));
    srcsz = 0;
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == 0, "Expected 0, got %u\n", srcsz);
    ok(!memcmp(dest, invariate, sizeof(dest)),
       "Expected dest to be unchanged, got %s\n", dest);
    ok(destsz == 0, "Expected 0, got %u\n", destsz);

    /* lpnWideCharCount does not include NULL terminator */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src);
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src),
       "Expected %u, got %u\n", lstrlenW(src), srcsz);
    ok(!strncmp(dest, "abc", 3), "Expected first three chars to be \"abc\"\n");
    ok(!memcmp(&dest[3], invariate, sizeof(dest) - 3),
       "Expected rest of dest to be unchanged, got %s\n", dest);
    ok(destsz == lstrlenW(src),
       "Expected %u, got %u\n", lstrlenW(src), destsz);

    /* lpnWideCharCount includes NULL terminator */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src) + 1;
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src) + 1, "Expected 3, got %u\n", srcsz);
    ok(!lstrcmpA(dest, "abc"), "Expected \"abc\", got \"%s\"\n", dest);
    ok(destsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, destsz);

    /* lpnWideCharCount is -1 */
    memset(dest, 'x', sizeof(dest));
    srcsz = -1;
    destsz = sizeof(dest);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src),
       "Expected %u, got %u\n", lstrlenW(src), srcsz);
    ok(!strncmp(dest, "abc", 3), "Expected first three chars to be \"abc\"\n");
    ok(!memcmp(&dest[3], invariate, sizeof(dest) - 3),
       "Expected rest of dest to be unchanged, got %s\n", dest);
    ok(destsz == lstrlenW(src),
       "Expected %u, got %u\n", lstrlenW(src), destsz);

    /* lpnMultiCharCount is 0 */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src) + 1;
    destsz = 0;
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, srcsz);
    ok(!memcmp(dest, invariate, sizeof(dest)),
       "Expected dest to be unchanged, got %s\n", dest);
    ok(destsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, destsz);

    /* lpnMultiCharCount is not large enough */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src) + 1;
    destsz = lstrlenW(src);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == E_FAIL, "Expected E_FAIL, got %08x\n", hr);
    ok(srcsz == 0, "Expected 0, got %u\n", srcsz);
    ok(!strncmp(dest, "abc", 3), "Expected first three chars to be \"abc\"\n");
    ok(!memcmp(&dest[3], invariate, sizeof(dest) - 3),
       "Expected rest of dest to be unchanged, got %s\n", dest);
    ok(destsz == 0, "Expected 0, got %u\n", srcsz);

    /* lpnMultiCharCount (bytes) does not leave room for NULL terminator */
    memset(dest, 'x', sizeof(dest));
    srcsz = lstrlenW(src) + 1;
    destsz = lstrlenW(src) * sizeof(WCHAR);
    hr = pConvertINetUnicodeToMultiByte(NULL, 1252, src, &srcsz, dest, &destsz);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(srcsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, srcsz);
    ok(!lstrcmpA(dest, "abc"), "Expected \"abc\", got \"%s\"\n", dest);
    ok(destsz == lstrlenW(src) + 1,
       "Expected %u, got %u\n", lstrlenW(src) + 1, destsz);
}