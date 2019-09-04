#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  long long uint64_t ;
struct bitfieldOp {size_t offset; long long i64; int opcode; int owtype; int bits; int sign; } ;
struct TYPE_28__ {unsigned char* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  long long int64_t ;
struct TYPE_29__ {int argc; TYPE_3__* db; TYPE_4__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_33__ {int dirty; } ;
struct TYPE_32__ {int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_31__ {char* ptr; } ;
struct TYPE_30__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BFOVERFLOW_FAIL ; 
 int BFOVERFLOW_SAT ; 
 int BFOVERFLOW_WRAP ; 
 int BITFIELDOP_GET ; 
 int BITFIELDOP_INCRBY ; 
 int BITFIELDOP_SET ; 
 scalar_t__ C_OK ; 
 int LONG_STR_SIZE ; 
 int /*<<< orphan*/  NOTIFY_STRING ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,long long) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 int checkSignedBitfieldOverflow (long long,long long,int,int,long long*) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int checkUnsignedBitfieldOverflow (long long,long long,int,int,long long*) ; 
 scalar_t__ getBitOffsetFromArgument (TYPE_2__*,TYPE_4__*,size_t*,int,int) ; 
 scalar_t__ getBitfieldTypeFromArgument (TYPE_2__*,TYPE_4__*,int*,int*) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_2__*,TYPE_4__*,long long*,int /*<<< orphan*/ *) ; 
 unsigned char* getObjectReadOnlyString (TYPE_1__*,long*,char*) ; 
 long long getSignedBitfield (unsigned char*,size_t,int) ; 
 long long getUnsignedBitfield (unsigned char*,size_t,int) ; 
 TYPE_1__* lookupKeyRead (TYPE_3__*,TYPE_4__*) ; 
 TYPE_1__* lookupStringForBitCommand (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  setSignedBitfield (unsigned char*,size_t,int,long long) ; 
 int /*<<< orphan*/  setUnsignedBitfield (unsigned char*,size_t,int,long long) ; 
 TYPE_5__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  zfree (struct bitfieldOp*) ; 
 struct bitfieldOp* zrealloc (struct bitfieldOp*,int) ; 

void bitfieldCommand(client *c) {
    robj *o;
    size_t bitoffset;
    int j, numops = 0, changes = 0;
    struct bitfieldOp *ops = NULL; /* Array of ops to execute at end. */
    int owtype = BFOVERFLOW_WRAP; /* Overflow type. */
    int readonly = 1;
    size_t highest_write_offset = 0;

    for (j = 2; j < c->argc; j++) {
        int remargs = c->argc-j-1; /* Remaining args other than current. */
        char *subcmd = c->argv[j]->ptr; /* Current command name. */
        int opcode; /* Current operation code. */
        long long i64 = 0;  /* Signed SET value. */
        int sign = 0; /* Signed or unsigned type? */
        int bits = 0; /* Bitfield width in bits. */

        if (!strcasecmp(subcmd,"get") && remargs >= 2)
            opcode = BITFIELDOP_GET;
        else if (!strcasecmp(subcmd,"set") && remargs >= 3)
            opcode = BITFIELDOP_SET;
        else if (!strcasecmp(subcmd,"incrby") && remargs >= 3)
            opcode = BITFIELDOP_INCRBY;
        else if (!strcasecmp(subcmd,"overflow") && remargs >= 1) {
            char *owtypename = c->argv[j+1]->ptr;
            j++;
            if (!strcasecmp(owtypename,"wrap"))
                owtype = BFOVERFLOW_WRAP;
            else if (!strcasecmp(owtypename,"sat"))
                owtype = BFOVERFLOW_SAT;
            else if (!strcasecmp(owtypename,"fail"))
                owtype = BFOVERFLOW_FAIL;
            else {
                addReplyError(c,"Invalid OVERFLOW type specified");
                zfree(ops);
                return;
            }
            continue;
        } else {
            addReply(c,shared.syntaxerr);
            zfree(ops);
            return;
        }

        /* Get the type and offset arguments, common to all the ops. */
        if (getBitfieldTypeFromArgument(c,c->argv[j+1],&sign,&bits) != C_OK) {
            zfree(ops);
            return;
        }

        if (getBitOffsetFromArgument(c,c->argv[j+2],&bitoffset,1,bits) != C_OK){
            zfree(ops);
            return;
        }

        if (opcode != BITFIELDOP_GET) {
            readonly = 0;
            if (highest_write_offset < bitoffset + bits - 1)
                highest_write_offset = bitoffset + bits - 1;
            /* INCRBY and SET require another argument. */
            if (getLongLongFromObjectOrReply(c,c->argv[j+3],&i64,NULL) != C_OK){
                zfree(ops);
                return;
            }
        }

        /* Populate the array of operations we'll process. */
        ops = zrealloc(ops,sizeof(*ops)*(numops+1));
        ops[numops].offset = bitoffset;
        ops[numops].i64 = i64;
        ops[numops].opcode = opcode;
        ops[numops].owtype = owtype;
        ops[numops].bits = bits;
        ops[numops].sign = sign;
        numops++;

        j += 3 - (opcode == BITFIELDOP_GET);
    }

    if (readonly) {
        /* Lookup for read is ok if key doesn't exit, but errors
         * if it's not a string. */
        o = lookupKeyRead(c->db,c->argv[1]);
        if (o != NULL && checkType(c,o,OBJ_STRING)) {
            zfree(ops);
            return;
        }
    } else {
        /* Lookup by making room up to the farest bit reached by
         * this operation. */
        if ((o = lookupStringForBitCommand(c,
            highest_write_offset)) == NULL) {
            zfree(ops);
            return;
        }
    }

    addReplyArrayLen(c,numops);

    /* Actually process the operations. */
    for (j = 0; j < numops; j++) {
        struct bitfieldOp *thisop = ops+j;

        /* Execute the operation. */
        if (thisop->opcode == BITFIELDOP_SET ||
            thisop->opcode == BITFIELDOP_INCRBY)
        {
            /* SET and INCRBY: We handle both with the same code path
             * for simplicity. SET return value is the previous value so
             * we need fetch & store as well. */

            /* We need two different but very similar code paths for signed
             * and unsigned operations, since the set of functions to get/set
             * the integers and the used variables types are different. */
            if (thisop->sign) {
                int64_t oldval, newval, wrapped, retval;
                int overflow;

                oldval = getSignedBitfield(o->ptr,thisop->offset,
                        thisop->bits);

                if (thisop->opcode == BITFIELDOP_INCRBY) {
                    newval = oldval + thisop->i64;
                    overflow = checkSignedBitfieldOverflow(oldval,
                            thisop->i64,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    retval = newval;
                } else {
                    newval = thisop->i64;
                    overflow = checkSignedBitfieldOverflow(newval,
                            0,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    retval = oldval;
                }

                /* On overflow of type is "FAIL", don't write and return
                 * NULL to signal the condition. */
                if (!(overflow && thisop->owtype == BFOVERFLOW_FAIL)) {
                    addReplyLongLong(c,retval);
                    setSignedBitfield(o->ptr,thisop->offset,
                                      thisop->bits,newval);
                } else {
                    addReplyNull(c);
                }
            } else {
                uint64_t oldval, newval, wrapped, retval;
                int overflow;

                oldval = getUnsignedBitfield(o->ptr,thisop->offset,
                        thisop->bits);

                if (thisop->opcode == BITFIELDOP_INCRBY) {
                    newval = oldval + thisop->i64;
                    overflow = checkUnsignedBitfieldOverflow(oldval,
                            thisop->i64,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    retval = newval;
                } else {
                    newval = thisop->i64;
                    overflow = checkUnsignedBitfieldOverflow(newval,
                            0,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    retval = oldval;
                }
                /* On overflow of type is "FAIL", don't write and return
                 * NULL to signal the condition. */
                if (!(overflow && thisop->owtype == BFOVERFLOW_FAIL)) {
                    addReplyLongLong(c,retval);
                    setUnsignedBitfield(o->ptr,thisop->offset,
                                        thisop->bits,newval);
                } else {
                    addReplyNull(c);
                }
            }
            changes++;
        } else {
            /* GET */
            unsigned char buf[9];
            long strlen = 0;
            unsigned char *src = NULL;
            char llbuf[LONG_STR_SIZE];

            if (o != NULL)
                src = getObjectReadOnlyString(o,&strlen,llbuf);

            /* For GET we use a trick: before executing the operation
             * copy up to 9 bytes to a local buffer, so that we can easily
             * execute up to 64 bit operations that are at actual string
             * object boundaries. */
            memset(buf,0,9);
            int i;
            size_t byte = thisop->offset >> 3;
            for (i = 0; i < 9; i++) {
                if (src == NULL || i+byte >= (size_t)strlen) break;
                buf[i] = src[i+byte];
            }

            /* Now operate on the copied buffer which is guaranteed
             * to be zero-padded. */
            if (thisop->sign) {
                int64_t val = getSignedBitfield(buf,thisop->offset-(byte*8),
                                            thisop->bits);
                addReplyLongLong(c,val);
            } else {
                uint64_t val = getUnsignedBitfield(buf,thisop->offset-(byte*8),
                                            thisop->bits);
                addReplyLongLong(c,val);
            }
        }
    }

    if (changes) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
        server.dirty += changes;
    }
    zfree(ops);
}