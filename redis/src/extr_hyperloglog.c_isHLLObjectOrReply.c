#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hllhdr {char* magic; scalar_t__ encoding; } ;
struct TYPE_6__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ HLL_DENSE ; 
 int HLL_DENSE_SIZE ; 
 scalar_t__ HLL_MAX_ENCODING ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReplySds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsEncodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int stringObjectLen (TYPE_1__*) ; 

int isHLLObjectOrReply(client *c, robj *o) {
    struct hllhdr *hdr;

    /* Key exists, check type */
    if (checkType(c,o,OBJ_STRING))
        return C_ERR; /* Error already sent. */

    if (!sdsEncodedObject(o)) goto invalid;
    if (stringObjectLen(o) < sizeof(*hdr)) goto invalid;
    hdr = o->ptr;

    /* Magic should be "HYLL". */
    if (hdr->magic[0] != 'H' || hdr->magic[1] != 'Y' ||
        hdr->magic[2] != 'L' || hdr->magic[3] != 'L') goto invalid;

    if (hdr->encoding > HLL_MAX_ENCODING) goto invalid;

    /* Dense representation string length should match exactly. */
    if (hdr->encoding == HLL_DENSE &&
        stringObjectLen(o) != HLL_DENSE_SIZE) goto invalid;

    /* All tests passed. */
    return C_OK;

invalid:
    addReplySds(c,
        sdsnew("-WRONGTYPE Key is not a valid "
               "HyperLogLog string value.\r\n"));
    return C_ERR;
}