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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int hpack_decode_byte_huffman (int /*<<< orphan*/  const*,int*) ; 
 unsigned char* malloc (size_t) ; 

__attribute__((used)) static char *hpack_decode_str_huffman(const uint8_t *data, size_t length)
{
    unsigned char *str = malloc(length * 2 + 1);
    if (str == NULL)
        return NULL;

    size_t len = 0;
    int bit_offset = -8 * length;
    data += length;

    for (;;)
    {
        int c = hpack_decode_byte_huffman(data, &bit_offset);
        if (c < 0)
        {
            errno = EINVAL;
            goto error;
        }

        /* NOTE: EOS (256) is converted to nul terminator */
        str[len++] = c;

        if (c == 256)
            break;
    }

    return (char *)str;

error:
    free(str);
    return NULL;
}