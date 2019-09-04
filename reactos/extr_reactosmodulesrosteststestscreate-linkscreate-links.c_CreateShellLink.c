#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_17__ {TYPE_1__* lpVtbl; } ;
struct TYPE_16__ {TYPE_2__* lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* Release ) (TYPE_3__*) ;scalar_t__ (* QueryInterface ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* SetDescription ) (TYPE_3__*,char*) ;scalar_t__ (* SetIconLocation ) (TYPE_3__*,char*,int) ;scalar_t__ (* SetWorkingDirectory ) (TYPE_3__*,char*) ;scalar_t__ (* SetArguments ) (TYPE_3__*,char*) ;scalar_t__ (* SetPath ) (TYPE_3__*,char*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* Release ) (TYPE_4__*) ;scalar_t__ (* Save ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  char* LPCSTR ;
typedef  TYPE_3__ IShellLinkA ;
typedef  TYPE_4__ IPersistFile ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IShellLink ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 (TYPE_3__*,char*) ; 
 scalar_t__ stub2 (TYPE_3__*,char*) ; 
 scalar_t__ stub3 (TYPE_3__*,char*) ; 
 scalar_t__ stub4 (TYPE_3__*,char*,int) ; 
 scalar_t__ stub5 (TYPE_3__*,char*) ; 
 scalar_t__ stub6 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub7 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__*) ; 

HRESULT CreateShellLink(LPCSTR linkPath, LPCSTR cmd, LPCSTR arg, LPCSTR dir, LPCSTR iconPath, int icon_nr, LPCSTR comment)
{
	IShellLinkA* psl;
	IPersistFile* ppf;
	WCHAR buffer[MAX_PATH];

	HRESULT hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, (LPVOID*)&psl);

	printf("creating shortcut file '%s' to %s...\n", linkPath, cmd);

	if (SUCCEEDED(hr)) {
		hr = psl->lpVtbl->SetPath(psl, cmd);

		if (arg)
			hr = psl->lpVtbl->SetArguments(psl, arg);

		if (dir)
			hr = psl->lpVtbl->SetWorkingDirectory(psl, dir);

		if (iconPath)
			hr = psl->lpVtbl->SetIconLocation(psl, iconPath, icon_nr);

		if (comment)
			hr = psl->lpVtbl->SetDescription(psl, comment);

		hr = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf);

		if (SUCCEEDED(hr)) {
			MultiByteToWideChar(CP_ACP, 0, linkPath, -1, buffer, MAX_PATH);

			hr = ppf->lpVtbl->Save(ppf, buffer, TRUE);

			ppf->lpVtbl->Release(ppf);
		}

		psl->lpVtbl->Release(psl);
	}

	if (SUCCEEDED(hr))
		printf("OK\n\n");
	else
		printf("error %08x\n\n", (int) hr);

	return hr;
}