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
typedef  int /*<<< orphan*/  type_t ;
typedef  enum type_context { ____Placeholder_type_context } type_context ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TDT_ALL_TYPES ; 
#define  TGT_BASIC 129 
#define  TGT_ENUM 128 
 int /*<<< orphan*/  print_start_tfs_comment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/ *) ; 
 int typegen_detect_type (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tfsoff (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_nonsimple_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,unsigned int,unsigned int*) ; 
 unsigned int write_simple_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int write_pointer_tfs(FILE *file, const attr_list_t *attrs,
                                      type_t *type, unsigned int ref_offset,
                                      enum type_context context,
                                      unsigned int *typestring_offset)
{
    unsigned int offset = *typestring_offset;
    type_t *ref = type_pointer_get_ref(type);

    print_start_tfs_comment(file, type, offset);
    update_tfsoff(type, offset, file);

    switch (typegen_detect_type(ref, attrs, TDT_ALL_TYPES))
    {
    case TGT_BASIC:
    case TGT_ENUM:
        *typestring_offset += write_simple_pointer(file, attrs, type, context);
        break;
    default:
        if (ref_offset)
            write_nonsimple_pointer(file, attrs, type, context, ref_offset, typestring_offset);
        break;
    }

    return offset;
}