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
struct TYPE_3__ {int dwStructSize; int nPort; int /*<<< orphan*/  lpszExtraInfo; void* dwExtraInfoLength; int /*<<< orphan*/  lpszUrlPath; void* dwUrlPathLength; int /*<<< orphan*/  lpszPassword; void* dwPasswordLength; int /*<<< orphan*/  lpszUserName; void* dwUserNameLength; int /*<<< orphan*/  lpszHostName; void* dwHostNameLength; int /*<<< orphan*/  nScheme; int /*<<< orphan*/  lpszScheme; void* dwSchemeLength; } ;
typedef  TYPE_1__ URL_COMPONENTS ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNET_SCHEME_HTTP ; 
 int /*<<< orphan*/  about ; 
 int /*<<< orphan*/  http ; 
 void* lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  password ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  username ; 
 int /*<<< orphan*/  winehq ; 

__attribute__((used)) static void fill_url_components( URL_COMPONENTS *uc )
{
    uc->dwStructSize = sizeof(URL_COMPONENTS);
    uc->lpszScheme = http;
    uc->dwSchemeLength = lstrlenW( uc->lpszScheme );
    uc->nScheme = INTERNET_SCHEME_HTTP;
    uc->lpszHostName = winehq;
    uc->dwHostNameLength = lstrlenW( uc->lpszHostName );
    uc->nPort = 80;
    uc->lpszUserName = username;
    uc->dwUserNameLength = lstrlenW( uc->lpszUserName );
    uc->lpszPassword = password;
    uc->dwPasswordLength = lstrlenW( uc->lpszPassword );
    uc->lpszUrlPath = about;
    uc->dwUrlPathLength = lstrlenW( uc->lpszUrlPath );
    uc->lpszExtraInfo = query;
    uc->dwExtraInfoLength = lstrlenW( uc->lpszExtraInfo );
}