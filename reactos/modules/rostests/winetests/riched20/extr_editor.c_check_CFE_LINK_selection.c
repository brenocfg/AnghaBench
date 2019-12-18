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
typedef  int /*<<< orphan*/  text_format ;
struct TYPE_2__ {int cbSize; int dwEffects; } ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ CHARFORMAT2A ;
typedef  int BOOL ;

/* Variables and functions */
 int CFE_LINK ; 
 int /*<<< orphan*/  EM_GETCHARFORMAT ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int SCF_SELECTION ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static BOOL check_CFE_LINK_selection(HWND hwnd, int sel_start, int sel_end)
{
  CHARFORMAT2A text_format;
  text_format.cbSize = sizeof(text_format);
  SendMessageA(hwnd, EM_SETSEL, sel_start, sel_end);
  SendMessageA(hwnd, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&text_format);
  return (text_format.dwEffects & CFE_LINK) != 0;
}