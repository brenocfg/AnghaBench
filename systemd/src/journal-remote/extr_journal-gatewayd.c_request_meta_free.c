#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct MHD_Connection {int dummy; } ;
typedef  enum MHD_RequestTerminationCode { ____Placeholder_MHD_RequestTerminationCode } MHD_RequestTerminationCode ;
struct TYPE_3__ {struct TYPE_3__* cursor; int /*<<< orphan*/  tmp; int /*<<< orphan*/  journal; } ;
typedef  TYPE_1__ RequestMeta ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_journal_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void request_meta_free(
                void *cls,
                struct MHD_Connection *connection,
                void **connection_cls,
                enum MHD_RequestTerminationCode toe) {

        RequestMeta *m = *connection_cls;

        if (!m)
                return;

        sd_journal_close(m->journal);

        safe_fclose(m->tmp);

        free(m->cursor);
        free(m);
}