#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  working_dir; int /*<<< orphan*/  install_sec; int /*<<< orphan*/  inf_filename; int /*<<< orphan*/  inf_path; int /*<<< orphan*/  hinf; } ;
typedef  TYPE_1__ ADVInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupCloseInfFile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void install_release(const ADVInfo *info)
{
    SetupCloseInfFile(info->hinf);

    HeapFree(GetProcessHeap(), 0, info->inf_path);
    HeapFree(GetProcessHeap(), 0, info->inf_filename);
    HeapFree(GetProcessHeap(), 0, info->install_sec);
    HeapFree(GetProcessHeap(), 0, info->working_dir);
}