#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_6__ {TYPE_1__* lpVtbl; } ;
struct TYPE_5__ {scalar_t__ (* Read ) (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__ IStream ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_TEMPORARY ; 
 int FILE_READ_DATA ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int FILE_WRITE_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT StreamToFile(IStream *stream, TCHAR *szFile)
{
    byte buffer[BLOCK_SIZE];
    DWORD bytes_read;
    DWORD bytes_written;
    HRESULT hr;
	HANDLE hFile;

    hFile = CreateFile( szFile,
          FILE_READ_DATA | FILE_WRITE_DATA,
          FILE_SHARE_READ | FILE_SHARE_WRITE,
          NULL,
          CREATE_ALWAYS,
          FILE_ATTRIBUTE_TEMPORARY,
          NULL );

    if (hFile != INVALID_HANDLE_VALUE) {
        do {
            hr = stream->lpVtbl->Read(stream, buffer, BLOCK_SIZE, &bytes_read);
			bytes_written = 0;
            if (SUCCEEDED(hr) && bytes_read)
			{
				if (!WriteFile(hFile, buffer, bytes_read, &bytes_written, NULL))
				{
					hr = HRESULT_FROM_WIN32(GetLastError());
					bytes_written = 0;
				}
			}
        } while (S_OK == hr && bytes_written != 0);
        CloseHandle(hFile);
		if (FAILED(hr))
			DeleteFile(szFile);
		else
			hr = S_OK;
    }
    else
	    hr = HRESULT_FROM_WIN32(GetLastError());

    return hr;
}