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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  EM_GETSEL ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  GetWindowTextA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 long SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SetWindowTextA (int /*<<< orphan*/ ,char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int CC_CheckDigitsInEdit( HWND hwnd, int maxval )
{
 int i, k, m, result, value;
 long editpos;
 char buffer[30];

 GetWindowTextA(hwnd, buffer, ARRAY_SIZE(buffer));
 m = strlen(buffer);
 result = 0;

 for (i = 0 ; i < m ; i++)
  if (buffer[i] < '0' || buffer[i] > '9')
  {
   for (k = i + 1; k <= m; k++)  /* delete bad character */
   {
    buffer[i] = buffer[k];
    m--;
   }
   buffer[m] = 0;
   result = 1;
  }

 value = atoi(buffer);
 if (value > maxval)       /* build a new string */
 {
  sprintf(buffer, "%d", maxval);
  result = 2;
 }
 if (result)
 {
  editpos = SendMessageA(hwnd, EM_GETSEL, 0, 0);
  SetWindowTextA(hwnd, buffer );
  SendMessageA(hwnd, EM_SETSEL, 0, editpos);
 }
 return value;
}