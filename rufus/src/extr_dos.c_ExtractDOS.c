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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  BT_FREEDOS 129 
#define  BT_MSDOS 128 
 int /*<<< orphan*/  ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 int ComboBox_GetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExtractFreeDOS (char const*) ; 
 int /*<<< orphan*/  ExtractMSDOS (char const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  hBootType ; 

BOOL ExtractDOS(const char* path)
{
	switch(ComboBox_GetItemData(hBootType, ComboBox_GetCurSel(hBootType))) {
	case BT_MSDOS:
		return ExtractMSDOS(path);
	case BT_FREEDOS:
		return ExtractFreeDOS(path);
	}
	return FALSE;
}