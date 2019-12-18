#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  n_ref; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer_event; int /*<<< orphan*/  event; TYPE_2__* writer; int /*<<< orphan*/  importer; } ;
typedef  TYPE_1__ RemoteSource ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_importer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_unref (TYPE_2__*) ; 

void source_free(RemoteSource *source) {
        if (!source)
                return;

        journal_importer_cleanup(&source->importer);

        log_debug("Writer ref count %i", source->writer->n_ref);
        writer_unref(source->writer);

        sd_event_source_unref(source->event);
        sd_event_source_unref(source->buffer_event);

        free(source);
}