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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ ReadFile (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT file_register(Registrar *This, LPCOLESTR fileName, BOOL do_register)
{
    HANDLE file;
    DWORD filelen, len;
    LPWSTR regstrw;
    LPSTR regstra;
    HRESULT hres;

    file = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if(file != INVALID_HANDLE_VALUE) {
        filelen = GetFileSize(file, NULL);
        regstra = HeapAlloc(GetProcessHeap(), 0, filelen);
        if(ReadFile(file, regstra, filelen, NULL, NULL)) {
            len = MultiByteToWideChar(CP_ACP, 0, regstra, filelen, NULL, 0)+1;
            regstrw = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len*sizeof(WCHAR));
            MultiByteToWideChar(CP_ACP, 0, regstra, filelen, regstrw, len);
            regstrw[len-1] = '\0';

            hres = string_register(This, regstrw, do_register);

            HeapFree(GetProcessHeap(), 0, regstrw);
        }else {
            WARN("Failed to read file %s\n", debugstr_w(fileName));
            hres = HRESULT_FROM_WIN32(GetLastError());
        }
        HeapFree(GetProcessHeap(), 0, regstra);
        CloseHandle(file);
    }else {
        WARN("Could not open file %s\n", debugstr_w(fileName));
        hres = HRESULT_FROM_WIN32(GetLastError());
    }

    return hres;
}