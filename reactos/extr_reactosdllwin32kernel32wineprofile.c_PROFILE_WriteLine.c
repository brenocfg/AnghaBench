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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int ENCODING ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CP_UTF8 ; 
#define  ENCODING_ANSI 131 
#define  ENCODING_UTF16BE 130 
#define  ENCODING_UTF16LE 129 
#define  ENCODING_UTF8 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PROFILE_ByteSwapShortBuffer (char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_wn (char*,int) ; 

__attribute__((used)) static void PROFILE_WriteLine( HANDLE hFile, WCHAR * szLine, int len, ENCODING encoding)
{
    char * write_buffer;
    int write_buffer_len;
    DWORD dwBytesWritten;

    TRACE("writing: %s\n", debugstr_wn(szLine, len));

    switch (encoding)
    {
    case ENCODING_ANSI:
        write_buffer_len = WideCharToMultiByte(CP_ACP, 0, szLine, len, NULL, 0, NULL, NULL);
        write_buffer = HeapAlloc(GetProcessHeap(), 0, write_buffer_len);
        if (!write_buffer) return;
        len = WideCharToMultiByte(CP_ACP, 0, szLine, len, write_buffer, write_buffer_len, NULL, NULL);
        WriteFile(hFile, write_buffer, len, &dwBytesWritten, NULL);
        HeapFree(GetProcessHeap(), 0, write_buffer);
        break;
    case ENCODING_UTF8:
        write_buffer_len = WideCharToMultiByte(CP_UTF8, 0, szLine, len, NULL, 0, NULL, NULL);
        write_buffer = HeapAlloc(GetProcessHeap(), 0, write_buffer_len);
        if (!write_buffer) return;
        len = WideCharToMultiByte(CP_UTF8, 0, szLine, len, write_buffer, write_buffer_len, NULL, NULL);
        WriteFile(hFile, write_buffer, len, &dwBytesWritten, NULL);
        HeapFree(GetProcessHeap(), 0, write_buffer);
        break;
    case ENCODING_UTF16LE:
        WriteFile(hFile, szLine, len * sizeof(WCHAR), &dwBytesWritten, NULL);
        break;
    case ENCODING_UTF16BE:
        PROFILE_ByteSwapShortBuffer(szLine, len);
        WriteFile(hFile, szLine, len * sizeof(WCHAR), &dwBytesWritten, NULL);
        break;
    default:
        FIXME("encoding type %d not implemented\n", encoding);
    }
}