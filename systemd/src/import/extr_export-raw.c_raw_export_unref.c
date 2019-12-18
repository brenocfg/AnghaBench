#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  path; int /*<<< orphan*/  buffer; int /*<<< orphan*/  input_fd; int /*<<< orphan*/  event; int /*<<< orphan*/  compress; int /*<<< orphan*/  output_event_source; } ;
typedef  TYPE_1__ RawExport ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  import_compress_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 

RawExport *raw_export_unref(RawExport *e) {
        if (!e)
                return NULL;

        sd_event_source_unref(e->output_event_source);

        import_compress_free(&e->compress);

        sd_event_unref(e->event);

        safe_close(e->input_fd);

        free(e->buffer);
        free(e->path);
        return mfree(e);
}