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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 scalar_t__ is_text (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void textfreeT(LPWSTR wstr, BOOL isW)
{
    if (!isW && is_text(wstr)) Free (wstr);
}