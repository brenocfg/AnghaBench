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
typedef  int /*<<< orphan*/  utf16_test ;
typedef  int /*<<< orphan*/  buf ;
typedef  unsigned char WCHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int fscanf (int /*<<< orphan*/ *,char*,char*) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int fwprintf (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  memcmp (char*,...) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 char* wine_dbgstr_w (unsigned char*) ; 

__attribute__((used)) static void test_fprintf(void)
{
    static const char file_name[] = "fprintf.tst";
    static const WCHAR utf16_test[] = {'u','n','i','c','o','d','e','\n',0};

    FILE *fp = fopen(file_name, "wb");
    char buf[1024];
    int ret;

    ret = fprintf(fp, "simple test\n");
    ok(ret == 12, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 12, "ftell returned %d\n", ret);

    ret = fprintf(fp, "contains%cnull\n", '\0');
    ok(ret == 14, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 26, "ftell returned %d\n", ret);

    ret = fwprintf(fp, utf16_test);
    ok(ret == 8, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 42, "ftell returned %d\n", ret);

    fclose(fp);

    fp = fopen(file_name, "rb");
    ret = fscanf(fp, "%[^\n] ", buf);
    ok(ret == 1, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 12, "ftell returned %d\n", ret);
    ok(!strcmp(buf, "simple test"), "buf = %s\n", buf);

    fgets(buf, sizeof(buf), fp);
    ret = ftell(fp);
    ok(ret == 26, "ret = %d\n", ret);
    ok(!memcmp(buf, "contains\0null\n", 14), "buf = %s\n", buf);

    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp);
    ret = ftell(fp);
    ok(ret == 41, "ret =  %d\n", ret);
    ok(!memcmp(buf, utf16_test, sizeof(utf16_test)),
            "buf = %s\n", wine_dbgstr_w((WCHAR*)buf));

    fclose(fp);

    fp = fopen(file_name, "wt");

    ret = fprintf(fp, "simple test\n");
    ok(ret == 12, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 13, "ftell returned %d\n", ret);

    ret = fprintf(fp, "contains%cnull\n", '\0');
    ok(ret == 14, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 28, "ftell returned %d\n", ret);

    ret = fwprintf(fp, utf16_test);
    ok(ret == 8, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 37, "ftell returned %d\n", ret);

    fclose(fp);

    fp = fopen(file_name, "rb");
    ret = fscanf(fp, "%[^\n] ", buf);
    ok(ret == 1, "ret = %d\n", ret);
    ret = ftell(fp);
    ok(ret == 13, "ftell returned %d\n", ret);
    ok(!strcmp(buf, "simple test\r"), "buf = %s\n", buf);

    fgets(buf, sizeof(buf), fp);
    ret = ftell(fp);
    ok(ret == 28, "ret = %d\n", ret);
    ok(!memcmp(buf, "contains\0null\r\n", 15), "buf = %s\n", buf);

    fgets(buf, sizeof(buf), fp);
    ret = ftell(fp);
    ok(ret == 37, "ret =  %d\n", ret);
    ok(!strcmp(buf, "unicode\r\n"), "buf = %s\n", buf);

    fclose(fp);
    unlink(file_name);
}