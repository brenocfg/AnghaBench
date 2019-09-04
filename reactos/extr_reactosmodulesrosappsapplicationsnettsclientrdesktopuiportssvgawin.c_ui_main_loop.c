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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  RDP_LOGON_NORMAL ; 
 int /*<<< orphan*/  True ; 
 int UpAndRunning ; 
 int /*<<< orphan*/  deactivated ; 
 int /*<<< orphan*/  ext_disc_reason ; 
 int /*<<< orphan*/  g_servername ; 
 int /*<<< orphan*/  g_sock ; 
 int /*<<< orphan*/  process_keyboard () ; 
 int /*<<< orphan*/  process_mouse () ; 
 int /*<<< orphan*/  rdp_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  rdp_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vga_waitevent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL ui_main_loop(void)
{
  int sel;
  fd_set rfds;

  if (!rdp_connect(g_servername, RDP_LOGON_NORMAL, "", "", "", ""))
    return False;
  UpAndRunning = 1;
  FD_ZERO(&rfds);
  FD_SET(g_sock, &rfds);
  sel = vga_waitevent(3, &rfds, NULL, NULL, NULL);
  while (sel >= 0)
  {
    if (sel & 1) /* mouse */
    {
      process_mouse();
    }
    else if (sel & 2) /* keyboard */
    {
      process_keyboard();
    }
    else
    {
      if (!rdp_loop(&deactivated, &ext_disc_reason))
        return True; /* ok */
    }
    FD_ZERO(&rfds);
    FD_SET(g_sock, &rfds);
    sel = vga_waitevent(3, &rfds, NULL, NULL, NULL);
  }
  return True;
}