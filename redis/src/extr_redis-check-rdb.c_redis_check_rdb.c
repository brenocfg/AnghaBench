#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_18__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_19__ {scalar_t__ cksum; int /*<<< orphan*/  update_cksum; } ;
typedef  TYPE_2__ rio ;
struct TYPE_21__ {int key_type; char* error; scalar_t__ error_set; void* doing; TYPE_1__* key; int /*<<< orphan*/  expires; int /*<<< orphan*/  already_expired; int /*<<< orphan*/  keys; TYPE_2__* rio; } ;
struct TYPE_20__ {scalar_t__ rdb_checksum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RDBFLAGS_NONE ; 
 void* RDB_CHECK_DOING_CHECK_SUM ; 
 void* RDB_CHECK_DOING_READ_AUX ; 
 void* RDB_CHECK_DOING_READ_EXPIRE ; 
 void* RDB_CHECK_DOING_READ_KEY ; 
 void* RDB_CHECK_DOING_READ_LEN ; 
 void* RDB_CHECK_DOING_READ_OBJECT_VALUE ; 
 void* RDB_CHECK_DOING_READ_TYPE ; 
 scalar_t__ RDB_LENERR ; 
 int RDB_OPCODE_AUX ; 
 int RDB_OPCODE_EOF ; 
 int RDB_OPCODE_EXPIRETIME ; 
 int RDB_OPCODE_EXPIRETIME_MS ; 
 int RDB_OPCODE_FREQ ; 
 int RDB_OPCODE_IDLE ; 
 int RDB_OPCODE_RESIZEDB ; 
 int RDB_OPCODE_SELECTDB ; 
 int RDB_VERSION ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memrev64ifbe (scalar_t__*) ; 
 long long mstime () ; 
 int /*<<< orphan*/  rdbCheckError (char*,...) ; 
 int /*<<< orphan*/  rdbCheckInfo (char*,...) ; 
 int /*<<< orphan*/  rdbIsObjectType (int) ; 
 scalar_t__ rdbLoadLen (TYPE_2__*,int /*<<< orphan*/ *) ; 
 long long rdbLoadMillisecondTime (TYPE_2__*,int) ; 
 TYPE_1__* rdbLoadObject (int,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rdbLoadProgressCallback ; 
 TYPE_1__* rdbLoadStringObject (TYPE_2__*) ; 
 long long rdbLoadTime (TYPE_2__*) ; 
 int rdbLoadType (TYPE_2__*) ; 
 TYPE_7__ rdbstate ; 
 scalar_t__ rioGetReadError (TYPE_2__*) ; 
 int /*<<< orphan*/  rioInitWithFile (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ rioRead (TYPE_2__*,...) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  startLoadingFile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stopLoading (int) ; 

int redis_check_rdb(char *rdbfilename, FILE *fp) {
    uint64_t dbid;
    int type, rdbver;
    char buf[1024];
    long long expiretime, now = mstime();
    static rio rdb; /* Pointed by global struct riostate. */

    int closefile = (fp == NULL);
    if (fp == NULL && (fp = fopen(rdbfilename,"r")) == NULL) return 1;

    rioInitWithFile(&rdb,fp);
    rdbstate.rio = &rdb;
    rdb.update_cksum = rdbLoadProgressCallback;
    if (rioRead(&rdb,buf,9) == 0) goto eoferr;
    buf[9] = '\0';
    if (memcmp(buf,"REDIS",5) != 0) {
        rdbCheckError("Wrong signature trying to load DB from file");
        goto err;
    }
    rdbver = atoi(buf+5);
    if (rdbver < 1 || rdbver > RDB_VERSION) {
        rdbCheckError("Can't handle RDB format version %d",rdbver);
        goto err;
    }

    expiretime = -1;
    startLoadingFile(fp, rdbfilename, RDBFLAGS_NONE);
    while(1) {
        robj *key, *val;

        /* Read type. */
        rdbstate.doing = RDB_CHECK_DOING_READ_TYPE;
        if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;

        /* Handle special types. */
        if (type == RDB_OPCODE_EXPIRETIME) {
            rdbstate.doing = RDB_CHECK_DOING_READ_EXPIRE;
            /* EXPIRETIME: load an expire associated with the next key
             * to load. Note that after loading an expire we need to
             * load the actual type, and continue. */
            expiretime = rdbLoadTime(&rdb);
            expiretime *= 1000;
            if (rioGetReadError(&rdb)) goto eoferr;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_EXPIRETIME_MS) {
            /* EXPIRETIME_MS: milliseconds precision expire times introduced
             * with RDB v3. Like EXPIRETIME but no with more precision. */
            rdbstate.doing = RDB_CHECK_DOING_READ_EXPIRE;
            expiretime = rdbLoadMillisecondTime(&rdb, rdbver);
            if (rioGetReadError(&rdb)) goto eoferr;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_FREQ) {
            /* FREQ: LFU frequency. */
            uint8_t byte;
            if (rioRead(&rdb,&byte,1) == 0) goto eoferr;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_IDLE) {
            /* IDLE: LRU idle time. */
            if (rdbLoadLen(&rdb,NULL) == RDB_LENERR) goto eoferr;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_EOF) {
            /* EOF: End of file, exit the main loop. */
            break;
        } else if (type == RDB_OPCODE_SELECTDB) {
            /* SELECTDB: Select the specified database. */
            rdbstate.doing = RDB_CHECK_DOING_READ_LEN;
            if ((dbid = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                goto eoferr;
            rdbCheckInfo("Selecting DB ID %d", dbid);
            continue; /* Read type again. */
        } else if (type == RDB_OPCODE_RESIZEDB) {
            /* RESIZEDB: Hint about the size of the keys in the currently
             * selected data base, in order to avoid useless rehashing. */
            uint64_t db_size, expires_size;
            rdbstate.doing = RDB_CHECK_DOING_READ_LEN;
            if ((db_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                goto eoferr;
            if ((expires_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                goto eoferr;
            continue; /* Read type again. */
        } else if (type == RDB_OPCODE_AUX) {
            /* AUX: generic string-string fields. Use to add state to RDB
             * which is backward compatible. Implementations of RDB loading
             * are requierd to skip AUX fields they don't understand.
             *
             * An AUX field is composed of two strings: key and value. */
            robj *auxkey, *auxval;
            rdbstate.doing = RDB_CHECK_DOING_READ_AUX;
            if ((auxkey = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
            if ((auxval = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;

            rdbCheckInfo("AUX FIELD %s = '%s'",
                (char*)auxkey->ptr, (char*)auxval->ptr);
            decrRefCount(auxkey);
            decrRefCount(auxval);
            continue; /* Read type again. */
        } else {
            if (!rdbIsObjectType(type)) {
                rdbCheckError("Invalid object type: %d", type);
                goto err;
            }
            rdbstate.key_type = type;
        }

        /* Read key */
        rdbstate.doing = RDB_CHECK_DOING_READ_KEY;
        if ((key = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
        rdbstate.key = key;
        rdbstate.keys++;
        /* Read value */
        rdbstate.doing = RDB_CHECK_DOING_READ_OBJECT_VALUE;
        if ((val = rdbLoadObject(type,&rdb,key)) == NULL) goto eoferr;
        /* Check if the key already expired. */
        if (expiretime != -1 && expiretime < now)
            rdbstate.already_expired++;
        if (expiretime != -1) rdbstate.expires++;
        rdbstate.key = NULL;
        decrRefCount(key);
        decrRefCount(val);
        rdbstate.key_type = -1;
        expiretime = -1;
    }
    /* Verify the checksum if RDB version is >= 5 */
    if (rdbver >= 5 && server.rdb_checksum) {
        uint64_t cksum, expected = rdb.cksum;

        rdbstate.doing = RDB_CHECK_DOING_CHECK_SUM;
        if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
        memrev64ifbe(&cksum);
        if (cksum == 0) {
            rdbCheckInfo("RDB file was saved with checksum disabled: no check performed.");
        } else if (cksum != expected) {
            rdbCheckError("RDB CRC error");
            goto err;
        } else {
            rdbCheckInfo("Checksum OK");
        }
    }

    if (closefile) fclose(fp);
    stopLoading(1);
    return 0;

eoferr: /* unexpected end of file is handled here with a fatal exit */
    if (rdbstate.error_set) {
        rdbCheckError(rdbstate.error);
    } else {
        rdbCheckError("Unexpected EOF reading RDB file");
    }
err:
    if (closefile) fclose(fp);
    stopLoading(0);
    return 1;
}