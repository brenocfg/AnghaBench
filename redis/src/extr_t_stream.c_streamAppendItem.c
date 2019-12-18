#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_21__ {scalar_t__ ms; scalar_t__ seq; } ;
typedef  TYPE_1__ streamID ;
struct TYPE_22__ {TYPE_1__ last_id; int /*<<< orphan*/  length; int /*<<< orphan*/  rax; } ;
typedef  TYPE_2__ stream ;
typedef  scalar_t__ sds ;
struct TYPE_23__ {scalar_t__ ptr; } ;
typedef  TYPE_3__ robj ;
typedef  int /*<<< orphan*/  rax_key ;
struct TYPE_24__ {unsigned char* data; int key_len; int /*<<< orphan*/  key; } ;
typedef  TYPE_4__ raxIterator ;
typedef  scalar_t__ int64_t ;
struct TYPE_20__ {size_t stream_node_max_bytes; scalar_t__ stream_node_max_entries; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int LP_INTBUF_SIZE ; 
 int STREAM_ITEM_FLAG_NONE ; 
 int STREAM_ITEM_FLAG_SAMEFIELDS ; 
 unsigned char* lpAppend (unsigned char*,unsigned char*,size_t) ; 
 unsigned char* lpAppendInteger (unsigned char*,scalar_t__) ; 
 size_t lpBytes (unsigned char*) ; 
 unsigned char* lpFirst (unsigned char*) ; 
 unsigned char* lpGet (unsigned char*,scalar_t__*,unsigned char*) ; 
 scalar_t__ lpGetInteger (unsigned char*) ; 
 unsigned char* lpNew () ; 
 unsigned char* lpNext (unsigned char*,unsigned char*) ; 
 unsigned char* lpReplaceInteger (unsigned char*,unsigned char**,scalar_t__) ; 
 scalar_t__ memcmp (unsigned char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ raxNext (TYPE_4__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_4__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_4__*) ; 
 size_t sdslen (scalar_t__) ; 
 TYPE_15__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 scalar_t__ streamCompareID (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  streamDecodeID (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  streamEncodeID (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  streamNextID (TYPE_1__*,TYPE_1__*) ; 

int streamAppendItem(stream *s, robj **argv, int64_t numfields, streamID *added_id, streamID *use_id) {
    
    /* Generate the new entry ID. */
    streamID id;
    if (use_id)
        id = *use_id;
    else
        streamNextID(&s->last_id,&id);

    /* Check that the new ID is greater than the last entry ID
     * or return an error. Automatically generated IDs might
     * overflow (and wrap-around) when incrementing the sequence 
       part. */
    if (streamCompareID(&id,&s->last_id) <= 0) return C_ERR;

    /* Add the new entry. */
    raxIterator ri;
    raxStart(&ri,s->rax);
    raxSeek(&ri,"$",NULL,0);

    size_t lp_bytes = 0;        /* Total bytes in the tail listpack. */
    unsigned char *lp = NULL;   /* Tail listpack pointer. */

    /* Get a reference to the tail node listpack. */
    if (raxNext(&ri)) {
        lp = ri.data;
        lp_bytes = lpBytes(lp);
    }
    raxStop(&ri);

    /* We have to add the key into the radix tree in lexicographic order,
     * to do so we consider the ID as a single 128 bit number written in
     * big endian, so that the most significant bytes are the first ones. */
    uint64_t rax_key[2];    /* Key in the radix tree containing the listpack.*/
    streamID master_id;     /* ID of the master entry in the listpack. */

    /* Create a new listpack and radix tree node if needed. Note that when
     * a new listpack is created, we populate it with a "master entry". This
     * is just a set of fields that is taken as references in order to compress
     * the stream entries that we'll add inside the listpack.
     *
     * Note that while we use the first added entry fields to create
     * the master entry, the first added entry is NOT represented in the master
     * entry, which is a stand alone object. But of course, the first entry
     * will compress well because it's used as reference.
     *
     * The master entry is composed like in the following example:
     *
     * +-------+---------+------------+---------+--/--+---------+---------+-+
     * | count | deleted | num-fields | field_1 | field_2 | ... | field_N |0|
     * +-------+---------+------------+---------+--/--+---------+---------+-+
     *
     * count and deleted just represent respectively the total number of
     * entries inside the listpack that are valid, and marked as deleted
     * (deleted flag in the entry flags set). So the total number of items
     * actually inside the listpack (both deleted and not) is count+deleted.
     *
     * The real entries will be encoded with an ID that is just the
     * millisecond and sequence difference compared to the key stored at
     * the radix tree node containing the listpack (delta encoding), and
     * if the fields of the entry are the same as the master entry fields, the
     * entry flags will specify this fact and the entry fields and number
     * of fields will be omitted (see later in the code of this function).
     *
     * The "0" entry at the end is the same as the 'lp-count' entry in the
     * regular stream entries (see below), and marks the fact that there are
     * no more entries, when we scan the stream from right to left. */

    /* First of all, check if we can append to the current macro node or
     * if we need to switch to the next one. 'lp' will be set to NULL if
     * the current node is full. */
    if (lp != NULL) {
        if (server.stream_node_max_bytes &&
            lp_bytes >= server.stream_node_max_bytes)
        {
            lp = NULL;
        } else if (server.stream_node_max_entries) {
            int64_t count = lpGetInteger(lpFirst(lp));
            if (count >= server.stream_node_max_entries) lp = NULL;
        }
    }

    int flags = STREAM_ITEM_FLAG_NONE;
    if (lp == NULL || lp_bytes >= server.stream_node_max_bytes) {
        master_id = id;
        streamEncodeID(rax_key,&id);
        /* Create the listpack having the master entry ID and fields. */
        lp = lpNew();
        lp = lpAppendInteger(lp,1); /* One item, the one we are adding. */
        lp = lpAppendInteger(lp,0); /* Zero deleted so far. */
        lp = lpAppendInteger(lp,numfields);
        for (int64_t i = 0; i < numfields; i++) {
            sds field = argv[i*2]->ptr;
            lp = lpAppend(lp,(unsigned char*)field,sdslen(field));
        }
        lp = lpAppendInteger(lp,0); /* Master entry zero terminator. */
        raxInsert(s->rax,(unsigned char*)&rax_key,sizeof(rax_key),lp,NULL);
        /* The first entry we insert, has obviously the same fields of the
         * master entry. */
        flags |= STREAM_ITEM_FLAG_SAMEFIELDS;
    } else {
        serverAssert(ri.key_len == sizeof(rax_key));
        memcpy(rax_key,ri.key,sizeof(rax_key));

        /* Read the master ID from the radix tree key. */
        streamDecodeID(rax_key,&master_id);
        unsigned char *lp_ele = lpFirst(lp);

        /* Update count and skip the deleted fields. */
        int64_t count = lpGetInteger(lp_ele);
        lp = lpReplaceInteger(lp,&lp_ele,count+1);
        lp_ele = lpNext(lp,lp_ele); /* seek deleted. */
        lp_ele = lpNext(lp,lp_ele); /* seek master entry num fields. */

        /* Check if the entry we are adding, have the same fields
         * as the master entry. */
        int64_t master_fields_count = lpGetInteger(lp_ele);
        lp_ele = lpNext(lp,lp_ele);
        if (numfields == master_fields_count) {
            int64_t i;
            for (i = 0; i < master_fields_count; i++) {
                sds field = argv[i*2]->ptr;
                int64_t e_len;
                unsigned char buf[LP_INTBUF_SIZE];
                unsigned char *e = lpGet(lp_ele,&e_len,buf);
                /* Stop if there is a mismatch. */
                if (sdslen(field) != (size_t)e_len ||
                    memcmp(e,field,e_len) != 0) break;
                lp_ele = lpNext(lp,lp_ele);
            }
            /* All fields are the same! We can compress the field names
             * setting a single bit in the flags. */
            if (i == master_fields_count) flags |= STREAM_ITEM_FLAG_SAMEFIELDS;
        }
    }

    /* Populate the listpack with the new entry. We use the following
     * encoding:
     *
     * +-----+--------+----------+-------+-------+-/-+-------+-------+--------+
     * |flags|entry-id|num-fields|field-1|value-1|...|field-N|value-N|lp-count|
     * +-----+--------+----------+-------+-------+-/-+-------+-------+--------+
     *
     * However if the SAMEFIELD flag is set, we have just to populate
     * the entry with the values, so it becomes:
     *
     * +-----+--------+-------+-/-+-------+--------+
     * |flags|entry-id|value-1|...|value-N|lp-count|
     * +-----+--------+-------+-/-+-------+--------+
     *
     * The entry-id field is actually two separated fields: the ms
     * and seq difference compared to the master entry.
     *
     * The lp-count field is a number that states the number of listpack pieces
     * that compose the entry, so that it's possible to travel the entry
     * in reverse order: we can just start from the end of the listpack, read
     * the entry, and jump back N times to seek the "flags" field to read
     * the stream full entry. */
    lp = lpAppendInteger(lp,flags);
    lp = lpAppendInteger(lp,id.ms - master_id.ms);
    lp = lpAppendInteger(lp,id.seq - master_id.seq);
    if (!(flags & STREAM_ITEM_FLAG_SAMEFIELDS))
        lp = lpAppendInteger(lp,numfields);
    for (int64_t i = 0; i < numfields; i++) {
        sds field = argv[i*2]->ptr, value = argv[i*2+1]->ptr;
        if (!(flags & STREAM_ITEM_FLAG_SAMEFIELDS))
            lp = lpAppend(lp,(unsigned char*)field,sdslen(field));
        lp = lpAppend(lp,(unsigned char*)value,sdslen(value));
    }
    /* Compute and store the lp-count field. */
    int64_t lp_count = numfields;
    lp_count += 3; /* Add the 3 fixed fields flags + ms-diff + seq-diff. */
    if (!(flags & STREAM_ITEM_FLAG_SAMEFIELDS)) {
        /* If the item is not compressed, it also has the fields other than
         * the values, and an additional num-fileds field. */
        lp_count += numfields+1;
    }
    lp = lpAppendInteger(lp,lp_count);

    /* Insert back into the tree in order to update the listpack pointer. */
    if (ri.data != lp)
        raxInsert(s->rax,(unsigned char*)&rax_key,sizeof(rax_key),lp,NULL);
    s->length++;
    s->last_id = id;
    if (added_id) *added_id = id;
    return C_OK;
}