#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct FILELIST {struct FILELIST* next; int /*<<< orphan*/  DoExtract; int /*<<< orphan*/  FileName; } ;
struct TYPE_4__ {int /*<<< orphan*/  Operation; struct FILELIST* FileList; } ;
typedef  TYPE_1__ SESSION ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_FILLFILELIST ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  file_in_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pExtract (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD fill_file_list(SESSION *session, LPCSTR szCabName, LPCSTR szFileList)
{
    DWORD dwNumFound = 0;
    struct FILELIST *pNode;

    session->Operation |= EXTRACT_FILLFILELIST;
    if (pExtract(session, szCabName) != S_OK)
    {
        session->Operation &= ~EXTRACT_FILLFILELIST;
        return -1;
    }

    pNode = session->FileList;
    while (pNode)
    {
        if (!file_in_list(pNode->FileName, szFileList))
            pNode->DoExtract = FALSE;
        else
            dwNumFound++;

        pNode = pNode->next;
    }

    session->Operation &= ~EXTRACT_FILLFILELIST;
    return dwNumFound;
}