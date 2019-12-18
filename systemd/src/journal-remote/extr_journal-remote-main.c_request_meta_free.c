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
struct MHD_Connection {int dummy; } ;
typedef  enum MHD_RequestTerminationCode { ____Placeholder_MHD_RequestTerminationCode } MHD_RequestTerminationCode ;
typedef  int /*<<< orphan*/  RemoteSource ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void**) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void request_meta_free(void *cls,
                              struct MHD_Connection *connection,
                              void **connection_cls,
                              enum MHD_RequestTerminationCode toe) {
        RemoteSource *s;

        assert(connection_cls);
        s = *connection_cls;

        if (s) {
                log_debug("Cleaning up connection metadata %p", s);
                source_free(s);
                *connection_cls = NULL;
        }
}