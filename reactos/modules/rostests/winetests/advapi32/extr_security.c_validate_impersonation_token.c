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
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  sil ;
typedef  int TOKEN_TYPE ;
typedef  int /*<<< orphan*/  TOKEN_PRIMARY_GROUP ;
typedef  int /*<<< orphan*/  TOKEN_OWNER ;
typedef  int /*<<< orphan*/  TOKEN_DEFAULT_DACL ;
typedef  int SECURITY_IMPERSONATION_LEVEL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*) ; 
 int SecurityImpersonation ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TokenDefaultDacl ; 
 int TokenImpersonation ; 
 int /*<<< orphan*/  TokenImpersonationLevel ; 
 int /*<<< orphan*/  TokenOwner ; 
 int TokenPrimary ; 
 int /*<<< orphan*/  TokenPrimaryGroup ; 
 int /*<<< orphan*/  TokenType ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static BOOL validate_impersonation_token(HANDLE token, DWORD *token_type)
{
    DWORD ret, needed;
    TOKEN_TYPE type;
    SECURITY_IMPERSONATION_LEVEL sil;

    type = 0xdeadbeef;
    needed = 0;
    SetLastError(0xdeadbeef);
    ret = GetTokenInformation(token, TokenType, &type, sizeof(type), &needed);
    ok(ret, "GetTokenInformation error %d\n", GetLastError());
    ok(needed == sizeof(type), "GetTokenInformation should return required buffer length\n");
    ok(type == TokenPrimary || type == TokenImpersonation, "expected TokenPrimary or TokenImpersonation, got %d\n", type);

    *token_type = type;
    if (type != TokenImpersonation) return FALSE;

    needed = 0;
    SetLastError(0xdeadbeef);
    ret = GetTokenInformation(token, TokenImpersonationLevel, &sil, sizeof(sil), &needed);
    ok(ret, "GetTokenInformation error %d\n", GetLastError());
    ok(needed == sizeof(sil), "GetTokenInformation should return required buffer length\n");
    ok(sil == SecurityImpersonation, "expected SecurityImpersonation, got %d\n", sil);

    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    ret = GetTokenInformation(token, TokenDefaultDacl, NULL, 0, &needed);
    ok(!ret, "GetTokenInformation should fail\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    ok(needed != 0xdeadbeef, "GetTokenInformation should return required buffer length\n");
    ok(needed > sizeof(TOKEN_DEFAULT_DACL), "GetTokenInformation returned empty default DACL\n");

    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    ret = GetTokenInformation(token, TokenOwner, NULL, 0, &needed);
    ok(!ret, "GetTokenInformation should fail\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    ok(needed != 0xdeadbeef, "GetTokenInformation should return required buffer length\n");
    ok(needed > sizeof(TOKEN_OWNER), "GetTokenInformation returned empty token owner\n");

    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    ret = GetTokenInformation(token, TokenPrimaryGroup, NULL, 0, &needed);
    ok(!ret, "GetTokenInformation should fail\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    ok(needed != 0xdeadbeef, "GetTokenInformation should return required buffer length\n");
    ok(needed > sizeof(TOKEN_PRIMARY_GROUP), "GetTokenInformation returned empty token primary group\n");

    return TRUE;
}