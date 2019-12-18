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
struct rev_info {char const* rev; scalar_t__ file; } ;

/* Variables and functions */
 struct rev_info* rev_infos ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static const char* get_file_rev(const char* file)
{
    const struct rev_info* rev;
 
    for(rev = rev_infos; rev->file; rev++) {
	if (strcmp(rev->file, file) == 0) return rev->rev;
    }

    return "-";
}