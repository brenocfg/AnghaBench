#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  char WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int cbSize; char const* pszMessageText; char const* pszCaptionText; int /*<<< orphan*/ * hbmBanner; int /*<<< orphan*/ * hwndParent; } ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  int /*<<< orphan*/ * PSEC_WINNT_AUTH_IDENTITY_OPAQUE ;
typedef  TYPE_1__ CREDUI_INFOW ;

/* Variables and functions */
 scalar_t__ ERROR_CANCELLED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NO_SUCH_PACKAGE ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSspiEncodeAuthIdentityAsStrings (int /*<<< orphan*/ *,char const**,char const**,char const**) ; 
 int /*<<< orphan*/  pSspiFreeAuthIdentity (int /*<<< orphan*/ *) ; 
 scalar_t__ pSspiPromptForCredentialsW (char const*,TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_SspiPromptForCredentials(void)
{
    static const WCHAR targetW[] = {'S','s','p','i','T','e','s','t',0};
    static const WCHAR basicW[] = {'b','a','s','i','c',0};
    ULONG ret;
    SECURITY_STATUS status;
    CREDUI_INFOW info;
    PSEC_WINNT_AUTH_IDENTITY_OPAQUE id;
    const WCHAR *username, *domain, *creds;
    int save;

    if (!pSspiPromptForCredentialsW || !pSspiFreeAuthIdentity)
    {
        win_skip( "SspiPromptForCredentialsW is missing\n" );
        return;
    }

    info.cbSize         = sizeof(info);
    info.hwndParent     = NULL;
    info.pszMessageText = targetW;
    info.pszCaptionText = basicW;
    info.hbmBanner      = NULL;
    ret = pSspiPromptForCredentialsW( NULL, &info, 0, basicW, NULL, &id, &save, 0 );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    ret = pSspiPromptForCredentialsW( targetW, &info, 0, NULL, NULL, &id, &save, 0 );
    ok( ret == ERROR_NO_SUCH_PACKAGE, "got %u\n", ret );

    if (winetest_interactive)
    {
        id = NULL;
        save = -1;
        ret = pSspiPromptForCredentialsW( targetW, &info, 0, basicW, NULL, &id, &save, 0 );
        ok( ret == ERROR_SUCCESS || ret == ERROR_CANCELLED, "got %u\n", ret );
        if (ret == ERROR_SUCCESS)
        {
            ok( id != NULL, "id not set\n" );
            ok( save == TRUE || save == FALSE, "got %d\n", save );

            username = creds = NULL;
            domain = (const WCHAR *)0xdeadbeef;
            status = pSspiEncodeAuthIdentityAsStrings( id, &username, &domain, &creds );
            ok( status == SEC_E_OK, "got %u\n", status );
            ok( username != NULL, "username not set\n" );
            ok( domain == NULL, "domain not set\n" );
            ok( creds != NULL, "creds not set\n" );
            pSspiFreeAuthIdentity( id );
        }
    }
}