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
 char* read_prompt_incremental (char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char *
read_prompt(const char *prompt)
{
	return read_prompt_incremental(prompt, true, true, NULL, NULL);
}