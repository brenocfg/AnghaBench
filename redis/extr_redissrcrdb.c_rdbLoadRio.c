#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
typedef  unsigned int uint64_t ;
typedef  scalar_t__ time_t ;
struct TYPE_28__ {char* ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_29__ {unsigned int cksum; int /*<<< orphan*/  max_processing_chunk; int /*<<< orphan*/  update_cksum; } ;
typedef  TYPE_2__ rio ;
struct TYPE_30__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  dict; } ;
typedef  TYPE_3__ redisDb ;
struct TYPE_31__ {int repl_id_is_set; void* repl_offset; int /*<<< orphan*/  repl_id; void* repl_stream_db; } ;
typedef  TYPE_4__ rdbSaveInfo ;
typedef  int /*<<< orphan*/  moduleType ;
struct TYPE_32__ {scalar_t__ rdb_checksum; int /*<<< orphan*/ * masterhost; int /*<<< orphan*/  lua; TYPE_3__* db; scalar_t__ dbnum; int /*<<< orphan*/  loading_process_events_interval_bytes; } ;

/* Variables and functions */
 scalar_t__ CONFIG_RUN_ID_SIZE ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 long long LRU_CLOCK () ; 
 unsigned int RDB_LENERR ; 
 int RDB_OPCODE_AUX ; 
 int RDB_OPCODE_EOF ; 
 int RDB_OPCODE_EXPIRETIME ; 
 int RDB_OPCODE_EXPIRETIME_MS ; 
 int RDB_OPCODE_FREQ ; 
 int RDB_OPCODE_IDLE ; 
 int RDB_OPCODE_MODULE_AUX ; 
 int RDB_OPCODE_RESIZEDB ; 
 int RDB_OPCODE_SELECTDB ; 
 int RDB_VERSION ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  dbAdd (TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  dictExpand (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * luaCreateFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memrev64ifbe (unsigned int*) ; 
 int /*<<< orphan*/ * moduleTypeLookupModuleByID (unsigned int) ; 
 int /*<<< orphan*/  moduleTypeNameByID (char*,unsigned int) ; 
 long long mstime () ; 
 int /*<<< orphan*/  objectSetLRUOrLFU (TYPE_1__*,long long,long long,long long) ; 
 int /*<<< orphan*/  rdbCheckMode ; 
 int /*<<< orphan*/  rdbExitReportCorruptRDB (char*,...) ; 
 TYPE_1__* rdbLoadCheckModuleValue (TYPE_2__*,char*) ; 
 unsigned int rdbLoadLen (TYPE_2__*,int /*<<< orphan*/ *) ; 
 long long rdbLoadMillisecondTime (TYPE_2__*,int) ; 
 TYPE_1__* rdbLoadObject (int,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rdbLoadProgressCallback ; 
 TYPE_1__* rdbLoadStringObject (TYPE_2__*) ; 
 long long rdbLoadTime (TYPE_2__*) ; 
 int rdbLoadType (TYPE_2__*) ; 
 scalar_t__ rioRead (TYPE_2__*,...) ; 
 scalar_t__ sdslen (char*) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  setExpire (int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*,long long) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 void* strtoll (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int rdbLoadRio(rio *rdb, rdbSaveInfo *rsi, int loading_aof) {
    uint64_t dbid;
    int type, rdbver;
    redisDb *db = server.db+0;
    char buf[1024];

    rdb->update_cksum = rdbLoadProgressCallback;
    rdb->max_processing_chunk = server.loading_process_events_interval_bytes;
    if (rioRead(rdb,buf,9) == 0) goto eoferr;
    buf[9] = '\0';
    if (memcmp(buf,"REDIS",5) != 0) {
        serverLog(LL_WARNING,"Wrong signature trying to load DB from file");
        errno = EINVAL;
        return C_ERR;
    }
    rdbver = atoi(buf+5);
    if (rdbver < 1 || rdbver > RDB_VERSION) {
        serverLog(LL_WARNING,"Can't handle RDB format version %d",rdbver);
        errno = EINVAL;
        return C_ERR;
    }

    /* Key-specific attributes, set by opcodes before the key type. */
    long long lru_idle = -1, lfu_freq = -1, expiretime = -1, now = mstime();
    long long lru_clock = LRU_CLOCK();

    while(1) {
        robj *key, *val;

        /* Read type. */
        if ((type = rdbLoadType(rdb)) == -1) goto eoferr;

        /* Handle special types. */
        if (type == RDB_OPCODE_EXPIRETIME) {
            /* EXPIRETIME: load an expire associated with the next key
             * to load. Note that after loading an expire we need to
             * load the actual type, and continue. */
            expiretime = rdbLoadTime(rdb);
            expiretime *= 1000;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_EXPIRETIME_MS) {
            /* EXPIRETIME_MS: milliseconds precision expire times introduced
             * with RDB v3. Like EXPIRETIME but no with more precision. */
            expiretime = rdbLoadMillisecondTime(rdb,rdbver);
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_FREQ) {
            /* FREQ: LFU frequency. */
            uint8_t byte;
            if (rioRead(rdb,&byte,1) == 0) goto eoferr;
            lfu_freq = byte;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_IDLE) {
            /* IDLE: LRU idle time. */
            uint64_t qword;
            if ((qword = rdbLoadLen(rdb,NULL)) == RDB_LENERR) goto eoferr;
            lru_idle = qword;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_EOF) {
            /* EOF: End of file, exit the main loop. */
            break;
        } else if (type == RDB_OPCODE_SELECTDB) {
            /* SELECTDB: Select the specified database. */
            if ((dbid = rdbLoadLen(rdb,NULL)) == RDB_LENERR) goto eoferr;
            if (dbid >= (unsigned)server.dbnum) {
                serverLog(LL_WARNING,
                    "FATAL: Data file was created with a Redis "
                    "server configured to handle more than %d "
                    "databases. Exiting\n", server.dbnum);
                exit(1);
            }
            db = server.db+dbid;
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_RESIZEDB) {
            /* RESIZEDB: Hint about the size of the keys in the currently
             * selected data base, in order to avoid useless rehashing. */
            uint64_t db_size, expires_size;
            if ((db_size = rdbLoadLen(rdb,NULL)) == RDB_LENERR)
                goto eoferr;
            if ((expires_size = rdbLoadLen(rdb,NULL)) == RDB_LENERR)
                goto eoferr;
            dictExpand(db->dict,db_size);
            dictExpand(db->expires,expires_size);
            continue; /* Read next opcode. */
        } else if (type == RDB_OPCODE_AUX) {
            /* AUX: generic string-string fields. Use to add state to RDB
             * which is backward compatible. Implementations of RDB loading
             * are requierd to skip AUX fields they don't understand.
             *
             * An AUX field is composed of two strings: key and value. */
            robj *auxkey, *auxval;
            if ((auxkey = rdbLoadStringObject(rdb)) == NULL) goto eoferr;
            if ((auxval = rdbLoadStringObject(rdb)) == NULL) goto eoferr;

            if (((char*)auxkey->ptr)[0] == '%') {
                /* All the fields with a name staring with '%' are considered
                 * information fields and are logged at startup with a log
                 * level of NOTICE. */
                serverLog(LL_NOTICE,"RDB '%s': %s",
                    (char*)auxkey->ptr,
                    (char*)auxval->ptr);
            } else if (!strcasecmp(auxkey->ptr,"repl-stream-db")) {
                if (rsi) rsi->repl_stream_db = atoi(auxval->ptr);
            } else if (!strcasecmp(auxkey->ptr,"repl-id")) {
                if (rsi && sdslen(auxval->ptr) == CONFIG_RUN_ID_SIZE) {
                    memcpy(rsi->repl_id,auxval->ptr,CONFIG_RUN_ID_SIZE+1);
                    rsi->repl_id_is_set = 1;
                }
            } else if (!strcasecmp(auxkey->ptr,"repl-offset")) {
                if (rsi) rsi->repl_offset = strtoll(auxval->ptr,NULL,10);
            } else if (!strcasecmp(auxkey->ptr,"lua")) {
                /* Load the script back in memory. */
                if (luaCreateFunction(NULL,server.lua,auxval) == NULL) {
                    rdbExitReportCorruptRDB(
                        "Can't load Lua script from RDB file! "
                        "BODY: %s", auxval->ptr);
                }
            } else if (!strcasecmp(auxkey->ptr,"redis-ver")) {
                serverLog(LL_NOTICE,"Loading RDB produced by version %s",
                    (char*)auxval->ptr);
            } else if (!strcasecmp(auxkey->ptr,"ctime")) {
                time_t age = time(NULL)-strtol(auxval->ptr,NULL,10);
                if (age < 0) age = 0;
                serverLog(LL_NOTICE,"RDB age %ld seconds",
                    (unsigned long) age);
            } else if (!strcasecmp(auxkey->ptr,"used-mem")) {
                long long usedmem = strtoll(auxval->ptr,NULL,10);
                serverLog(LL_NOTICE,"RDB memory usage when created %.2f Mb",
                    (double) usedmem / (1024*1024));
            } else if (!strcasecmp(auxkey->ptr,"aof-preamble")) {
                long long haspreamble = strtoll(auxval->ptr,NULL,10);
                if (haspreamble) serverLog(LL_NOTICE,"RDB has an AOF tail");
            } else if (!strcasecmp(auxkey->ptr,"redis-bits")) {
                /* Just ignored. */
            } else {
                /* We ignore fields we don't understand, as by AUX field
                 * contract. */
                serverLog(LL_DEBUG,"Unrecognized RDB AUX field: '%s'",
                    (char*)auxkey->ptr);
            }

            decrRefCount(auxkey);
            decrRefCount(auxval);
            continue; /* Read type again. */
        } else if (type == RDB_OPCODE_MODULE_AUX) {
            /* This is just for compatibility with the future: we have plans
             * to add the ability for modules to store anything in the RDB
             * file, like data that is not related to the Redis key space.
             * Such data will potentially be stored both before and after the
             * RDB keys-values section. For this reason since RDB version 9,
             * we have the ability to read a MODULE_AUX opcode followed by an
             * identifier of the module, and a serialized value in "MODULE V2"
             * format. */
            uint64_t moduleid = rdbLoadLen(rdb,NULL);
            moduleType *mt = moduleTypeLookupModuleByID(moduleid);
            char name[10];
            moduleTypeNameByID(name,moduleid);

            if (!rdbCheckMode && mt == NULL) {
                /* Unknown module. */
                serverLog(LL_WARNING,"The RDB file contains AUX module data I can't load: no matching module '%s'", name);
                exit(1);
            } else if (!rdbCheckMode && mt != NULL) {
                /* This version of Redis actually does not know what to do
                 * with modules AUX data... */
                serverLog(LL_WARNING,"The RDB file contains AUX module data I can't load for the module '%s'. Probably you want to use a newer version of Redis which implements aux data callbacks", name);
                exit(1);
            } else {
                /* RDB check mode. */
                robj *aux = rdbLoadCheckModuleValue(rdb,name);
                decrRefCount(aux);
            }
        }

        /* Read key */
        if ((key = rdbLoadStringObject(rdb)) == NULL) goto eoferr;
        /* Read value */
        if ((val = rdbLoadObject(type,rdb,key)) == NULL) goto eoferr;
        /* Check if the key already expired. This function is used when loading
         * an RDB file from disk, either at startup, or when an RDB was
         * received from the master. In the latter case, the master is
         * responsible for key expiry. If we would expire keys here, the
         * snapshot taken by the master may not be reflected on the slave. */
        if (server.masterhost == NULL && !loading_aof && expiretime != -1 && expiretime < now) {
            decrRefCount(key);
            decrRefCount(val);
        } else {
            /* Add the new object in the hash table */
            dbAdd(db,key,val);

            /* Set the expire time if needed */
            if (expiretime != -1) setExpire(NULL,db,key,expiretime);

            /* Set usage information (for eviction). */
            objectSetLRUOrLFU(val,lfu_freq,lru_idle,lru_clock);

            /* Decrement the key refcount since dbAdd() will take its
             * own reference. */
            decrRefCount(key);
        }

        /* Reset the state that is key-specified and is populated by
         * opcodes before the key, so that we start from scratch again. */
        expiretime = -1;
        lfu_freq = -1;
        lru_idle = -1;
    }
    /* Verify the checksum if RDB version is >= 5 */
    if (rdbver >= 5) {
        uint64_t cksum, expected = rdb->cksum;

        if (rioRead(rdb,&cksum,8) == 0) goto eoferr;
        if (server.rdb_checksum) {
            memrev64ifbe(&cksum);
            if (cksum == 0) {
                serverLog(LL_WARNING,"RDB file was saved with checksum disabled: no check performed.");
            } else if (cksum != expected) {
                serverLog(LL_WARNING,"Wrong RDB checksum. Aborting now.");
                rdbExitReportCorruptRDB("RDB CRC error");
            }
        }
    }
    return C_OK;

eoferr: /* unexpected end of file is handled here with a fatal exit */
    serverLog(LL_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
    rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
    return C_ERR; /* Just to avoid warning */
}