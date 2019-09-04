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
typedef  int /*<<< orphan*/  Registrar ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HINSTANCE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FindResourceW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOAD_LIBRARY_AS_DATAFILE ; 
 scalar_t__ LoadLibraryExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (scalar_t__,int /*<<< orphan*/ ) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int SizeofResource (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  string_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT resource_register(Registrar *This, LPCOLESTR resFileName,
                        LPCOLESTR szID, LPCOLESTR szType, BOOL do_register)
{
    HINSTANCE hins;
    HRSRC src;
    LPSTR regstra;
    LPWSTR regstrw;
    DWORD len, reslen;
    HRESULT hres;

    hins = LoadLibraryExW(resFileName, NULL, LOAD_LIBRARY_AS_DATAFILE);
    if(hins) {
        src = FindResourceW(hins, szID, szType);
        if(src) {
            regstra = LoadResource(hins, src);
            reslen = SizeofResource(hins, src);
            if(regstra) {
                len = MultiByteToWideChar(CP_ACP, 0, regstra, reslen, NULL, 0)+1;
                regstrw = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len*sizeof(WCHAR));
                MultiByteToWideChar(CP_ACP, 0, regstra, reslen, regstrw, len);
                regstrw[len-1] = '\0';

                hres = string_register(This, regstrw, do_register);

                HeapFree(GetProcessHeap(), 0, regstrw);
            }else {
                WARN("could not load resource\n");
                hres = HRESULT_FROM_WIN32(GetLastError());
            }
        }else {
            WARN("Could not find source\n");
            hres = HRESULT_FROM_WIN32(GetLastError());
        }
        FreeLibrary(hins);
    }else {
        WARN("Could not load resource file\n");
        hres = HRESULT_FROM_WIN32(GetLastError());
    }

    return hres;
}