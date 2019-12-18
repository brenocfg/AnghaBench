#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* StatInfoList; } ;
struct TYPE_7__ {struct TYPE_7__* Next; struct TYPE_7__* StatInfoListNext; TYPE_2__* ExtInfo; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__* PFILE_INFO ;
typedef  TYPE_2__* PEXTENSION_INFO ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  FILE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* StatInfoList ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PFILE_INFO
AddFile(LPTSTR FileName,
  PEXTENSION_INFO ExtInfo)
{
  PFILE_INFO StatInfo;
  PFILE_INFO Info;

  StatInfo = (PFILE_INFO) HeapAlloc (GetProcessHeap(), 0, sizeof (FILE_INFO));
  if (!StatInfo)
    return NULL;
  ZeroMemory (StatInfo, sizeof (FILE_INFO));
  _tcscpy (StatInfo->FileName, FileName);
  StatInfo->ExtInfo = ExtInfo;

  if (ExtInfo->StatInfoList)
  {
    Info = ExtInfo->StatInfoList;
    while (Info->StatInfoListNext != NULL)
    {
      Info = Info->StatInfoListNext;
    }
    Info->StatInfoListNext = StatInfo;
  }
  else
  {
    ExtInfo->StatInfoList = StatInfo;
  }

  if (StatInfoList)
  {
    Info = StatInfoList;
    while (Info->Next != NULL)
    {
      Info = Info->Next;
    }
    Info->Next = StatInfo;
  }
  else
  {
    StatInfoList = StatInfo;
  }

  return StatInfo;
}