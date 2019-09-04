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
typedef  enum join_op { ____Placeholder_join_op } join_op ;
typedef  int /*<<< orphan*/ ******** WCHAR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int JOIN_OP_APPEND ; 
 int JOIN_OP_PREPEND ; 
 int JOIN_OP_REPLACE ; 
 scalar_t__ join_multi_string_values (int,int /*<<< orphan*/ **********,int,int /*<<< orphan*/ **********,int,int*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ **********) ; 
 int /*<<< orphan*/ ************** split_multi_string_values (int /*<<< orphan*/ ******** const*,int,int*) ; 

__attribute__((used)) static BYTE *build_multi_string_value( BYTE *old_value, DWORD old_size,
                                       BYTE *new_value, DWORD new_size, DWORD *size )
{
    DWORD i, old_len = 0, new_len = 0, old_count = 0, new_count = 0;
    const WCHAR *new_ptr = NULL, *old_ptr = NULL;
    enum join_op op = JOIN_OP_REPLACE;
    WCHAR **old = NULL, **new = NULL;
    BYTE *ret;

    if (new_size / sizeof(WCHAR) - 1 > 1)
    {
        new_ptr = (const WCHAR *)new_value;
        new_len = new_size / sizeof(WCHAR) - 1;

        if (!new_ptr[0] && new_ptr[new_len - 1])
        {
            op = JOIN_OP_APPEND;
            new_len--;
            new_ptr++;
        }
        else if (new_ptr[0] && !new_ptr[new_len - 1])
        {
            op = JOIN_OP_PREPEND;
            new_len--;
        }
        else if (new_len > 2 && !new_ptr[0] && !new_ptr[new_len - 1])
        {
            op = JOIN_OP_REPLACE;
            new_len -= 2;
            new_ptr++;
        }
        new = split_multi_string_values( new_ptr, new_len, &new_count );
    }
    if (old_size / sizeof(WCHAR) - 1 > 1)
    {
        old_ptr = (const WCHAR *)old_value;
        old_len = old_size / sizeof(WCHAR) - 1;
        old = split_multi_string_values( old_ptr, old_len, &old_count );
    }
    ret = (BYTE *)join_multi_string_values( op, old, old_count, new, new_count, size );
    for (i = 0; i < old_count; i++) msi_free( old[i] );
    for (i = 0; i < new_count; i++) msi_free( new[i] );
    msi_free( old );
    msi_free( new );
    return ret;
}