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
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  LSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  size_t DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegEnumValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t*) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t*) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  hkey_main ; 
 scalar_t__ memcmp (int*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  wine_debugstr_an (char*,size_t) ; 

__attribute__((used)) static void test_string_termination(void)
{
    HKEY subkey;
    LSTATUS ret;
    static const char string[] = "FullString";
    char name[11];
    BYTE buffer[11];
    DWORD insize, outsize, nsize;

    ret = RegCreateKeyA(hkey_main, "string_termination", &subkey);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    /* Off-by-one RegSetValueExA -> adds a trailing '\0'! */
    insize=sizeof(string)-1;
    ret = RegSetValueExA(subkey, "stringtest", 0, REG_SZ, (BYTE*)string, insize);
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d\n", ret);
    outsize=insize;
    ret = RegQueryValueExA(subkey, "stringtest", NULL, NULL, buffer, &outsize);
    ok(ret == ERROR_MORE_DATA, "RegQueryValueExA returned: %d\n", ret);

    /* Off-by-two RegSetValueExA -> no trailing '\0' */
    insize=sizeof(string)-2;
    ret = RegSetValueExA(subkey, "stringtest", 0, REG_SZ, (BYTE*)string, insize);
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d\n", ret);
    outsize=0;
    ret = RegQueryValueExA(subkey, "stringtest", NULL, NULL, NULL, &outsize);
    ok(ret == ERROR_SUCCESS, "RegQueryValueExA failed: %d\n", ret);
    ok(outsize == insize, "wrong size %u != %u\n", outsize, insize);

    /* RegQueryValueExA may return a string with no trailing '\0' */
    outsize=insize;
    memset(buffer, 0xbd, sizeof(buffer));
    ret = RegQueryValueExA(subkey, "stringtest", NULL, NULL, buffer, &outsize);
    ok(ret == ERROR_SUCCESS, "RegQueryValueExA failed: %d\n", ret);
    ok(outsize == insize, "wrong size: %u != %u\n", outsize, insize);
    ok(memcmp(buffer, string, outsize) == 0, "bad string: %s/%u != %s\n",
       wine_debugstr_an((char*)buffer, outsize), outsize, string);
    ok(buffer[insize] == 0xbd, "buffer overflow at %u %02x\n", insize, buffer[insize]);

    /* RegQueryValueExA adds a trailing '\0' if there is room */
    outsize=insize+1;
    memset(buffer, 0xbd, sizeof(buffer));
    ret = RegQueryValueExA(subkey, "stringtest", NULL, NULL, buffer, &outsize);
    ok(ret == ERROR_SUCCESS, "RegQueryValueExA failed: %d\n", ret);
    ok(outsize == insize, "wrong size: %u != %u\n", outsize, insize);
    ok(memcmp(buffer, string, outsize) == 0, "bad string: %s/%u != %s\n",
       wine_debugstr_an((char*)buffer, outsize), outsize, string);
    ok(buffer[insize] == 0, "buffer overflow at %u %02x\n", insize, buffer[insize]);

    /* RegEnumValueA may return a string with no trailing '\0' */
    outsize=insize;
    memset(buffer, 0xbd, sizeof(buffer));
    nsize=sizeof(name);
    ret = RegEnumValueA(subkey, 0, name, &nsize, NULL, NULL, buffer, &outsize);
    ok(ret == ERROR_SUCCESS, "RegEnumValueA failed: %d\n", ret);
    ok(strcmp(name, "stringtest") == 0, "wrong name: %s\n", name);
    ok(outsize == insize, "wrong size: %u != %u\n", outsize, insize);
    ok(memcmp(buffer, string, outsize) == 0, "bad string: %s/%u != %s\n",
       wine_debugstr_an((char*)buffer, outsize), outsize, string);
    ok(buffer[insize] == 0xbd, "buffer overflow at %u %02x\n", insize, buffer[insize]);

    /* RegEnumValueA adds a trailing '\0' if there is room */
    outsize=insize+1;
    memset(buffer, 0xbd, sizeof(buffer));
    nsize=sizeof(name);
    ret = RegEnumValueA(subkey, 0, name, &nsize, NULL, NULL, buffer, &outsize);
    ok(ret == ERROR_SUCCESS, "RegEnumValueA failed: %d\n", ret);
    ok(strcmp(name, "stringtest") == 0, "wrong name: %s\n", name);
    ok(outsize == insize, "wrong size: %u != %u\n", outsize, insize);
    ok(memcmp(buffer, string, outsize) == 0, "bad string: %s/%u != %s\n",
       wine_debugstr_an((char*)buffer, outsize), outsize, string);
    ok(buffer[insize] == 0, "buffer overflow at %u %02x\n", insize, buffer[insize]);

    RegDeleteKeyA(subkey, "");
    RegCloseKey(subkey);
}