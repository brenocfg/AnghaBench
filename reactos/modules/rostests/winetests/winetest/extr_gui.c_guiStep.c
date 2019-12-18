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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  WPARAM ;

/* Variables and functions */
 int IDC_ST0 ; 
 int /*<<< orphan*/  PBM_SETPOS ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int const,char*) ; 
 int /*<<< orphan*/  dialog ; 
 int /*<<< orphan*/  free (char*) ; 
 int progressCurr ; 
 int progressGroup ; 
 int progressScale ; 
 char* vstrmake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
guiStep (va_list ap)
{
    const int pgID = IDC_ST0 + progressGroup * 2;
    char *str = vstrmake (NULL, ap);
    
    progressCurr++;
    SetDlgItemText (dialog, pgID, str);
    SendDlgItemMessage (dialog, pgID+1, PBM_SETPOS,
                        (WPARAM)(progressScale * progressCurr), 0);
    free (str);
    return 0;
}