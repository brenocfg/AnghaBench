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
typedef  scalar_t__ int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hpack_append_hdr (struct hpack_decoder*,char*,char*) ; 
 scalar_t__ hpack_decode_int (int,int /*<<< orphan*/  const**,size_t*) ; 
 char* hpack_decode_str (int /*<<< orphan*/  const**,size_t*) ; 
 char* hpack_lookup_name (struct hpack_decoder*,scalar_t__) ; 

__attribute__((used)) static int hpack_decode_hdr_index(struct hpack_decoder *dec,
                                  const uint8_t **restrict datap,
                                  size_t *restrict lengthp,
                                  char **restrict namep,
                                  char **restrict valuep)
{
    int_fast32_t idx = hpack_decode_int(6, datap, lengthp);
    if (idx < 0)
        return -1;

    char *name;

    if (idx != 0)
        name = hpack_lookup_name(dec, idx);
    else
        name = hpack_decode_str(datap, lengthp);
    if (name == NULL)
        return -1;

    char *value = hpack_decode_str(datap, lengthp);
    if (value == NULL)
    {
        free(name);
        return -1;
    }

    if (hpack_append_hdr(dec, name, value))
    {
        free(value);
        free(name);
        return -1;
    }

    *namep = name;
    *valuep = value;
    return 0;
}