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
 int /*<<< orphan*/  ES_MULTILINE ; 
 int /*<<< orphan*/  RICHEDIT_CLASS20W ; 
 int /*<<< orphan*/  new_windowW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HWND new_richeditW(HWND parent) {
  return new_windowW(RICHEDIT_CLASS20W, ES_MULTILINE, parent);
}