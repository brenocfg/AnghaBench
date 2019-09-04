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
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  fileInfo_t ;
typedef  int InfoError ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*) ; 
 int /*<<< orphan*/  DISPLAYOUT (char*,...) ; 
 int /*<<< orphan*/  FIO_addFInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  displayInfo (char const*,int /*<<< orphan*/ *,int) ; 
 int getFileInfo (int /*<<< orphan*/ *,char const*) ; 
#define  info_file_error 132 
#define  info_frame_error 131 
#define  info_not_zstd 130 
#define  info_success 129 
#define  info_truncated_input 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
FIO_listFile(fileInfo_t* total, const char* inFileName, int displayLevel)
{
    fileInfo_t info;
    memset(&info, 0, sizeof(info));
    {   InfoError const error = getFileInfo(&info, inFileName);
        switch (error) {
            case info_frame_error:
                /* display error, but provide output */
                DISPLAYLEVEL(1, "Error while parsing \"%s\" \n", inFileName);
                break;
            case info_not_zstd:
                DISPLAYOUT("File \"%s\" not compressed by zstd \n", inFileName);
                if (displayLevel > 2) DISPLAYOUT("\n");
                return 1;
            case info_file_error:
                /* error occurred while opening the file */
                if (displayLevel > 2) DISPLAYOUT("\n");
                return 1;
            case info_truncated_input:
                DISPLAYOUT("File \"%s\" is truncated \n", inFileName);
                if (displayLevel > 2) DISPLAYOUT("\n");
                return 1;
            case info_success:
            default:
                break;
        }

        displayInfo(inFileName, &info, displayLevel);
        *total = FIO_addFInfo(*total, info);
        assert(error == info_success || error == info_frame_error);
        return error;
    }
}