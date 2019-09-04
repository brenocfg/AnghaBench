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
struct IFD_entry {int type; int count; size_t value; scalar_t__ id; } ;
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  size_t ULONG ;

/* Variables and functions */
#define  IFD_ASCII 139 
#define  IFD_BYTE 138 
#define  IFD_DOUBLE 137 
#define  IFD_FLOAT 136 
#define  IFD_LONG 135 
#define  IFD_RATIONAL 134 
#define  IFD_SBYTE 133 
#define  IFD_SHORT 132 
#define  IFD_SLONG 131 
#define  IFD_SRATIONAL 130 
#define  IFD_SSHORT 129 
#define  IFD_UNDEFINED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* ulong_bswap (size_t) ; 
 int /*<<< orphan*/  ulonglong_bswap (int /*<<< orphan*/ ) ; 
 void* ushort_bswap (scalar_t__) ; 

__attribute__((used)) static void byte_swap_ifd_data(char *data)
{
    USHORT number_of_entries, i;
    struct IFD_entry *entry;
    char *data_start = data;

    number_of_entries = *(USHORT *)data;
    *(USHORT *)data = ushort_bswap(*(USHORT *)data);
    data += sizeof(USHORT);

    for (i = 0; i < number_of_entries; i++)
    {
        entry = (struct IFD_entry *)data;

        switch (entry->type)
        {
        case IFD_BYTE:
        case IFD_SBYTE:
        case IFD_ASCII:
        case IFD_UNDEFINED:
            if (entry->count > 4)
                entry->value = ulong_bswap(entry->value);
            break;

        case IFD_SHORT:
        case IFD_SSHORT:
            if (entry->count > 2)
            {
                ULONG j, count = entry->count;
                USHORT *us = (USHORT *)(data_start + entry->value);
                if (!count) count = 1;
                for (j = 0; j < count; j++)
                    us[j] = ushort_bswap(us[j]);

                entry->value = ulong_bswap(entry->value);
            }
            else
            {
                ULONG j, count = entry->count;
                USHORT *us = (USHORT *)&entry->value;
                if (!count) count = 1;
                for (j = 0; j < count; j++)
                    us[j] = ushort_bswap(us[j]);
            }
            break;

        case IFD_LONG:
        case IFD_SLONG:
        case IFD_FLOAT:
            if (entry->count > 1)
            {
                ULONG j, count = entry->count;
                ULONG *ul = (ULONG *)(data_start + entry->value);
                if (!count) count = 1;
                for (j = 0; j < count; j++)
                    ul[j] = ulong_bswap(ul[j]);
            }
            entry->value = ulong_bswap(entry->value);
            break;

        case IFD_RATIONAL:
        case IFD_SRATIONAL:
            {
                ULONG j;
                ULONG *ul = (ULONG *)(data_start + entry->value);
                for (j = 0; j < entry->count * 2; j++)
                    ul[j] = ulong_bswap(ul[j]);
            }
            entry->value = ulong_bswap(entry->value);
            break;

        case IFD_DOUBLE:
            {
                ULONG j;
                ULONGLONG *ull = (ULONGLONG *)(data_start + entry->value);
                for (j = 0; j < entry->count; j++)
                    ull[j] = ulonglong_bswap(ull[j]);
            }
            entry->value = ulong_bswap(entry->value);
            break;

        default:
            assert(0);
            break;
        }

        entry->id = ushort_bswap(entry->id);
        entry->type = ushort_bswap(entry->type);
        entry->count = ulong_bswap(entry->count);
        data += sizeof(*entry);
    }
}