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
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_AddFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAppendW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  URL_UNESCAPE_INPLACE ; 
 int /*<<< orphan*/  UrlCreateFromPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UrlUnescapeW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT addFileHelper(IBackgroundCopyJob* job,
                             const WCHAR *localName, const WCHAR *remoteName)
{
    DWORD urlSize;
    WCHAR localFile[MAX_PATH];
    WCHAR remoteUrl[MAX_PATH];
    WCHAR remoteFile[MAX_PATH];

    GetCurrentDirectoryW(MAX_PATH, localFile);
    PathAppendW(localFile, localName);
    GetCurrentDirectoryW(MAX_PATH, remoteFile);
    PathAppendW(remoteFile, remoteName);
    urlSize = MAX_PATH;
    UrlCreateFromPathW(remoteFile, remoteUrl, &urlSize, 0);
    UrlUnescapeW(remoteUrl, NULL, &urlSize, URL_UNESCAPE_INPLACE);
    return IBackgroundCopyJob_AddFile(job, remoteUrl, localFile);
}