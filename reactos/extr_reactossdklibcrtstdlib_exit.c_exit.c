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

/* Variables and functions */
 int /*<<< orphan*/  ExitProcess (int) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  _cexit () ; 

void exit(int exitcode)
{
#if 0
  HMODULE hmscoree;
  static const WCHAR mscoreeW[] = {'m','s','c','o','r','e','e',0};
  void (WINAPI *pCorExitProcess)(int);
#endif
  WARN("exit(%d) called\n",exitcode);
  _cexit();
#if 0 
  hmscoree = GetModuleHandleW(mscoreeW);

  if (hmscoree)
  {
    pCorExitProcess = (void*)GetProcAddress(hmscoree, "CorExitProcess");

    if (pCorExitProcess)
      pCorExitProcess(exitcode);
  }
#endif
  ExitProcess(exitcode);

}