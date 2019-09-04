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
typedef  int LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  GetWindowTextA (int /*<<< orphan*/ ,char*,int) ; 
 int MAXLEN ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  hwndET2 ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void ET2_check_change(void) {
   char szLocalString[MAXLEN];
   /* This EN_UPDATE handler changes any 'foo' to 'bar'. */
   GetWindowTextA(hwndET2, szLocalString, MAXLEN);
   if (strcmp(szLocalString, "foo")==0) {
       strcpy(szLocalString, "bar");
       SendMessageA(hwndET2, WM_SETTEXT, 0, (LPARAM) szLocalString);
   }
   /* always leave the cursor at the end. */
   SendMessageA(hwndET2, EM_SETSEL, MAXLEN - 1, MAXLEN - 1);
}