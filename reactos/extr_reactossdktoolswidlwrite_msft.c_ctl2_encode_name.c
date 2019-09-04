#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int varflags; int /*<<< orphan*/  lcid; } ;
struct TYPE_5__ {TYPE_1__ typelib_header; } ;
typedef  TYPE_2__ msft_typelib_t ;

/* Variables and functions */
 int lhash_val_of_name_sys (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int ctl2_encode_name(
	msft_typelib_t *typelib,   /* [I] The typelib to operate against (used for LCID only). */
	const char *name,          /* [I] The name string to encode. */
	char **result)             /* [O] A pointer to a pointer to receive the encoded name. */
{
    int length;
    static char converted_name[0x104];
    int offset;
    int value;

    length = strlen(name);
    memcpy(converted_name + 4, name, length);

    converted_name[length + 4] = 0;


    value = lhash_val_of_name_sys(typelib->typelib_header.varflags & 0x0f, typelib->typelib_header.lcid, converted_name + 4);

#ifdef WORDS_BIGENDIAN
    converted_name[3] = length & 0xff;
    converted_name[2] = 0x00;
    converted_name[1] = value;
    converted_name[0] = value >> 8;
#else
    converted_name[0] = length & 0xff;
    converted_name[1] = 0x00;
    converted_name[2] = value;
    converted_name[3] = value >> 8;
#endif

    for (offset = (4 - length) & 3; offset; offset--) converted_name[length + offset + 3] = 0x57;

    *result = converted_name;

    return (length + 7) & ~3;
}