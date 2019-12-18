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
struct TYPE_6__ {scalar_t__ local; scalar_t__ image_root; scalar_t__ final_path; int /*<<< orphan*/  output_fd; int /*<<< orphan*/  input_event_source; int /*<<< orphan*/  compress; scalar_t__ temp_path; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ RawImport ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  import_compress_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

RawImport* raw_import_unref(RawImport *i) {
        if (!i)
                return NULL;

        sd_event_unref(i->event);

        if (i->temp_path) {
                (void) unlink(i->temp_path);
                free(i->temp_path);
        }

        import_compress_free(&i->compress);

        sd_event_source_unref(i->input_event_source);

        safe_close(i->output_fd);

        free(i->final_path);
        free(i->image_root);
        free(i->local);
        return mfree(i);
}