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

/* Variables and functions */
 int /*<<< orphan*/  MB_ICONERROR ; 
 int /*<<< orphan*/  MessageBoxA (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void PrintErrorMessage(const char *message)
{
  #ifdef _CONSOLE
  printf("\n7-Zip Error: %s\n", message);
  #else
  #ifdef UNDER_CE
  WCHAR messageW[256 + 4];
  unsigned i;
  for (i = 0; i < 256 && message[i] != 0; i++)
    messageW[i] = message[i];
  messageW[i] = 0;
  MessageBoxW(0, messageW, L"7-Zip Error", MB_ICONERROR);
  #else
  MessageBoxA(0, message, "7-Zip Error", MB_ICONERROR);
  #endif
  #endif
}