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
typedef  int /*<<< orphan*/  buf ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ERROR_DATATYPE_MISMATCH ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNSUPPORTED_TYPE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int REG_BINARY ; 
 int REG_DWORD ; 
 int REG_EXPAND_SZ ; 
 int REG_SZ ; 
 int RRF_NOEXPAND ; 
 int RRF_RT_ANY ; 
 int RRF_RT_DWORD ; 
 int RRF_RT_QWORD ; 
 int RRF_RT_REG_BINARY ; 
 int RRF_RT_REG_DWORD ; 
 int RRF_RT_REG_EXPAND_SZ ; 
 int RRF_RT_REG_SZ ; 
 int RRF_ZEROONFAILURE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pRegGetValueA (int /*<<< orphan*/ ,char*,char*,int,int*,...) ; 
 char* sTestpath1 ; 
 char* sTestpath2 ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_get_value(void)
{
    DWORD ret;
    DWORD size;
    DWORD type;
    DWORD dw, qw[2];
    CHAR buf[80];
    CHAR expanded[] = "bar\\subdir1";
    CHAR expanded2[] = "ImARatherLongButIndeedNeededString\\subdir1";
   
    if(!pRegGetValueA)
    {
        win_skip("RegGetValue not available on this platform\n");
        return;
    }

    /* Invalid parameter */
    ret = pRegGetValueA(hkey_main, NULL, "DWORD", RRF_RT_REG_DWORD, &type, &dw, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "ret=%d\n", ret);

    /* Query REG_DWORD using RRF_RT_REG_DWORD (ok) */
    size = type = dw = 0xdeadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "DWORD", RRF_RT_REG_DWORD, &type, &dw, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == 4, "size=%d\n", size);
    ok(type == REG_DWORD, "type=%d\n", type);
    ok(dw == 0x12345678, "dw=%d\n", dw);

    /* Query by subkey-name */
    ret = pRegGetValueA(HKEY_CURRENT_USER, "Software\\Wine\\Test", "DWORD", RRF_RT_REG_DWORD, NULL, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);

    /* Query REG_DWORD using RRF_RT_REG_BINARY (restricted) */
    size = type = dw = 0xdeadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "DWORD", RRF_RT_REG_BINARY, &type, &dw, &size);
    ok(ret == ERROR_UNSUPPORTED_TYPE, "ret=%d\n", ret);
    /* Although the function failed all values are retrieved */
    ok(size == 4, "size=%d\n", size);
    ok(type == REG_DWORD, "type=%d\n", type);
    ok(dw == 0x12345678, "dw=%d\n", dw);

    /* Test RRF_ZEROONFAILURE */
    type = dw = 0xdeadbeef; size = 4;
    ret = pRegGetValueA(hkey_main, NULL, "DWORD", RRF_RT_REG_SZ|RRF_ZEROONFAILURE, &type, &dw, &size);
    ok(ret == ERROR_UNSUPPORTED_TYPE, "ret=%d\n", ret);
    /* Again all values are retrieved ... */
    ok(size == 4, "size=%d\n", size);
    ok(type == REG_DWORD, "type=%d\n", type);
    /* ... except the buffer, which is zeroed out */
    ok(dw == 0, "dw=%d\n", dw);

    /* Test RRF_ZEROONFAILURE with a NULL buffer... */
    type = size = 0xbadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "DWORD", RRF_RT_REG_SZ|RRF_ZEROONFAILURE, &type, NULL, &size);
    ok(ret == ERROR_UNSUPPORTED_TYPE, "ret=%d\n", ret);
    ok(size == 4, "size=%d\n", size);
    ok(type == REG_DWORD, "type=%d\n", type);

    /* Query REG_DWORD using RRF_RT_DWORD (ok) */
    size = type = dw = 0xdeadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "DWORD", RRF_RT_DWORD, &type, &dw, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == 4, "size=%d\n", size);
    ok(type == REG_DWORD, "type=%d\n", type);
    ok(dw == 0x12345678, "dw=%d\n", dw);

    /* Query 32-bit REG_BINARY using RRF_RT_DWORD (ok) */
    size = type = dw = 0xdeadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "BIN32", RRF_RT_DWORD, &type, &dw, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == 4, "size=%d\n", size);
    ok(type == REG_BINARY, "type=%d\n", type);
    ok(dw == 0x12345678, "dw=%d\n", dw);
    
    /* Query 64-bit REG_BINARY using RRF_RT_DWORD (type mismatch) */
    qw[0] = qw[1] = size = type = 0xdeadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "BIN64", RRF_RT_DWORD, &type, qw, &size);
    ok(ret == ERROR_DATATYPE_MISMATCH, "ret=%d\n", ret);
    ok(size == 8, "size=%d\n", size);
    ok(type == REG_BINARY, "type=%d\n", type);
    ok(qw[0] == 0x12345678 && 
       qw[1] == 0x87654321, "qw={%d,%d}\n", qw[0], qw[1]);
    
    /* Query 64-bit REG_BINARY using 32-bit buffer (buffer too small) */
    type = dw = 0xdeadbeef; size = 4;
    ret = pRegGetValueA(hkey_main, NULL, "BIN64", RRF_RT_REG_BINARY, &type, &dw, &size);
    ok(ret == ERROR_MORE_DATA, "ret=%d\n", ret);
    ok(dw == 0xdeadbeef, "dw=%d\n", dw);
    ok(size == 8, "size=%d\n", size);

    /* Query 64-bit REG_BINARY using RRF_RT_QWORD (ok) */
    qw[0] = qw[1] = size = type = 0xdeadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "BIN64", RRF_RT_QWORD, &type, qw, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == 8, "size=%d\n", size);
    ok(type == REG_BINARY, "type=%d\n", type);
    ok(qw[0] == 0x12345678 &&
       qw[1] == 0x87654321, "qw={%d,%d}\n", qw[0], qw[1]);

    /* Query REG_SZ using RRF_RT_REG_SZ (ok) */
    buf[0] = 0; type = 0xdeadbeef; size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP1_SZ", RRF_RT_REG_SZ, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == strlen(sTestpath1)+1, "strlen(sTestpath1)=%d size=%d\n", lstrlenA(sTestpath1), size);
    ok(type == REG_SZ, "type=%d\n", type);
    ok(!strcmp(sTestpath1, buf), "sTestpath=\"%s\" buf=\"%s\"\n", sTestpath1, buf);

    /* Query REG_SZ using RRF_RT_REG_SZ and no buffer (ok) */
    type = 0xdeadbeef; size = 0;
    ret = pRegGetValueA(hkey_main, NULL, "TP1_SZ", RRF_RT_REG_SZ, &type, NULL, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    /* v5.2.3790.1830 (2003 SP1) returns sTestpath1 length + 2 here. */
    ok(size == strlen(sTestpath1)+1 || broken(size == strlen(sTestpath1)+2),
       "strlen(sTestpath1)=%d size=%d\n", lstrlenA(sTestpath1), size);
    ok(type == REG_SZ, "type=%d\n", type);

    /* Query REG_SZ using RRF_RT_REG_SZ on a zero-byte value (ok) */
    strcpy(buf, sTestpath1);
    type = 0xdeadbeef;
    size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP1_ZB_SZ", RRF_RT_REG_SZ, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    /* v5.2.3790.1830 (2003 SP1) returns sTestpath1 length + 2 here. */
    ok(size == 0 ||
       size == 1, /* win2k3 */
       "size=%d\n", size);
    ok(type == REG_SZ, "type=%d\n", type);
    ok(!strcmp(sTestpath1, buf) ||
       !strcmp(buf, ""),
       "Expected \"%s\" or \"\", got \"%s\"\n", sTestpath1, buf);

    /* Query REG_SZ using RRF_RT_REG_SZ|RRF_NOEXPAND (ok) */
    buf[0] = 0; type = 0xdeadbeef; size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP1_SZ", RRF_RT_REG_SZ|RRF_NOEXPAND, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == strlen(sTestpath1)+1, "strlen(sTestpath1)=%d size=%d\n", lstrlenA(sTestpath1), size);
    ok(type == REG_SZ, "type=%d\n", type);
    ok(!strcmp(sTestpath1, buf), "sTestpath=\"%s\" buf=\"%s\"\n", sTestpath1, buf);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_SZ and no buffer (ok, expands) */
    size = 0;
    ret = pRegGetValueA(hkey_main, NULL, "TP2_EXP_SZ", RRF_RT_REG_SZ, NULL, NULL, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok((size == strlen(expanded2)+1) || /* win2k3 SP1 */
       (size == strlen(expanded2)+2) || /* win2k3 SP2 */
       (size == strlen(sTestpath2)+1),
        "strlen(expanded2)=%d, strlen(sTestpath2)=%d, size=%d\n", lstrlenA(expanded2), lstrlenA(sTestpath2), size);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_SZ (ok, expands) */
    buf[0] = 0; type = 0xdeadbeef; size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP1_EXP_SZ", RRF_RT_REG_SZ, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    /* At least v5.2.3790.1830 (2003 SP1) returns the unexpanded sTestpath1 length + 1 here. */
    ok(size == strlen(expanded)+1 || broken(size == strlen(sTestpath1)+1),
        "strlen(expanded)=%d, strlen(sTestpath1)=%d, size=%d\n", lstrlenA(expanded), lstrlenA(sTestpath1), size);
    ok(type == REG_SZ, "type=%d\n", type);
    ok(!strcmp(expanded, buf), "expanded=\"%s\" buf=\"%s\"\n", expanded, buf);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_SZ (ok, expands a lot) */
    buf[0] = 0; type = 0xdeadbeef; size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP2_EXP_SZ", RRF_RT_REG_SZ, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    /* At least v5.2.3790.1830 (2003 SP1) returns the unexpanded sTestpath2 length + 1 here. */
    ok(size == strlen(expanded2)+1 || broken(size == strlen(sTestpath2)+1),
        "strlen(expanded2)=%d, strlen(sTestpath1)=%d, size=%d\n", lstrlenA(expanded2), lstrlenA(sTestpath2), size);
    ok(type == REG_SZ, "type=%d\n", type);
    ok(!strcmp(expanded2, buf), "expanded2=\"%s\" buf=\"%s\"\n", expanded2, buf);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_EXPAND_SZ|RRF_NOEXPAND (ok, doesn't expand) */
    buf[0] = 0; type = 0xdeadbeef; size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP1_EXP_SZ", RRF_RT_REG_EXPAND_SZ|RRF_NOEXPAND, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    ok(size == strlen(sTestpath1)+1, "strlen(sTestpath1)=%d size=%d\n", lstrlenA(sTestpath1), size);
    ok(type == REG_EXPAND_SZ, "type=%d\n", type);
    ok(!strcmp(sTestpath1, buf), "sTestpath=\"%s\" buf=\"%s\"\n", sTestpath1, buf);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_EXPAND_SZ|RRF_NOEXPAND and no buffer (ok, doesn't expand) */
    size = 0xbadbeef;
    ret = pRegGetValueA(hkey_main, NULL, "TP1_EXP_SZ", RRF_RT_REG_EXPAND_SZ|RRF_NOEXPAND, NULL, NULL, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    /* v5.2.3790.1830 (2003 SP1) returns sTestpath1 length + 2 here. */
    ok(size == strlen(sTestpath1)+1 || broken(size == strlen(sTestpath1)+2),
       "strlen(sTestpath1)=%d size=%d\n", lstrlenA(sTestpath1), size);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_SZ|RRF_NOEXPAND (type mismatch) */
    ret = pRegGetValueA(hkey_main, NULL, "TP1_EXP_SZ", RRF_RT_REG_SZ|RRF_NOEXPAND, NULL, NULL, NULL);
    ok(ret == ERROR_UNSUPPORTED_TYPE, "ret=%d\n", ret);

    /* Query REG_EXPAND_SZ using RRF_RT_REG_EXPAND_SZ (not allowed without RRF_NOEXPAND) */
    ret = pRegGetValueA(hkey_main, NULL, "TP1_EXP_SZ", RRF_RT_REG_EXPAND_SZ, NULL, NULL, NULL);
    /* before win8: ERROR_INVALID_PARAMETER, win8: ERROR_UNSUPPORTED_TYPE */
    ok(ret == ERROR_INVALID_PARAMETER || ret == ERROR_UNSUPPORTED_TYPE, "ret=%d\n", ret);

    /* Query REG_EXPAND_SZ using RRF_RT_ANY */
    buf[0] = 0; type = 0xdeadbeef; size = sizeof(buf);
    ret = pRegGetValueA(hkey_main, NULL, "TP1_EXP_SZ", RRF_RT_ANY, &type, buf, &size);
    ok(ret == ERROR_SUCCESS, "ret=%d\n", ret);
    /* At least v5.2.3790.1830 (2003 SP1) returns the unexpanded sTestpath1 length + 1 here. */
    ok(size == strlen(expanded)+1 || broken(size == strlen(sTestpath1)+1),
        "strlen(expanded)=%d, strlen(sTestpath1)=%d, size=%d\n", lstrlenA(expanded), lstrlenA(sTestpath1), size);
    ok(type == REG_SZ, "type=%d\n", type);
    ok(!strcmp(expanded, buf), "expanded=\"%s\" buf=\"%s\"\n", expanded, buf);
}