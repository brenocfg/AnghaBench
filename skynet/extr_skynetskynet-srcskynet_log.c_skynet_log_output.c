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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PTYPE_SOCKET ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  log_blob (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  log_socket (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  skynet_now () ; 

void 
skynet_log_output(FILE *f, uint32_t source, int type, int session, void * buffer, size_t sz) {
	if (type == PTYPE_SOCKET) {
		log_socket(f, buffer, sz);
	} else {
		uint32_t ti = (uint32_t)skynet_now();
		fprintf(f, ":%08x %d %d %u ", source, type, session, ti);
		log_blob(f, buffer, sz);
		fprintf(f,"\n");
		fflush(f);
	}
}