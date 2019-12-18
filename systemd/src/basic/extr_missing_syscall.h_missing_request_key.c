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
typedef  int key_serial_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_request_key ; 
 int /*<<< orphan*/  errno ; 
 int syscall (int /*<<< orphan*/ ,char const*,char const*,char const*,int) ; 

__attribute__((used)) static inline key_serial_t missing_request_key(const char *type, const char *description, const char * callout_info, key_serial_t destringid) {
#  if defined __NR_request_key && __NR_request_key > 0
        return syscall(__NR_request_key, type, description, callout_info, destringid);
#  else
        errno = ENOSYS;
        return -1;
#  endif

#  define request_key missing_request_key
}