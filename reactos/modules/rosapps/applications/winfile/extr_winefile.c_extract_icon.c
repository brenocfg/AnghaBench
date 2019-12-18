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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IExtractIconW ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ ) ; 
 scalar_t__ ExtractIconExW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 unsigned int GIL_DONTCACHE ; 
 int /*<<< orphan*/  GIL_FORSHELL ; 
 unsigned int GIL_NOTFILENAME ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IExtractIconW_Extract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IExtractIconW_GetIconLocation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,unsigned int*) ; 
 int /*<<< orphan*/  IID_IExtractIconW ; 
 int /*<<< orphan*/  IShellFolder_GetUIObjectOf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int _MAX_PATH ; 

__attribute__((used)) static HICON extract_icon(IShellFolder* folder, LPCITEMIDLIST pidl)
{
	IExtractIconW* pExtract;

	if (SUCCEEDED(IShellFolder_GetUIObjectOf(folder, 0, 1, (LPCITEMIDLIST*)&pidl, &IID_IExtractIconW, 0, (LPVOID*)&pExtract))) {
		WCHAR path[_MAX_PATH];
		unsigned flags;
		HICON hicon;
		int idx;

		if (SUCCEEDED(IExtractIconW_GetIconLocation(pExtract, GIL_FORSHELL, path, _MAX_PATH, &idx, &flags))) {
			if (!(flags & GIL_NOTFILENAME)) {
				if (idx == -1)
					idx = 0;	/* special case for some control panel applications */

				if ((int)ExtractIconExW(path, idx, 0, &hicon, 1) > 0)
					flags &= ~GIL_DONTCACHE;
			} else {
				HICON hIconLarge = 0;

				HRESULT hr = IExtractIconW_Extract(pExtract, path, idx, &hIconLarge, &hicon, MAKELONG(0/*GetSystemMetrics(SM_CXICON)*/,GetSystemMetrics(SM_CXSMICON)));

				if (SUCCEEDED(hr))
					DestroyIcon(hIconLarge);
			}

			return hicon;
		}
	}

	return 0;
}