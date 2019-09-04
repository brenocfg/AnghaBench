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
struct flag_info {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DDRAW_dump_flags_nolf (int /*<<< orphan*/ ,struct flag_info const*,size_t) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static void DDRAW_dump_flags(DWORD flags, const struct flag_info *names, size_t num_names)
{
    DDRAW_dump_flags_nolf(flags, names, num_names);
    TRACE("\n");
}