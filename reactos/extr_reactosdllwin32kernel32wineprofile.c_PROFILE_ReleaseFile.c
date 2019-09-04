#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  LastWriteTime; int /*<<< orphan*/  encoding; int /*<<< orphan*/ * filename; int /*<<< orphan*/ * section; int /*<<< orphan*/  changed; } ;

/* Variables and functions */
 TYPE_1__* CurProfile ; 
 int /*<<< orphan*/  ENCODING_ANSI ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROFILE_FlushFile () ; 
 int /*<<< orphan*/  PROFILE_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void PROFILE_ReleaseFile(void)
{
    PROFILE_FlushFile();
    PROFILE_Free( CurProfile->section );
    HeapFree( GetProcessHeap(), 0, CurProfile->filename );
    CurProfile->changed = FALSE;
    CurProfile->section = NULL;
    CurProfile->filename  = NULL;
    CurProfile->encoding = ENCODING_ANSI;
    ZeroMemory(&CurProfile->LastWriteTime, sizeof(CurProfile->LastWriteTime));
}