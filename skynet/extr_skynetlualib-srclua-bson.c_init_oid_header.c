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
typedef  int uint32_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 scalar_t__ gethostname (char*,int) ; 
 int getpid () ; 
 int oid_counter ; 
 int* oid_header ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_oid_header() {
	if (oid_counter) {
		// already init
		return;
	}
	pid_t pid = getpid();
	uint32_t h = 0;
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname))==0) {
		int i;
		for (i=0;i<sizeof(hostname) && hostname[i];i++) {
			h = h ^ ((h<<5)+(h>>2)+hostname[i]);
 		}
		h ^= i;
	}
	oid_header[0] = h & 0xff;
	oid_header[1] = (h>>8) & 0xff;
	oid_header[2] = (h>>16) & 0xff;
	oid_header[3] = pid & 0xff;
	oid_header[4] = (pid >> 8) & 0xff;
	
	uint32_t c = h ^ time(NULL) ^ (uintptr_t)&h;
	if (c == 0) {
		c = 1;
	}
	oid_counter = c;
}