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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ RPC_STATUS ;
typedef  scalar_t__ RPC_CSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetUserNameExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NameSamCompatible ; 
 int /*<<< orphan*/  RPC_C_AUTHN_DEFAULT ; 
 int /*<<< orphan*/  RPC_C_AUTHN_WINNT ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_UNKNOWN_AUTHN_SERVICE ; 
 scalar_t__ RpcServerInqDefaultPrincNameA (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RpcServerRegisterAuthInfoA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcStringFreeA (scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void test_RpcServerInqDefaultPrincName(void)
{
    RPC_STATUS ret;
    RPC_CSTR principal, saved_principal;
    char *username;
    ULONG len = 0;

    GetUserNameExA( NameSamCompatible, NULL, &len );
    username = HeapAlloc( GetProcessHeap(), 0, len );
    GetUserNameExA( NameSamCompatible, username, &len );

    ret = RpcServerInqDefaultPrincNameA( 0, NULL );
    ok( ret == RPC_S_UNKNOWN_AUTHN_SERVICE, "got %u\n", ret );

    ret = RpcServerInqDefaultPrincNameA( RPC_C_AUTHN_DEFAULT, NULL );
    ok( ret == RPC_S_UNKNOWN_AUTHN_SERVICE, "got %u\n", ret );

    principal = (RPC_CSTR)0xdeadbeef;
    ret = RpcServerInqDefaultPrincNameA( RPC_C_AUTHN_DEFAULT, &principal );
    ok( ret == RPC_S_UNKNOWN_AUTHN_SERVICE, "got %u\n", ret );
    ok( principal == (RPC_CSTR)0xdeadbeef, "got unexpected principal\n" );

    saved_principal = (RPC_CSTR)0xdeadbeef;
    ret = RpcServerInqDefaultPrincNameA( RPC_C_AUTHN_WINNT, &saved_principal );
    ok( ret == RPC_S_OK, "got %u\n", ret );
    ok( saved_principal != (RPC_CSTR)0xdeadbeef, "expected valid principal\n" );
    ok( !strcmp( (const char *)saved_principal, username ), "got \'%s\'\n", saved_principal );
    trace("%s\n", saved_principal);

    ret = RpcServerRegisterAuthInfoA( (RPC_CSTR)"wine\\test", RPC_C_AUTHN_WINNT, NULL, NULL );
    ok( ret == RPC_S_OK, "got %u\n", ret );

    principal = (RPC_CSTR)0xdeadbeef;
    ret = RpcServerInqDefaultPrincNameA( RPC_C_AUTHN_WINNT, &principal );
    ok( ret == RPC_S_OK, "got %u\n", ret );
    ok( principal != (RPC_CSTR)0xdeadbeef, "expected valid principal\n" );
    ok( !strcmp( (const char *)principal, username ), "got \'%s\'\n", principal );
    RpcStringFreeA( &principal );

    ret = RpcServerRegisterAuthInfoA( saved_principal, RPC_C_AUTHN_WINNT, NULL, NULL );
    ok( ret == RPC_S_OK, "got %u\n", ret );

    RpcStringFreeA( &saved_principal );
    HeapFree( GetProcessHeap(), 0, username );
}