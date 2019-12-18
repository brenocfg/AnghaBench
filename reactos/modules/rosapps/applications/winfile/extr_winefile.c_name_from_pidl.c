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
struct TYPE_4__ {int /*<<< orphan*/  mkid; } ;
typedef  int /*<<< orphan*/  STRRET ;
typedef  int /*<<< orphan*/  SHGDNF ;
typedef  char* LPWSTR ;
typedef  TYPE_1__* LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IShellFolder_GetDisplayNameOf (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_strret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_strretW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static HRESULT name_from_pidl(IShellFolder* folder, LPITEMIDLIST pidl, LPWSTR buffer, int len, SHGDNF flags)
{
	STRRET str;

	HRESULT hr = IShellFolder_GetDisplayNameOf(folder, pidl, flags, &str);

	if (SUCCEEDED(hr)) {
		get_strretW(&str, &pidl->mkid, buffer, len);
		free_strret(&str);
	} else
		buffer[0] = '\0';

	return hr;
}