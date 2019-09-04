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
struct TYPE_4__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEnhMetaFileA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static HENHMETAFILE create_emf(void)
{
    const RECT rect = {0, 0, 100, 100};
    HDC hdc = CreateEnhMetaFileA(NULL, NULL, &rect, "HENHMETAFILE Marshaling Test\0Test\0\0");
    ExtTextOutA(hdc, 0, 0, ETO_OPAQUE, &rect, "Test String", strlen("Test String"), NULL);
    return CloseEnhMetaFile(hdc);
}