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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  HistoryCurrentBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HistoryDeleteBuffer (int /*<<< orphan*/ ) ; 

VOID
HistoryDeleteCurrentBuffer(PCONSRV_CONSOLE Console,
                           PUNICODE_STRING ExeName)
{
    HistoryDeleteBuffer(HistoryCurrentBuffer(Console, ExeName));
}