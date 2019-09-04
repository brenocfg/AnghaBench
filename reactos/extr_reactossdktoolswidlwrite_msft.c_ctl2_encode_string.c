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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int ctl2_encode_string(
	const char *string,        /* [I] The string to encode. */
	char **result)             /* [O] A pointer to a pointer to receive the encoded string. */
{
    int length;
    static char converted_string[0x104];
    int offset;

    length = strlen(string);
    memcpy(converted_string + 2, string, length);

#ifdef WORDS_BIGENDIAN
    converted_string[1] = length & 0xff;
    converted_string[0] = (length >> 8) & 0xff;
#else
    converted_string[0] = length & 0xff;
    converted_string[1] = (length >> 8) & 0xff;
#endif

    if(length < 3) { /* strings of this length are padded with up to 8 bytes incl the 2 byte length */
        for(offset = 0; offset < 4; offset++)
            converted_string[length + offset + 2] = 0x57;
        length += 4;
    }
    for (offset = (4 - (length + 2)) & 3; offset; offset--) converted_string[length + offset + 1] = 0x57;

    *result = converted_string;

    return (length + 5) & ~3;
}