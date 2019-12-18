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
typedef  int /*<<< orphan*/  passwordW ;
typedef  unsigned char WCHAR ;
typedef  int ULONG ;
typedef  void UCHAR ;
typedef  int SECURITY_STATUS ;
typedef  int /*<<< orphan*/  PSEC_WINNT_AUTH_IDENTITY_OPAQUE ;

/* Variables and functions */
 int CRED_TYPE_DOMAIN_PASSWORD ; 
 int SEC_E_OK ; 
 int /*<<< orphan*/  lstrcmpW (unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  memcmp (void*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pSspiEncodeStringsAsAuthIdentity (unsigned char const*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pSspiFreeAuthIdentity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSspiLocalFree (void*) ; 
 int pSspiPrepareForCredWrite (int /*<<< orphan*/ ,unsigned char const*,int*,unsigned char const**,unsigned char const**,void**,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (unsigned char const*) ; 

__attribute__((used)) static void test_SspiPrepareForCredWrite(void)
{
    static const WCHAR usernameW[] =
        {'u','s','e','r','n','a','m','e',0};
    static const WCHAR domainnameW[] =
        {'d','o','m','a','i','n','n','a','m','e',0};
    static const WCHAR passwordW[] =
        {'p','a','s','s','w','o','r','d',0};
    static const WCHAR targetW[] =
        {'d','o','m','a','i','n','n','a','m','e','\\','u','s','e','r','n','a','m','e',0};
    static const WCHAR target2W[] =
        {'d','o','m','a','i','n','n','a','m','e','2','\\','u','s','e','r','n','a','m','e','2',0};
    const WCHAR *target, *username;
    PSEC_WINNT_AUTH_IDENTITY_OPAQUE id;
    SECURITY_STATUS status;
    ULONG type, size;
    UCHAR *blob;

    if (!pSspiPrepareForCredWrite)
    {
        win_skip( "SspiPrepareForCredWrite not exported by secur32.dll\n" );
        return;
    }

    status = pSspiEncodeStringsAsAuthIdentity( usernameW, domainnameW, passwordW, &id );
    ok( status == SEC_E_OK, "got %08x\n", status );

    type = size = 0;
    status = pSspiPrepareForCredWrite( id, NULL, &type, &target, &username, &blob, &size );
    ok( status == SEC_E_OK, "got %08x\n", status );
    ok( type == CRED_TYPE_DOMAIN_PASSWORD, "got %u\n", type );
    ok( !lstrcmpW( target, targetW ), "got %s\n", wine_dbgstr_w(target) );
    ok( !lstrcmpW( username, targetW ), "got %s\n", wine_dbgstr_w(username) );
    ok( !memcmp( blob, passwordW, sizeof(passwordW) - sizeof(WCHAR) ), "wrong data\n" );
    ok( size == sizeof(passwordW) - sizeof(WCHAR), "got %u\n", size );
    pSspiLocalFree( (void *)target );
    pSspiLocalFree( (void *)username );
    pSspiLocalFree( blob );

    type = size = 0;
    status = pSspiPrepareForCredWrite( id, target2W, &type, &target, &username, &blob, &size );
    ok( status == SEC_E_OK, "got %08x\n", status );
    ok( type == CRED_TYPE_DOMAIN_PASSWORD, "got %u\n", type );
    ok( !lstrcmpW( target, target2W ), "got %s\n", wine_dbgstr_w(target) );
    ok( !lstrcmpW( username, targetW ), "got %s\n", wine_dbgstr_w(username) );
    ok( !memcmp( blob, passwordW, sizeof(passwordW) - sizeof(WCHAR) ), "wrong data\n" );
    ok( size == sizeof(passwordW) - sizeof(WCHAR), "got %u\n", size );
    pSspiLocalFree( (void *)target );
    pSspiLocalFree( (void *)username );
    pSspiLocalFree( blob );

    pSspiFreeAuthIdentity( id );
}