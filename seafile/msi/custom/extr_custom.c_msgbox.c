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
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

void msgbox(const char *msg)
{
    MessageBox(NULL, msg, "Seafile Custom", MB_OK);
}