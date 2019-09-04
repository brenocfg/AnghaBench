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
typedef  char WCHAR ;
typedef  scalar_t__ PATTRINFO ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TAG_16BIT_DESCRIPTION ; 
 int /*<<< orphan*/  TAG_16BIT_MODULE_NAME ; 
 int /*<<< orphan*/  TAG_BIN_FILE_VERSION ; 
 int /*<<< orphan*/  TAG_BIN_PRODUCT_VERSION ; 
 int /*<<< orphan*/  TAG_CHECKSUM ; 
 int /*<<< orphan*/  TAG_COMPANY_NAME ; 
 int /*<<< orphan*/  TAG_EXE_WRAPPER ; 
 int /*<<< orphan*/  TAG_EXPORT_NAME ; 
 int /*<<< orphan*/  TAG_FILE_DESCRIPTION ; 
 int /*<<< orphan*/  TAG_FILE_VERSION ; 
 int /*<<< orphan*/  TAG_INTERNAL_NAME ; 
 int /*<<< orphan*/  TAG_LEGAL_COPYRIGHT ; 
 int /*<<< orphan*/  TAG_LINKER_VERSION ; 
 int /*<<< orphan*/  TAG_LINK_DATE ; 
 int /*<<< orphan*/  TAG_MODULE_TYPE ; 
 int /*<<< orphan*/  TAG_ORIGINAL_FILENAME ; 
 int /*<<< orphan*/  TAG_PE_CHECKSUM ; 
 int /*<<< orphan*/  TAG_PRODUCT_NAME ; 
 int /*<<< orphan*/  TAG_PRODUCT_VERSION ; 
 int /*<<< orphan*/  TAG_SIZE ; 
 int /*<<< orphan*/  TAG_UPTO_BIN_FILE_VERSION ; 
 int /*<<< orphan*/  TAG_UPTO_BIN_PRODUCT_VERSION ; 
 int /*<<< orphan*/  TAG_UPTO_LINK_DATE ; 
 int /*<<< orphan*/  TAG_VERDATEHI ; 
 int /*<<< orphan*/  TAG_VERDATELO ; 
 int /*<<< orphan*/  TAG_VERFILEOS ; 
 int /*<<< orphan*/  TAG_VERFILETYPE ; 
 int /*<<< orphan*/  TAG_VER_LANGUAGE ; 
 int VFT_APP ; 
 int VOS__WINDOWS32 ; 
 int /*<<< orphan*/  expect_tag_dword (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect_tag_empty (scalar_t__,int) ; 
 int /*<<< orphan*/  expect_tag_qword (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect_tag_skip (scalar_t__,int) ; 
 int /*<<< orphan*/  expect_tag_skip_range (scalar_t__,int,int) ; 
 int /*<<< orphan*/  expect_tag_str (scalar_t__,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSdbFreeFileAttributes (scalar_t__) ; 
 scalar_t__ pSdbGetFileAttributes (char const*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  test_crc (int,int) ; 
 int /*<<< orphan*/  test_crc2 (int,int,int) ; 
 int /*<<< orphan*/  test_create_exe (char*,int) ; 
 int /*<<< orphan*/  test_create_file (char*,char*,int) ; 
 int /*<<< orphan*/  test_create_ne (char*,int) ; 

__attribute__((used)) static void test_ApplicationAttributes(void)
{
    static const WCHAR path[] = {'t','e','s','t','x','x','.','e','x','e',0};
    static const WCHAR PRODUCT_VERSION[] = {'1','.','0','.','0','.','1',0};
    static const WCHAR FILE_DESCRIPTION[] = {'F','i','l','e','D','e','s','c','r','i','p','t','i','o','n',0};
    static const WCHAR COMPANY_NAME[] = {'C','o','m','p','a','n','y','N','a','m','e',0};
    static const WCHAR PRODUCT_NAME[] = {'P','r','o','d','u','c','t','N','a','m','e',0};
    static const WCHAR FILE_VERSION[] = {'1','.','0','.','0','.','0',0};
    static const WCHAR ORIGINAL_FILENAME[] = {'O','r','i','g','i','n','a','l','F','i','l','e','n','a','m','e',0};
    static const WCHAR INTERNAL_NAME[] = {'I','n','t','e','r','n','a','l','N','a','m','e',0};
    static const WCHAR LEGAL_COPYRIGHT[] = {'L','e','g','a','l','C','o','p','y','r','i','g','h','t',0};
    static const WCHAR EXPORT_NAME[] = {'T','e','S','t','2','.','e','x','e',0};
    static const WCHAR OS2_DESCRIPTION[] = {'M','O','D',' ','D','E','S','C','R','I','P','T','I','O','N',' ','H','E','R','E',0};
    static const WCHAR OS2_EXPORT_NAME[] = {'T','E','S','T','M','O','D','.','h','X','x',0};
    static const WCHAR OS2_DESCRIPTION_broken[] = {'Z',0};
    static const WCHAR OS2_EXPORT_NAME_broken[] = {'E',0};

    PATTRINFO pattrinfo = (PATTRINFO)0xdead;
    DWORD num = 333;
    BOOL ret;

    /* ensure the file is not there. */
    DeleteFileA("testxx.exe");
    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret == FALSE, "expected SdbGetFileAttributes to fail.\n");
    ok(pattrinfo == (PATTRINFO)0xdead, "expected the pointer not to change.\n");
    ok(num == 333, "expected the number of items not to change.\n");
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);

    /* Test a file with as much features as possible */
    test_create_exe(L"testxx.exe", 0);

    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret != FALSE, "expected SdbGetFileAttributes to succeed.\n");
    ok(pattrinfo != (PATTRINFO)0xdead, "expected a valid pointer.\n");
    ok(num == 28, "expected 28 items, got %d.\n", num);

    if (num == 28 && ret)
    {
        expect_tag_dword(pattrinfo, 0, TAG_SIZE, 0x800);
        expect_tag_dword(pattrinfo, 1, TAG_CHECKSUM, 0x178bd629);
        expect_tag_qword(pattrinfo, 2, TAG_BIN_FILE_VERSION, 0x1000000000000ull);
        expect_tag_qword(pattrinfo, 3, TAG_BIN_PRODUCT_VERSION, 0x1000000000001ull);
        expect_tag_str(pattrinfo, 4, TAG_PRODUCT_VERSION, PRODUCT_VERSION);
        expect_tag_str(pattrinfo, 5, TAG_FILE_DESCRIPTION, FILE_DESCRIPTION);
        expect_tag_str(pattrinfo, 6, TAG_COMPANY_NAME, COMPANY_NAME);
        expect_tag_str(pattrinfo, 7, TAG_PRODUCT_NAME, PRODUCT_NAME);
        expect_tag_str(pattrinfo, 8, TAG_FILE_VERSION, FILE_VERSION);
        expect_tag_str(pattrinfo, 9, TAG_ORIGINAL_FILENAME, ORIGINAL_FILENAME);
        expect_tag_str(pattrinfo, 10, TAG_INTERNAL_NAME, INTERNAL_NAME);
        expect_tag_str(pattrinfo, 11, TAG_LEGAL_COPYRIGHT, LEGAL_COPYRIGHT);
        expect_tag_dword(pattrinfo, 12, TAG_VERDATEHI, 0x1d1a019);
        expect_tag_dword(pattrinfo, 13, TAG_VERDATELO, 0xac754c50);
        expect_tag_dword(pattrinfo, 14, TAG_VERFILEOS, VOS__WINDOWS32);
        expect_tag_dword(pattrinfo, 15, TAG_VERFILETYPE, VFT_APP);
        expect_tag_dword(pattrinfo, 16, TAG_MODULE_TYPE, 0x3); /* Win32 */
        expect_tag_dword(pattrinfo, 17, TAG_PE_CHECKSUM, 0xBAAD);
        expect_tag_dword(pattrinfo, 18, TAG_LINKER_VERSION, 0x40002);
        expect_tag_skip(pattrinfo, 19); /* TAG_16BIT_DESCRIPTION */
        expect_tag_skip(pattrinfo, 20); /* TAG_16BIT_MODULE_NAME */
        expect_tag_qword(pattrinfo, 21, TAG_UPTO_BIN_FILE_VERSION, 0x1000000000000ull);
        expect_tag_qword(pattrinfo, 22, TAG_UPTO_BIN_PRODUCT_VERSION, 0x1000000000001ull);
        expect_tag_dword(pattrinfo, 23, TAG_LINK_DATE, 0x12345);
        expect_tag_dword(pattrinfo, 24, TAG_UPTO_LINK_DATE, 0x12345);
        expect_tag_str(pattrinfo, 25, TAG_EXPORT_NAME, EXPORT_NAME);
        expect_tag_dword(pattrinfo, 26, TAG_VER_LANGUAGE, 0xffff);
        expect_tag_dword(pattrinfo, 27, TAG_EXE_WRAPPER, 0x0);
    }
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);


    /* Disable resource and exports */
    test_create_exe(L"testxx.exe", 1);

    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret != FALSE, "expected SdbGetFileAttributes to succeed.\n");
    ok(pattrinfo != (PATTRINFO)0xdead, "expected a valid pointer.\n");
    ok(num == 28, "expected 28 items, got %d.\n", num);

    if (num == 28 && ret)
    {
        expect_tag_dword(pattrinfo, 0, TAG_SIZE, 0x800);
        expect_tag_dword(pattrinfo, 1, TAG_CHECKSUM, 0xea7caffd);
        expect_tag_skip_range(pattrinfo, 2, 16);
        expect_tag_dword(pattrinfo, 16, TAG_MODULE_TYPE, 0x3); /* Win32 */
        expect_tag_dword(pattrinfo, 17, TAG_PE_CHECKSUM, 0xBAAD);
        expect_tag_dword(pattrinfo, 18, TAG_LINKER_VERSION, 0x40002);
        expect_tag_skip_range(pattrinfo, 19, 23);
        expect_tag_dword(pattrinfo, 23, TAG_LINK_DATE, 0x12345);
        expect_tag_dword(pattrinfo, 24, TAG_UPTO_LINK_DATE, 0x12345);
        expect_tag_skip(pattrinfo, 25); /* TAG_EXPORT_NAME */
        expect_tag_empty(pattrinfo, 26); /* TAG_VER_LANGUAGE */
        expect_tag_dword(pattrinfo, 27, TAG_EXE_WRAPPER, 0x0);
    }
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);

    /* A file with just 'MZ' */
    test_create_file(L"testxx.exe", "MZ", 2);

    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret != FALSE, "expected SdbGetFileAttributes to succeed.\n");
    ok(pattrinfo != (PATTRINFO)0xdead, "expected a valid pointer.\n");
    ok(num == 28, "expected 28 items, got %d.\n", num);

    if (num == 28 && ret)
    {
        expect_tag_dword(pattrinfo, 0, TAG_SIZE, 0x2);
        expect_tag_dword(pattrinfo, 1, TAG_CHECKSUM, 0);
        expect_tag_skip_range(pattrinfo, 2, 16);
        expect_tag_dword(pattrinfo, 16, TAG_MODULE_TYPE, 0x1);
        expect_tag_skip_range(pattrinfo, 17, 26);
        expect_tag_empty(pattrinfo, 26); /* TAG_VER_LANGUAGE */
        expect_tag_skip(pattrinfo, 27); /* TAG_EXE_WRAPPER */
    }
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);

    /* Empty file */
    test_create_file(L"testxx.exe", NULL, 0);

    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret != FALSE, "expected SdbGetFileAttributes to succeed.\n");
    ok(pattrinfo != (PATTRINFO)0xdead, "expected a valid pointer.\n");
    ok(num == 28, "expected 28 items, got %d.\n", num);

    if (num == 28 && ret)
    {
        expect_tag_dword(pattrinfo, 0, TAG_SIZE, 0);
        expect_tag_skip_range(pattrinfo, 1, 26);
        expect_tag_empty(pattrinfo, 26); /* TAG_VER_LANGUAGE */
        expect_tag_skip(pattrinfo, 27); /* TAG_EXE_WRAPPER */
    }
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);

    /* minimal NE executable */
    test_create_ne(L"testxx.exe", 0);

    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret != FALSE, "expected SdbGetFileAttributes to succeed.\n");
    ok(pattrinfo != (PATTRINFO)0xdead, "expected a valid pointer.\n");
    ok(num == 28, "expected 28 items, got %d.\n", num);

    if (num == 28 && ret)
    {
        expect_tag_dword(pattrinfo, 0, TAG_SIZE, 0xa8);
        expect_tag_dword(pattrinfo, 1, TAG_CHECKSUM, 0xf2abe4e9);
        expect_tag_skip_range(pattrinfo, 2, 16);
        expect_tag_dword(pattrinfo, 16, TAG_MODULE_TYPE, 0x2);
        expect_tag_skip(pattrinfo, 17); /* TAG_PE_CHECKSUM */
        expect_tag_skip(pattrinfo, 18); /* TAG_LINKER_VERSION */
        expect_tag_str(pattrinfo, 19, TAG_16BIT_DESCRIPTION, OS2_DESCRIPTION);
        expect_tag_str(pattrinfo, 20, TAG_16BIT_MODULE_NAME, OS2_EXPORT_NAME);
        expect_tag_skip_range(pattrinfo, 21, 26);
        expect_tag_empty(pattrinfo, 26); /* TAG_VER_LANGUAGE */
        expect_tag_skip(pattrinfo, 27); /* TAG_EXE_WRAPPER */
    }
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);

    /* NE executable with description / module name pointers zero, to show they are always used */
    test_create_ne(L"testxx.exe", 1);

    ret = pSdbGetFileAttributes(path, &pattrinfo, &num);
    ok(ret != FALSE, "expected SdbGetFileAttributes to succeed.\n");
    ok(pattrinfo != (PATTRINFO)0xdead, "expected a valid pointer.\n");
    ok(num == 28, "expected 28 items, got %d.\n", num);

    if (num == 28 && ret)
    {
        expect_tag_dword(pattrinfo, 0, TAG_SIZE, 0xa8);
        expect_tag_dword(pattrinfo, 1, TAG_CHECKSUM, 0xddcbe4c9);
        expect_tag_skip_range(pattrinfo, 2, 16);
        expect_tag_dword(pattrinfo, 16, TAG_MODULE_TYPE, 0x2);
        expect_tag_skip(pattrinfo, 17); /* TAG_PE_CHECKSUM */
        expect_tag_skip(pattrinfo, 18); /* TAG_LINKER_VERSION */
        expect_tag_str(pattrinfo, 19, TAG_16BIT_DESCRIPTION, OS2_DESCRIPTION_broken);   /* the 'Z' from 'MZ' */
        expect_tag_str(pattrinfo, 20, TAG_16BIT_MODULE_NAME, OS2_EXPORT_NAME_broken);   /* the 'E' from 'NE' */
        expect_tag_skip_range(pattrinfo, 21, 26);
        expect_tag_empty(pattrinfo, 26); /* TAG_VER_LANGUAGE */
        expect_tag_skip(pattrinfo, 27); /* TAG_EXE_WRAPPER */
    }
    if (ret)
        pSdbFreeFileAttributes(pattrinfo);

    test_crc(1, 0);
    test_crc(2, 0);
    test_crc(3, 0);
    test_crc(4, 0x2020202);
    test_crc(5, 0x2020202);
    test_crc(6, 0x2020202);
    test_crc(7, 0x2020202);
    test_crc(8, 0x81818181);
    test_crc(9, 0x81818181);
    test_crc(10, 0x81818181);
    test_crc(11, 0x81818181);
    test_crc(12, 0xc2c2c2c2);
    test_crc(16, 0x62626262);

    /* This seems to be the cutoff point */
    test_crc2(0xffc, 4, 0xfbfbfcfc);
    test_crc2(0xffc, 8, 0x7070717);
    test_crc2(0xffc, 0xcc, 0xc8eba002);
    test_crc2(0xffc, 0, 0x4622028d);

    test_crc2(0x1000, 4, 0x80);
    test_crc2(0x1000, 8, 0x8787878f);
    test_crc2(0x1000, 0xcc, 0x4adc3667);
    test_crc2(0x1000, 0, 0xa3108044);

    /* Here is another cutoff point */
    test_crc2(0x11fc, 4, 0x80);
    test_crc2(0x11fc, 8, 0x8787878f);
    test_crc2(0x11fc, 0xcc, 0x4adc3667);
    test_crc2(0x11fc, 0, 0xf03e0800);

    test_crc2(0x1200, 4, 0x80);
    test_crc2(0x1200, 8, 0x8787878f);
    test_crc2(0x1200, 0xcc, 0x4adc3667);
    test_crc2(0x1200, 0, 0xa3108044);

    /* After that, it stays the same for all sizes */
    test_crc2(0xf000, 4, 0x80);
    test_crc2(0xf000, 8, 0x8787878f);
    test_crc2(0xf000, 0xcc, 0x4adc3667);
    test_crc2(0xf000, 0, 0xa3108044);


    DeleteFileA("testxx.exe");
}