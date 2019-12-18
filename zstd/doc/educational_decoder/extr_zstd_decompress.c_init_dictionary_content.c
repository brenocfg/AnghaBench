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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  istream_t ;
struct TYPE_3__ {int /*<<< orphan*/  content_size; int /*<<< orphan*/  content; } ;
typedef  TYPE_1__ dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 int /*<<< orphan*/ * IO_get_read_ptr (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_istream_len (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_dictionary_content(dictionary_t *const dict,
                                    istream_t *const in) {
    // Copy in the content
    dict->content_size = IO_istream_len(in);
    dict->content = malloc(dict->content_size);
    if (!dict->content) {
        BAD_ALLOC();
    }

    const u8 *const content = IO_get_read_ptr(in, dict->content_size);

    memcpy(dict->content, content, dict->content_size);
}