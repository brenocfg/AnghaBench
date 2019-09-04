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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  tcursor ;

/* Variables and functions */
 int /*<<< orphan*/ * desk_save ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  mcursor ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_init () ; 
 scalar_t__ xmalloc (int) ; 

int ui_init(void)
{
  vga_init();
  memset(&mcursor, 0, sizeof(tcursor));
  desk_save = (uint8*)xmalloc(0x38400 * g_server_Bpp);
  return 1;
}