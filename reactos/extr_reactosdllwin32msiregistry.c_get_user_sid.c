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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_7__ {TYPE_1__ User; } ;
typedef  TYPE_2__ TOKEN_USER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConvertSidToStringSidW (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  TokenUser ; 
 TYPE_2__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 

__attribute__((used)) static WCHAR *get_user_sid(void)
{
    HANDLE token;
    DWORD size = 256;
    TOKEN_USER *user;
    WCHAR *ret;

    if (!OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &token )) return NULL;
    if (!(user = msi_alloc( size )))
    {
        CloseHandle( token );
        return NULL;
    }
    if (!GetTokenInformation( token, TokenUser, user, size, &size ))
    {
        msi_free( user );
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || !(user = msi_alloc( size )))
        {
            CloseHandle( token );
            return NULL;
        }
        GetTokenInformation( token, TokenUser, user, size, &size );
    }
    CloseHandle( token );
    if (!ConvertSidToStringSidW( user->User.Sid, &ret ))
    {
        msi_free( user );
        return NULL;
    }
    msi_free( user );
    return ret;
}