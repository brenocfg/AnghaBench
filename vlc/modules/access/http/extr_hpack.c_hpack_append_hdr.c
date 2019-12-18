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
struct hpack_decoder {char** table; int entries; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hpack_decode_evict (struct hpack_decoder*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char** realloc (char**,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int hpack_append_hdr(struct hpack_decoder *dec,
                            const char *name, const char *value)
{
    size_t namelen = strlen(name), valuelen = strlen(value);
    char *entry = malloc(namelen + valuelen + 2);
    if (entry == NULL)
        return -1;
    memcpy(entry, name, namelen + 1);
    memcpy(entry + namelen + 1, value, valuelen + 1);

    char **newtab = realloc(dec->table,
                            sizeof (dec->table[0]) * (dec->entries + 1));
    if (newtab == NULL)
    {
        free(entry);
        return -1;
    }

    dec->table = newtab;
    dec->table[dec->entries] = entry;
    dec->entries++;
    dec->size += 32 + namelen + valuelen;

    hpack_decode_evict(dec);
    return 0;
}