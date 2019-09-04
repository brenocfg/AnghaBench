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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  MEPF_CELL ; 
 int /*<<< orphan*/ * ME_InsertEndParaFromCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

ME_DisplayItem* ME_InsertTableCellFromCursor(ME_TextEditor *editor)
{
  ME_DisplayItem *para;
  WCHAR tab = '\t';
  para = ME_InsertEndParaFromCursor(editor, 0, &tab, 1, MEPF_CELL);
  return para;
}