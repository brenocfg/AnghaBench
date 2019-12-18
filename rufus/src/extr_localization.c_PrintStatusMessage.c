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
 int SBT_OWNERDRAW ; 
 int SB_SECTION_LEFT ; 
 int /*<<< orphan*/  SB_SETTEXTW ; 
 int /*<<< orphan*/  SendMessageLU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  hStatus ; 

__attribute__((used)) static void PrintStatusMessage(char* msg) {
	SendMessageLU(hStatus, SB_SETTEXTW, SBT_OWNERDRAW | SB_SECTION_LEFT, msg);
}