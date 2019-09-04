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
struct inf_file {scalar_t__ nb_fields; scalar_t__ alloc_fields; struct field* fields; } ;
struct field {int /*<<< orphan*/  const* text; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 struct field* grow_array (struct field*,scalar_t__*,int) ; 

__attribute__((used)) static struct field *add_field( struct inf_file *file, const WCHAR *text )
{
    struct field *field;

    if (file->nb_fields >= file->alloc_fields)
    {
        if (!(file->fields = grow_array( file->fields, &file->alloc_fields,
                                         sizeof(file->fields[0]) ))) return NULL;
    }
    field = &file->fields[file->nb_fields++];
    field->text = text;
    return field;
}