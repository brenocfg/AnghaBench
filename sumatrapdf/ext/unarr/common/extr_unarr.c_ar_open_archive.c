#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* off64_t ;
typedef  int /*<<< orphan*/  ar_stream ;
typedef  int /*<<< orphan*/  ar_parse_entry_fn ;
typedef  int /*<<< orphan*/  ar_get_global_comment_fn ;
typedef  int /*<<< orphan*/  ar_entry_uncompress_fn ;
typedef  int /*<<< orphan*/  ar_entry_get_name_fn ;
typedef  int /*<<< orphan*/  ar_archive_close_fn ;
struct TYPE_5__ {void* entry_offset_next; void* entry_offset_first; int /*<<< orphan*/ * stream; int /*<<< orphan*/  get_comment; int /*<<< orphan*/  uncompress; int /*<<< orphan*/  get_name; int /*<<< orphan*/  parse_entry; int /*<<< orphan*/  close; } ;
typedef  TYPE_1__ ar_archive ;

/* Variables and functions */
 TYPE_1__* malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

ar_archive *ar_open_archive(ar_stream *stream, size_t struct_size, ar_archive_close_fn close, ar_parse_entry_fn parse_entry,
                            ar_entry_get_name_fn get_name, ar_entry_uncompress_fn uncompress, ar_get_global_comment_fn get_comment,
                            off64_t first_entry_offset)
{
    ar_archive *ar = malloc(struct_size);
    if (!ar)
        return NULL;
    memset(ar, 0, struct_size);
    ar->close = close;
    ar->parse_entry = parse_entry;
    ar->get_name = get_name;
    ar->uncompress = uncompress;
    ar->get_comment = get_comment;
    ar->stream = stream;
    ar->entry_offset_first = first_entry_offset;
    ar->entry_offset_next = first_entry_offset;
    return ar;
}