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
struct TYPE_6__ {int /*<<< orphan*/  objtable; scalar_t__ record_stream; TYPE_1__* record_graphics; int /*<<< orphan*/  hemf; int /*<<< orphan*/  preserve_hemf; int /*<<< orphan*/  record_dc; int /*<<< orphan*/  comment_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  busy; int /*<<< orphan*/ * image; } ;
typedef  TYPE_2__ GpMetafile ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metafile_free_object_table_entry (TYPE_2__*,unsigned int) ; 

void METAFILE_Free(GpMetafile *metafile)
{
    unsigned int i;

    heap_free(metafile->comment_data);
    DeleteEnhMetaFile(CloseEnhMetaFile(metafile->record_dc));
    if (!metafile->preserve_hemf)
        DeleteEnhMetaFile(metafile->hemf);
    if (metafile->record_graphics)
    {
        WARN("metafile closed while recording\n");
        /* not sure what to do here; for now just prevent the graphics from functioning or using this object */
        metafile->record_graphics->image = NULL;
        metafile->record_graphics->busy = TRUE;
    }

    if (metafile->record_stream)
        IStream_Release(metafile->record_stream);

    for (i = 0; i < ARRAY_SIZE(metafile->objtable); i++)
        metafile_free_object_table_entry(metafile, i);
}