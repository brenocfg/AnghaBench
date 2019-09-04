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
struct __stat64 {int dummy; } ;

/* Variables and functions */
 int _wstat64 (int /*<<< orphan*/ ,struct __stat64*) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/  wpath ; 

__attribute__((used)) static __inline int _stat64U(const char *path, struct __stat64 *buffer)
{
	int ret;
	wconvert(path);
	ret = _wstat64(wpath, buffer);
	wfree(path);
	return ret;
}