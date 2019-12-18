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
typedef  int /*<<< orphan*/  fileInfo_t ;
typedef  int /*<<< orphan*/  InfoError ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_IF (int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  UTIL_isRegularFile (char const*) ; 
 int /*<<< orphan*/  getFileInfo_fileConfirmed (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  info_file_error ; 

__attribute__((used)) static InfoError
getFileInfo(fileInfo_t* info, const char* srcFileName)
{
    ERROR_IF(!UTIL_isRegularFile(srcFileName),
            info_file_error, "Error : %s is not a file", srcFileName);
    return getFileInfo_fileConfirmed(info, srcFileName);
}