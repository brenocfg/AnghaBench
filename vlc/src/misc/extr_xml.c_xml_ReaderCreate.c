#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p_module; int /*<<< orphan*/ * p_stream; } ;
typedef  TYPE_1__ xml_reader_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

xml_reader_t *xml_ReaderCreate(vlc_object_t *obj, stream_t *stream)
{
    xml_reader_t *reader;

    reader = vlc_custom_create(obj, sizeof(*reader), "xml reader");

    reader->p_stream = stream;
    reader->p_module = module_need(reader, "xml reader", NULL, false);
    if (unlikely(reader->p_module == NULL))
    {
        msg_Err(reader, "XML reader not found");
        vlc_object_delete(reader);
        return NULL;
    }
    return reader;
}