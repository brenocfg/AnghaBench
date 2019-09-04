#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_7__ {TYPE_1__ User; } ;
typedef  TYPE_2__ TOKEN_USER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/  pConvertSidToStringSidA (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static char *get_user_sid(void)
{
    HANDLE token;
    DWORD size = 0;
    TOKEN_USER *user;
    char *usersid = NULL;

    OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token);
    GetTokenInformation(token, TokenUser, NULL, size, &size);

    user = HeapAlloc(GetProcessHeap(), 0, size);
    GetTokenInformation(token, TokenUser, user, size, &size);
    pConvertSidToStringSidA(user->User.Sid, &usersid);
    HeapFree(GetProcessHeap(), 0, user);

    CloseHandle(token);
    return usersid;
}