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
typedef  int /*<<< orphan*/  targetW ;
typedef  int /*<<< orphan*/  dw ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
struct TYPE_4__ {int Length; char const* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_ALREADY_EXISTS ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_LINK ; 
 int REG_OPTION_CREATE_LINK ; 
 int REG_OPTION_OPEN_LINK ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegOpenKeyExA (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pNtDeleteKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlFormatCurrentUserKeyPath (TYPE_1__*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_symlinks(void)
{
    static const WCHAR targetW[] = {'\\','S','o','f','t','w','a','r','e','\\','W','i','n','e',
                                    '\\','T','e','s','t','\\','t','a','r','g','e','t',0};
    BYTE buffer[1024];
    UNICODE_STRING target_str;
    WCHAR *target;
    HKEY key, link;
    NTSTATUS status;
    DWORD target_len, type, len, dw, err;

    if (!pRtlFormatCurrentUserKeyPath || !pNtDeleteKey)
    {
        win_skip( "Can't perform symlink tests\n" );
        return;
    }

    pRtlFormatCurrentUserKeyPath( &target_str );

    target_len = target_str.Length + sizeof(targetW);
    target = HeapAlloc( GetProcessHeap(), 0, target_len );
    memcpy( target, target_str.Buffer, target_str.Length );
    memcpy( target + target_str.Length/sizeof(WCHAR), targetW, sizeof(targetW) );

    err = RegCreateKeyExA( hkey_main, "link", 0, NULL, REG_OPTION_CREATE_LINK,
                           KEY_ALL_ACCESS, NULL, &link, NULL );
    ok( err == ERROR_SUCCESS, "RegCreateKeyEx failed: %u\n", err );

    /* REG_SZ is not allowed */
    err = RegSetValueExA( link, "SymbolicLinkValue", 0, REG_SZ, (BYTE *)"foobar", sizeof("foobar") );
    ok( err == ERROR_ACCESS_DENIED, "RegSetValueEx wrong error %u\n", err );
    err = RegSetValueExA( link, "SymbolicLinkValue", 0, REG_LINK,
                          (BYTE *)target, target_len - sizeof(WCHAR) );
    ok( err == ERROR_SUCCESS, "RegSetValueEx failed error %u\n", err );
    /* other values are not allowed */
    err = RegSetValueExA( link, "link", 0, REG_LINK, (BYTE *)target, target_len - sizeof(WCHAR) );
    ok( err == ERROR_ACCESS_DENIED, "RegSetValueEx wrong error %u\n", err );

    /* try opening the target through the link */

    err = RegOpenKeyA( hkey_main, "link", &key );
    ok( err == ERROR_FILE_NOT_FOUND, "RegOpenKey wrong error %u\n", err );

    err = RegCreateKeyExA( hkey_main, "target", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &key, NULL );
    ok( err == ERROR_SUCCESS, "RegCreateKeyEx failed error %u\n", err );

    dw = 0xbeef;
    err = RegSetValueExA( key, "value", 0, REG_DWORD, (BYTE *)&dw, sizeof(dw) );
    ok( err == ERROR_SUCCESS, "RegSetValueEx failed error %u\n", err );
    RegCloseKey( key );

    err = RegOpenKeyA( hkey_main, "link", &key );
    ok( err == ERROR_SUCCESS, "RegOpenKey failed error %u\n", err );

    len = sizeof(buffer);
    err = RegQueryValueExA( key, "value", NULL, &type, buffer, &len );
    ok( err == ERROR_SUCCESS, "RegOpenKey failed error %u\n", err );
    ok( len == sizeof(DWORD), "wrong len %u\n", len );

    len = sizeof(buffer);
    err = RegQueryValueExA( key, "SymbolicLinkValue", NULL, &type, buffer, &len );
    ok( err == ERROR_FILE_NOT_FOUND, "RegQueryValueEx wrong error %u\n", err );

    /* REG_LINK can be created in non-link keys */
    err = RegSetValueExA( key, "SymbolicLinkValue", 0, REG_LINK,
                          (BYTE *)target, target_len - sizeof(WCHAR) );
    ok( err == ERROR_SUCCESS, "RegSetValueEx failed error %u\n", err );
    len = sizeof(buffer);
    err = RegQueryValueExA( key, "SymbolicLinkValue", NULL, &type, buffer, &len );
    ok( err == ERROR_SUCCESS, "RegQueryValueEx failed error %u\n", err );
    ok( len == target_len - sizeof(WCHAR), "wrong len %u\n", len );
    err = RegDeleteValueA( key, "SymbolicLinkValue" );
    ok( err == ERROR_SUCCESS, "RegDeleteValue failed error %u\n", err );

    RegCloseKey( key );

    err = RegCreateKeyExA( hkey_main, "link", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &key, NULL );
    ok( err == ERROR_SUCCESS, "RegCreateKeyEx failed error %u\n", err );

    len = sizeof(buffer);
    err = RegQueryValueExA( key, "value", NULL, &type, buffer, &len );
    ok( err == ERROR_SUCCESS, "RegQueryValueEx failed error %u\n", err );
    ok( len == sizeof(DWORD), "wrong len %u\n", len );

    err = RegQueryValueExA( key, "SymbolicLinkValue", NULL, &type, buffer, &len );
    ok( err == ERROR_FILE_NOT_FOUND, "RegQueryValueEx wrong error %u\n", err );
    RegCloseKey( key );

    /* now open the symlink itself */

    err = RegOpenKeyExA( hkey_main, "link", REG_OPTION_OPEN_LINK, KEY_ALL_ACCESS, &key );
    ok( err == ERROR_SUCCESS, "RegOpenKeyEx failed error %u\n", err );
    len = sizeof(buffer);
    err = RegQueryValueExA( key, "SymbolicLinkValue", NULL, &type, buffer, &len );
    ok( err == ERROR_SUCCESS, "RegQueryValueEx failed error %u\n", err );
    ok( len == target_len - sizeof(WCHAR), "wrong len %u\n", len );
    RegCloseKey( key );

    err = RegCreateKeyExA( hkey_main, "link", 0, NULL, REG_OPTION_OPEN_LINK,
                           KEY_ALL_ACCESS, NULL, &key, NULL );
    ok( err == ERROR_SUCCESS, "RegCreateKeyEx failed error %u\n", err );
    len = sizeof(buffer);
    err = RegQueryValueExA( key, "SymbolicLinkValue", NULL, &type, buffer, &len );
    ok( err == ERROR_SUCCESS, "RegQueryValueEx failed error %u\n", err );
    ok( len == target_len - sizeof(WCHAR), "wrong len %u\n", len );
    RegCloseKey( key );

    err = RegCreateKeyExA( hkey_main, "link", 0, NULL, REG_OPTION_CREATE_LINK,
                           KEY_ALL_ACCESS, NULL, &key, NULL );
    ok( err == ERROR_ALREADY_EXISTS, "RegCreateKeyEx wrong error %u\n", err );

    err = RegCreateKeyExA( hkey_main, "link", 0, NULL, REG_OPTION_CREATE_LINK | REG_OPTION_OPEN_LINK,
                           KEY_ALL_ACCESS, NULL, &key, NULL );
    ok( err == ERROR_ALREADY_EXISTS, "RegCreateKeyEx wrong error %u\n", err );

    err = RegDeleteKeyA( hkey_main, "target" );
    ok( err == ERROR_SUCCESS, "RegDeleteKey failed error %u\n", err );

    err = RegDeleteKeyA( hkey_main, "link" );
    ok( err == ERROR_FILE_NOT_FOUND, "RegDeleteKey wrong error %u\n", err );

    status = pNtDeleteKey( link );
    ok( !status, "NtDeleteKey failed: 0x%08x\n", status );
    RegCloseKey( link );

    HeapFree( GetProcessHeap(), 0, target );
    pRtlFreeUnicodeString( &target_str );
}