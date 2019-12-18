#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct PropertiesDialog {int /*<<< orphan*/  pVersionData; } ;
struct LANGANDCODEPAGE {int /*<<< orphan*/  wCodePage; int /*<<< orphan*/  wLanguage; } ;
typedef  char WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  dwFileVersionLS; int /*<<< orphan*/  dwFileVersionMS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int UINT ;
typedef  scalar_t__* PVOID ;
typedef  scalar_t__ LPVOID ;
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  scalar_t__ LPBYTE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int BUFFER_LEN ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetFileVersionInfoSizeW (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GetFileVersionInfoW (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IDC_LIST_PROP_VERSION_TYPES ; 
 int /*<<< orphan*/  IDC_LIST_PROP_VERSION_VALUES ; 
 int /*<<< orphan*/  IDC_STATIC_PROP_VERSION ; 
 scalar_t__* InfoStrings ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*,int) ; 
 int /*<<< orphan*/  PropDlg_DisplayValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ VerQueryValueW (int /*<<< orphan*/ ,char const*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void CheckForFileInfo(struct PropertiesDialog* dlg, HWND hwnd, LPCWSTR strFilename)
{
	static const WCHAR sBackSlash[] = {'\\','\0'};
	static const WCHAR sTranslation[] = {'\\','V','a','r','F','i','l','e','I','n','f','o','\\','T','r','a','n','s','l','a','t','i','o','n','\0'};
	static const WCHAR sStringFileInfo[] = {'\\','S','t','r','i','n','g','F','i','l','e','I','n','f','o','\\',
										'%','0','4','x','%','0','4','x','\\','%','s','\0'};
        static const WCHAR sFmt[] = {'%','d','.','%','d','.','%','d','.','%','d','\0'};
	DWORD dwVersionDataLen = GetFileVersionInfoSizeW(strFilename, NULL);

	if (dwVersionDataLen) {
		dlg->pVersionData = HeapAlloc(GetProcessHeap(), 0, dwVersionDataLen);

		if (GetFileVersionInfoW(strFilename, 0, dwVersionDataLen, dlg->pVersionData)) {
			LPVOID pVal;
			UINT nValLen;

			if (VerQueryValueW(dlg->pVersionData, sBackSlash, &pVal, &nValLen)) {
				if (nValLen == sizeof(VS_FIXEDFILEINFO)) {
					VS_FIXEDFILEINFO* pFixedFileInfo = (VS_FIXEDFILEINFO*)pVal;
                                        WCHAR buffer[BUFFER_LEN];

                                        sprintfW(buffer, sFmt,
                                                 HIWORD(pFixedFileInfo->dwFileVersionMS), LOWORD(pFixedFileInfo->dwFileVersionMS),
                                                 HIWORD(pFixedFileInfo->dwFileVersionLS), LOWORD(pFixedFileInfo->dwFileVersionLS));

                                        SetDlgItemTextW(hwnd, IDC_STATIC_PROP_VERSION, buffer);
				}
			}

			/* Read the list of languages and code pages. */
			if (VerQueryValueW(dlg->pVersionData, sTranslation, &pVal, &nValLen)) {
				struct LANGANDCODEPAGE* pTranslate = (struct LANGANDCODEPAGE*)pVal;
				struct LANGANDCODEPAGE* pEnd = (struct LANGANDCODEPAGE*)((LPBYTE)pVal+nValLen);

				HWND hlbox = GetDlgItem(hwnd, IDC_LIST_PROP_VERSION_TYPES);

				/* Read the file description for each language and code page. */
				for(; pTranslate<pEnd; ++pTranslate) {
					LPCSTR* p;

					for(p=InfoStrings; *p; ++p) {
						WCHAR subblock[200];
						WCHAR infoStr[100];
						LPCWSTR pTxt;
						UINT nValLen;

						LPCSTR pInfoString = *p;
						MultiByteToWideChar(CP_ACP, 0, pInfoString, -1, infoStr, 100);
						wsprintfW(subblock, sStringFileInfo, pTranslate->wLanguage, pTranslate->wCodePage, infoStr);

						/* Retrieve file description for language and code page */
						if (VerQueryValueW(dlg->pVersionData, subblock, (PVOID)&pTxt, &nValLen)) {
							int idx = SendMessageW(hlbox, LB_ADDSTRING, 0L, (LPARAM)infoStr);
							SendMessageW(hlbox, LB_SETITEMDATA, idx, (LPARAM)pTxt);
						}
					}
				}

				SendMessageW(hlbox, LB_SETCURSEL, 0, 0);

				PropDlg_DisplayValue(hlbox, GetDlgItem(hwnd,IDC_LIST_PROP_VERSION_VALUES));
			}
		}
	}
}