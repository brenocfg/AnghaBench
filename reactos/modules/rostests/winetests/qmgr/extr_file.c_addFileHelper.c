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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_AddFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  PathAppendW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  URL_UNESCAPE_INPLACE ; 
 int /*<<< orphan*/  UrlCreateFromPathW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UrlUnescapeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_localFile ; 
 int /*<<< orphan*/  test_remoteUrl ; 

__attribute__((used)) static HRESULT addFileHelper(IBackgroundCopyJob* job,
        const WCHAR *localName, const WCHAR *remoteName)
{
    DWORD urlSize;

    GetCurrentDirectoryW(MAX_PATH, test_localFile);
    PathAppendW(test_localFile, localName);
    GetCurrentDirectoryW(MAX_PATH, test_remoteUrl);
    PathAppendW(test_remoteUrl, remoteName);
    urlSize = MAX_PATH;
    UrlCreateFromPathW(test_remoteUrl, test_remoteUrl, &urlSize, 0);
    UrlUnescapeW(test_remoteUrl, NULL, &urlSize, URL_UNESCAPE_INPLACE);

    return IBackgroundCopyJob_AddFile(job, test_remoteUrl, test_localFile);
}