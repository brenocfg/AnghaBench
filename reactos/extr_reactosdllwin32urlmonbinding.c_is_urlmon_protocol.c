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
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IUri_GetScheme (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRUE ; 
#define  URL_SCHEME_FILE 133 
#define  URL_SCHEME_FTP 132 
#define  URL_SCHEME_GOPHER 131 
#define  URL_SCHEME_HTTP 130 
#define  URL_SCHEME_HTTPS 129 
#define  URL_SCHEME_MK 128 

__attribute__((used)) static BOOL is_urlmon_protocol(IUri *uri)
{
    DWORD scheme;
    HRESULT hres;

    hres = IUri_GetScheme(uri, &scheme);
    if(FAILED(hres))
        return FALSE;

    switch(scheme) {
    case URL_SCHEME_FILE:
    case URL_SCHEME_FTP:
    case URL_SCHEME_GOPHER:
    case URL_SCHEME_HTTP:
    case URL_SCHEME_HTTPS:
    case URL_SCHEME_MK:
        return TRUE;
    }

    return FALSE;
}