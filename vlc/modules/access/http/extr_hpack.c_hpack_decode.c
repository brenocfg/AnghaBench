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
struct hpack_decoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hpack_decode_hdr (struct hpack_decoder*,int /*<<< orphan*/  const**,size_t*,char**,char**) ; 

int hpack_decode(struct hpack_decoder *dec, const uint8_t *data,
                 size_t length, char *headers[][2], unsigned max)
{
    unsigned count = 0;

    while (length > 0)
    {
        char *name, *value;
        int val = hpack_decode_hdr(dec, &data, &length, &name, &value);
        if (val < 0)
            goto error;

        assert((name == NULL) == (value == NULL));
        if (name == NULL)
            continue;

        if (count < max)
        {
            headers[count][0] = name;
            headers[count][1] = value;
        }
        else
        {
            free(value);
            free(name);
        }
        count++;
    }
    return count;

error:
    while (count > 0)
    {
        count--;
        free(headers[count][1]);
        free(headers[count][0]);
    }
    return -1;
}