#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct hllhdr {scalar_t__ encoding; int /*<<< orphan*/  registers; } ;
typedef  struct hllhdr uint8_t ;
typedef  struct hllhdr* sds ;
struct TYPE_22__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_23__ {int argc; TYPE_7__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ client ;
struct TYPE_26__ {char* ptr; } ;
struct TYPE_25__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_24__ {int /*<<< orphan*/  czero; int /*<<< orphan*/  cone; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  HLL_DENSE_GET_REGISTER (struct hllhdr,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HLL_HDR_SIZE ; 
 int HLL_REGISTERS ; 
 scalar_t__ HLL_SPARSE ; 
 scalar_t__ HLL_SPARSE_IS_XZERO (struct hllhdr*) ; 
 scalar_t__ HLL_SPARSE_IS_ZERO (struct hllhdr*) ; 
 int HLL_SPARSE_VAL_LEN (struct hllhdr*) ; 
 int HLL_SPARSE_VAL_VALUE (struct hllhdr*) ; 
 int HLL_SPARSE_XZERO_LEN (struct hllhdr*) ; 
 int HLL_SPARSE_ZERO_LEN (struct hllhdr*) ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_2__*,struct hllhdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,struct hllhdr) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyStatus (TYPE_2__*,char*) ; 
 TYPE_1__* dbUnshareStringValue (int /*<<< orphan*/ ,TYPE_7__*,TYPE_1__*) ; 
 scalar_t__ hllSparseToDense (TYPE_1__*) ; 
 int /*<<< orphan*/  invalid_hll_err ; 
 scalar_t__ isHLLObjectOrReply (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* lookupKeyWrite (int /*<<< orphan*/ ,TYPE_7__*) ; 
 struct hllhdr* sdscatprintf (struct hllhdr*,char*,int,...) ; 
 struct hllhdr* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (struct hllhdr*) ; 
 int /*<<< orphan*/  sdslen (struct hllhdr*) ; 
 int /*<<< orphan*/  sdsnew (int /*<<< orphan*/ ) ; 
 struct hllhdr* sdstrim (struct hllhdr*,char*) ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

void pfdebugCommand(client *c) {
    char *cmd = c->argv[1]->ptr;
    struct hllhdr *hdr;
    robj *o;
    int j;

    o = lookupKeyWrite(c->db,c->argv[2]);
    if (o == NULL) {
        addReplyError(c,"The specified key does not exist");
        return;
    }
    if (isHLLObjectOrReply(c,o) != C_OK) return;
    o = dbUnshareStringValue(c->db,c->argv[2],o);
    hdr = o->ptr;

    /* PFDEBUG GETREG <key> */
    if (!strcasecmp(cmd,"getreg")) {
        if (c->argc != 3) goto arityerr;

        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == C_ERR) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
            server.dirty++; /* Force propagation on encoding change. */
        }

        hdr = o->ptr;
        addReplyArrayLen(c,HLL_REGISTERS);
        for (j = 0; j < HLL_REGISTERS; j++) {
            uint8_t val;

            HLL_DENSE_GET_REGISTER(val,hdr->registers,j);
            addReplyLongLong(c,val);
        }
    }
    /* PFDEBUG DECODE <key> */
    else if (!strcasecmp(cmd,"decode")) {
        if (c->argc != 3) goto arityerr;

        uint8_t *p = o->ptr, *end = p+sdslen(o->ptr);
        sds decoded = sdsempty();

        if (hdr->encoding != HLL_SPARSE) {
            addReplyError(c,"HLL encoding is not sparse");
            return;
        }

        p += HLL_HDR_SIZE;
        while(p < end) {
            int runlen, regval;

            if (HLL_SPARSE_IS_ZERO(p)) {
                runlen = HLL_SPARSE_ZERO_LEN(p);
                p++;
                decoded = sdscatprintf(decoded,"z:%d ",runlen);
            } else if (HLL_SPARSE_IS_XZERO(p)) {
                runlen = HLL_SPARSE_XZERO_LEN(p);
                p += 2;
                decoded = sdscatprintf(decoded,"Z:%d ",runlen);
            } else {
                runlen = HLL_SPARSE_VAL_LEN(p);
                regval = HLL_SPARSE_VAL_VALUE(p);
                p++;
                decoded = sdscatprintf(decoded,"v:%d,%d ",regval,runlen);
            }
        }
        decoded = sdstrim(decoded," ");
        addReplyBulkCBuffer(c,decoded,sdslen(decoded));
        sdsfree(decoded);
    }
    /* PFDEBUG ENCODING <key> */
    else if (!strcasecmp(cmd,"encoding")) {
        char *encodingstr[2] = {"dense","sparse"};
        if (c->argc != 3) goto arityerr;

        addReplyStatus(c,encodingstr[hdr->encoding]);
    }
    /* PFDEBUG TODENSE <key> */
    else if (!strcasecmp(cmd,"todense")) {
        int conv = 0;
        if (c->argc != 3) goto arityerr;

        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == C_ERR) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
            conv = 1;
            server.dirty++; /* Force propagation on encoding change. */
        }
        addReply(c,conv ? shared.cone : shared.czero);
    } else {
        addReplyErrorFormat(c,"Unknown PFDEBUG subcommand '%s'", cmd);
    }
    return;

arityerr:
    addReplyErrorFormat(c,
        "Wrong number of arguments for the '%s' subcommand",cmd);
}