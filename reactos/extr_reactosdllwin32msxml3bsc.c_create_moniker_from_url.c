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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateURLMonikerEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_uri (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

HRESULT create_moniker_from_url(LPCWSTR url, IMoniker **mon)
{
    HRESULT hr;
    IUri *uri;

    TRACE("%s\n", debugstr_w(url));

    if (FAILED(hr = create_uri(url, &uri)))
        return hr;

    hr = CreateURLMonikerEx2(NULL, uri, mon, 0);
    IUri_Release(uri);
    return hr;
}