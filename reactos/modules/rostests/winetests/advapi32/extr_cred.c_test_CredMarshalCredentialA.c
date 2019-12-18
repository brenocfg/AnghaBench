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
typedef  int /*<<< orphan*/  cert ;
typedef  char WCHAR ;
struct TYPE_4__ {int* rgbHashOfCert; int cbSize; char* UserName; } ;
typedef  TYPE_1__ USERNAME_TARGET_CREDENTIAL_INFO ;
typedef  char* DWORD ;
typedef  TYPE_1__ CERT_CREDENTIAL_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CertCredential ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  UsernameTargetCredential ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCredFree (char*) ; 
 int pCredMarshalCredentialA (int /*<<< orphan*/ ,TYPE_1__*,char**) ; 

__attribute__((used)) static void test_CredMarshalCredentialA(void)
{
    static WCHAR emptyW[] = {0};
    static WCHAR tW[] = {'t',0};
    static WCHAR teW[] = {'t','e',0};
    static WCHAR tesW[] = {'t','e','s',0};
    static WCHAR testW[] = {'t','e','s','t',0};
    static WCHAR test1W[] = {'t','e','s','t','1',0};
    CERT_CREDENTIAL_INFO cert;
    USERNAME_TARGET_CREDENTIAL_INFO username;
    DWORD error;
    char *str;
    BOOL ret;

    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( 0, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    memset( cert.rgbHashOfCert, 0, sizeof(cert.rgbHashOfCert) );
    cert.cbSize = sizeof(cert);
    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( 0, &cert, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    str = (char *)0xdeadbeef;
    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( 0, &cert, &str );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );
    ok( str == (char *)0xdeadbeef, "got %p\n", str );

    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( CertCredential, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    if (0) { /* crash */
    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( CertCredential, &cert, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );
    }

    cert.cbSize = 0;
    str = (char *)0xdeadbeef;
    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );
    ok( str == (char *)0xdeadbeef, "got %p\n", str );

    cert.cbSize = sizeof(cert) + 4;
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@BAAAAAAAAAAAAAAAAAAAAAAAAAAA" ), "got %s\n", str );
    pCredFree( str );

    cert.cbSize = sizeof(cert);
    cert.rgbHashOfCert[0] = 2;
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@BCAAAAAAAAAAAAAAAAAAAAAAAAAA" ), "got %s\n", str );
    pCredFree( str );

    cert.rgbHashOfCert[0] = 255;
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@B-DAAAAAAAAAAAAAAAAAAAAAAAAA" ), "got %s\n", str );
    pCredFree( str );

    cert.rgbHashOfCert[0] = 1;
    cert.rgbHashOfCert[1] = 1;
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@BBEAAAAAAAAAAAAAAAAAAAAAAAAA" ), "got %s\n", str );
    pCredFree( str );

    cert.rgbHashOfCert[0] = 1;
    cert.rgbHashOfCert[1] = 1;
    cert.rgbHashOfCert[2] = 1;
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@BBEQAAAAAAAAAAAAAAAAAAAAAAAA" ), "got %s\n", str );
    pCredFree( str );

    memset( cert.rgbHashOfCert, 0, sizeof(cert.rgbHashOfCert) );
    cert.rgbHashOfCert[0] = 'W';
    cert.rgbHashOfCert[1] = 'i';
    cert.rgbHashOfCert[2] = 'n';
    cert.rgbHashOfCert[3] = 'e';
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@BXlmblBAAAAAAAAAAAAAAAAAAAAA" ), "got %s\n", str );
    pCredFree( str );

    memset( cert.rgbHashOfCert, 0xff, sizeof(cert.rgbHashOfCert) );
    str = NULL;
    ret = pCredMarshalCredentialA( CertCredential, &cert, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@B--------------------------P" ), "got %s\n", str );
    pCredFree( str );

    username.UserName = NULL;
    str = (char *)0xdeadbeef;
    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );
    ok( str == (char *)0xdeadbeef, "got %p\n", str );

    username.UserName = emptyW;
    str = (char *)0xdeadbeef;
    SetLastError( 0xdeadbeef );
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );
    ok( str == (char *)0xdeadbeef, "got %p\n", str );

    username.UserName = tW;
    str = NULL;
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@CCAAAAA0BA" ), "got %s\n", str );
    pCredFree( str );

    username.UserName = teW;
    str = NULL;
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@CEAAAAA0BQZAA" ), "got %s\n", str );
    pCredFree( str );

    username.UserName = tesW;
    str = NULL;
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@CGAAAAA0BQZAMHA" ), "got %s\n", str );
    pCredFree( str );

    username.UserName = testW;
    str = NULL;
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@CIAAAAA0BQZAMHA0BA" ), "got %s\n", str );
    pCredFree( str );

    username.UserName = test1W;
    str = NULL;
    ret = pCredMarshalCredentialA( UsernameTargetCredential, &username, &str );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( str != NULL, "str not set\n" );
    ok( !lstrcmpA( str, "@@CKAAAAA0BQZAMHA0BQMAA" ), "got %s\n", str );
    pCredFree( str );
}