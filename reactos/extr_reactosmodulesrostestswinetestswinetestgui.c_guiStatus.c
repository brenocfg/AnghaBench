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

/* Variables and functions */
 int /*<<< orphan*/  IDC_SB ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dialog ; 
 int /*<<< orphan*/  free (char*) ; 
 char* vstrmake (size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
guiStatus (va_list ap)
{
    size_t len;
    char *str = vstrmake (&len, ap);

    if (len > 128) str[129] = 0;
    SetDlgItemText (dialog, IDC_SB, str);
    free (str);
    return 0;
}