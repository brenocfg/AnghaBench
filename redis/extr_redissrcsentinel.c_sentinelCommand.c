#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_2__ ;
typedef  struct TYPE_47__   TYPE_20__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_46__ {int flags; long long info_refresh; int /*<<< orphan*/  info; int /*<<< orphan*/ * slaves; int /*<<< orphan*/  name; int /*<<< orphan*/  quorum; int /*<<< orphan*/ * sentinels; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_48__ {char* ip; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ sentinelAddr ;
typedef  int /*<<< orphan*/  sds ;
typedef  long long mstime_t ;
typedef  int /*<<< orphan*/  ip ;
struct TYPE_49__ {int /*<<< orphan*/ * valDestructor; } ;
typedef  TYPE_3__ dictType ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_50__ {int argc; TYPE_14__** argv; } ;
typedef  TYPE_4__ client ;
struct TYPE_51__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  czero; int /*<<< orphan*/  cone; } ;
struct TYPE_47__ {int /*<<< orphan*/  simfailure_flags; int /*<<< orphan*/ * masters; int /*<<< orphan*/  tilt; } ;
struct TYPE_45__ {scalar_t__ ptr; } ;

/* Variables and functions */
 scalar_t__ ANET_ERR ; 
 scalar_t__ C_OK ; 
#define  EBUSY 129 
#define  EINVAL 128 
 int /*<<< orphan*/  LL_WARNING ; 
 int NET_IP_STR_LEN ; 
 int /*<<< orphan*/  SENTINEL_GENERATE_EVENT ; 
 int SENTINEL_ISQR_NOAUTH ; 
 int SENTINEL_ISQR_NOQUORUM ; 
 int SENTINEL_ISQR_OK ; 
 int /*<<< orphan*/  SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION ; 
 int /*<<< orphan*/  SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION ; 
 int /*<<< orphan*/  SENTINEL_SIMFAILURE_NONE ; 
 int SRI_FAILOVER_IN_PROGRESS ; 
 int SRI_FORCE_FAILOVER ; 
 int SRI_MASTER ; 
 int SRI_S_DOWN ; 
 int /*<<< orphan*/  addReply (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_4__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyDictOfRedisInstances (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyError (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_4__*,long long) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_4__*) ; 
 int /*<<< orphan*/  addReplyNullArray (TYPE_4__*) ; 
 int /*<<< orphan*/  addReplySds (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySentinelRedisInstance (TYPE_4__*,TYPE_1__*) ; 
 scalar_t__ anetResolveIP (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 TYPE_1__* createSentinelRedisInstance (scalar_t__,int,scalar_t__,long,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * dictCreate (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ *) ; 
 TYPE_1__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ *) ; 
 int errno ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_4__*,TYPE_14__*,long*,char*) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_4__*,TYPE_14__*,long long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* getSentinelRedisInstanceByAddrAndRunID (int /*<<< orphan*/ *,scalar_t__,long,int /*<<< orphan*/ *) ; 
 TYPE_3__ instancesDictType ; 
 long long mstime () ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_20__ sentinel ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  sentinelFlushConfig () ; 
 TYPE_2__* sentinelGetCurrentMasterAddress (TYPE_1__*) ; 
 TYPE_1__* sentinelGetMasterByName (scalar_t__) ; 
 TYPE_1__* sentinelGetMasterByNameOrReplyError (TYPE_4__*,TYPE_14__*) ; 
 int sentinelIsQuorumReachable (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  sentinelPendingScriptsCommand (TYPE_4__*) ; 
 long long sentinelResetMastersByPattern (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sentinelSelectSlave (TYPE_1__*) ; 
 int /*<<< orphan*/  sentinelSetCommand (TYPE_4__*) ; 
 int /*<<< orphan*/  sentinelStartFailover (TYPE_1__*) ; 
 char* sentinelVoteLeader (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_5__ shared ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void sentinelCommand(client *c) {
    if (!strcasecmp(c->argv[1]->ptr,"masters")) {
        /* SENTINEL MASTERS */
        if (c->argc != 2) goto numargserr;
        addReplyDictOfRedisInstances(c,sentinel.masters);
    } else if (!strcasecmp(c->argv[1]->ptr,"master")) {
        /* SENTINEL MASTER <name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
            == NULL) return;
        addReplySentinelRedisInstance(c,ri);
    } else if (!strcasecmp(c->argv[1]->ptr,"slaves") ||
               !strcasecmp(c->argv[1]->ptr,"replicas"))
    {
        /* SENTINEL REPLICAS <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
            return;
        addReplyDictOfRedisInstances(c,ri->slaves);
    } else if (!strcasecmp(c->argv[1]->ptr,"sentinels")) {
        /* SENTINEL SENTINELS <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
            return;
        addReplyDictOfRedisInstances(c,ri->sentinels);
    } else if (!strcasecmp(c->argv[1]->ptr,"is-master-down-by-addr")) {
        /* SENTINEL IS-MASTER-DOWN-BY-ADDR <ip> <port> <current-epoch> <runid>
         *
         * Arguments:
         *
         * ip and port are the ip and port of the master we want to be
         * checked by Sentinel. Note that the command will not check by
         * name but just by master, in theory different Sentinels may monitor
         * differnet masters with the same name.
         *
         * current-epoch is needed in order to understand if we are allowed
         * to vote for a failover leader or not. Each Sentinel can vote just
         * one time per epoch.
         *
         * runid is "*" if we are not seeking for a vote from the Sentinel
         * in order to elect the failover leader. Otherwise it is set to the
         * runid we want the Sentinel to vote if it did not already voted.
         */
        sentinelRedisInstance *ri;
        long long req_epoch;
        uint64_t leader_epoch = 0;
        char *leader = NULL;
        long port;
        int isdown = 0;

        if (c->argc != 6) goto numargserr;
        if (getLongFromObjectOrReply(c,c->argv[3],&port,NULL) != C_OK ||
            getLongLongFromObjectOrReply(c,c->argv[4],&req_epoch,NULL)
                                                              != C_OK)
            return;
        ri = getSentinelRedisInstanceByAddrAndRunID(sentinel.masters,
            c->argv[2]->ptr,port,NULL);

        /* It exists? Is actually a master? Is subjectively down? It's down.
         * Note: if we are in tilt mode we always reply with "0". */
        if (!sentinel.tilt && ri && (ri->flags & SRI_S_DOWN) &&
                                    (ri->flags & SRI_MASTER))
            isdown = 1;

        /* Vote for the master (or fetch the previous vote) if the request
         * includes a runid, otherwise the sender is not seeking for a vote. */
        if (ri && ri->flags & SRI_MASTER && strcasecmp(c->argv[5]->ptr,"*")) {
            leader = sentinelVoteLeader(ri,(uint64_t)req_epoch,
                                            c->argv[5]->ptr,
                                            &leader_epoch);
        }

        /* Reply with a three-elements multi-bulk reply:
         * down state, leader, vote epoch. */
        addReplyArrayLen(c,3);
        addReply(c, isdown ? shared.cone : shared.czero);
        addReplyBulkCString(c, leader ? leader : "*");
        addReplyLongLong(c, (long long)leader_epoch);
        if (leader) sdsfree(leader);
    } else if (!strcasecmp(c->argv[1]->ptr,"reset")) {
        /* SENTINEL RESET <pattern> */
        if (c->argc != 3) goto numargserr;
        addReplyLongLong(c,sentinelResetMastersByPattern(c->argv[2]->ptr,SENTINEL_GENERATE_EVENT));
    } else if (!strcasecmp(c->argv[1]->ptr,"get-master-addr-by-name")) {
        /* SENTINEL GET-MASTER-ADDR-BY-NAME <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        ri = sentinelGetMasterByName(c->argv[2]->ptr);
        if (ri == NULL) {
            addReplyNullArray(c);
        } else {
            sentinelAddr *addr = sentinelGetCurrentMasterAddress(ri);

            addReplyArrayLen(c,2);
            addReplyBulkCString(c,addr->ip);
            addReplyBulkLongLong(c,addr->port);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover")) {
        /* SENTINEL FAILOVER <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
            return;
        if (ri->flags & SRI_FAILOVER_IN_PROGRESS) {
            addReplySds(c,sdsnew("-INPROG Failover already in progress\r\n"));
            return;
        }
        if (sentinelSelectSlave(ri) == NULL) {
            addReplySds(c,sdsnew("-NOGOODSLAVE No suitable replica to promote\r\n"));
            return;
        }
        serverLog(LL_WARNING,"Executing user requested FAILOVER of '%s'",
            ri->name);
        sentinelStartFailover(ri);
        ri->flags |= SRI_FORCE_FAILOVER;
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
        /* SENTINEL PENDING-SCRIPTS */

        if (c->argc != 2) goto numargserr;
        sentinelPendingScriptsCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"monitor")) {
        /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
        sentinelRedisInstance *ri;
        long quorum, port;
        char ip[NET_IP_STR_LEN];

        if (c->argc != 6) goto numargserr;
        if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
            != C_OK) return;
        if (getLongFromObjectOrReply(c,c->argv[4],&port,"Invalid port")
            != C_OK) return;

        if (quorum <= 0) {
            addReplyError(c, "Quorum must be 1 or greater.");
            return;
        }

        /* Make sure the IP field is actually a valid IP before passing it
         * to createSentinelRedisInstance(), otherwise we may trigger a
         * DNS lookup at runtime. */
        if (anetResolveIP(NULL,c->argv[3]->ptr,ip,sizeof(ip)) == ANET_ERR) {
            addReplyError(c,"Invalid IP address specified");
            return;
        }

        /* Parameters are valid. Try to create the master instance. */
        ri = createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
                c->argv[3]->ptr,port,quorum,NULL);
        if (ri == NULL) {
            switch(errno) {
            case EBUSY:
                addReplyError(c,"Duplicated master name");
                break;
            case EINVAL:
                addReplyError(c,"Invalid port number");
                break;
            default:
                addReplyError(c,"Unspecified error adding the instance");
                break;
            }
        } else {
            sentinelFlushConfig();
            sentinelEvent(LL_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
            addReply(c,shared.ok);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"flushconfig")) {
        if (c->argc != 2) goto numargserr;
        sentinelFlushConfig();
        addReply(c,shared.ok);
        return;
    } else if (!strcasecmp(c->argv[1]->ptr,"remove")) {
        /* SENTINEL REMOVE <name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
            == NULL) return;
        sentinelEvent(LL_WARNING,"-monitor",ri,"%@");
        dictDelete(sentinel.masters,c->argv[2]->ptr);
        sentinelFlushConfig();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"ckquorum")) {
        /* SENTINEL CKQUORUM <name> */
        sentinelRedisInstance *ri;
        int usable;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
            == NULL) return;
        int result = sentinelIsQuorumReachable(ri,&usable);
        if (result == SENTINEL_ISQR_OK) {
            addReplySds(c, sdscatfmt(sdsempty(),
                "+OK %i usable Sentinels. Quorum and failover authorization "
                "can be reached\r\n",usable));
        } else {
            sds e = sdscatfmt(sdsempty(),
                "-NOQUORUM %i usable Sentinels. ",usable);
            if (result & SENTINEL_ISQR_NOQUORUM)
                e = sdscat(e,"Not enough available Sentinels to reach the"
                             " specified quorum for this master");
            if (result & SENTINEL_ISQR_NOAUTH) {
                if (result & SENTINEL_ISQR_NOQUORUM) e = sdscat(e,". ");
                e = sdscat(e, "Not enough available Sentinels to reach the"
                              " majority and authorize a failover");
            }
            e = sdscat(e,"\r\n");
            addReplySds(c,e);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc < 3) goto numargserr;
        sentinelSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"info-cache")) {
        /* SENTINEL INFO-CACHE <name> */
        if (c->argc < 2) goto numargserr;
        mstime_t now = mstime();

        /* Create an ad-hoc dictionary type so that we can iterate
         * a dictionary composed of just the master groups the user
         * requested. */
        dictType copy_keeper = instancesDictType;
        copy_keeper.valDestructor = NULL;
        dict *masters_local = sentinel.masters;
        if (c->argc > 2) {
            masters_local = dictCreate(&copy_keeper, NULL);

            for (int i = 2; i < c->argc; i++) {
                sentinelRedisInstance *ri;
                ri = sentinelGetMasterByName(c->argv[i]->ptr);
                if (!ri) continue; /* ignore non-existing names */
                dictAdd(masters_local, ri->name, ri);
            }
        }

        /* Reply format:
         *   1.) master name
         *   2.) 1.) info from master
         *       2.) info from replica
         *       ...
         *   3.) other master name
         *   ...
         */
        addReplyArrayLen(c,dictSize(masters_local) * 2);

        dictIterator  *di;
        dictEntry *de;
        di = dictGetIterator(masters_local);
        while ((de = dictNext(di)) != NULL) {
            sentinelRedisInstance *ri = dictGetVal(de);
            addReplyBulkCBuffer(c,ri->name,strlen(ri->name));
            addReplyArrayLen(c,dictSize(ri->slaves) + 1); /* +1 for self */
            addReplyArrayLen(c,2);
            addReplyLongLong(c, now - ri->info_refresh);
            if (ri->info)
                addReplyBulkCBuffer(c,ri->info,sdslen(ri->info));
            else
                addReplyNull(c);

            dictIterator *sdi;
            dictEntry *sde;
            sdi = dictGetIterator(ri->slaves);
            while ((sde = dictNext(sdi)) != NULL) {
                sentinelRedisInstance *sri = dictGetVal(sde);
                addReplyArrayLen(c,2);
                addReplyLongLong(c, now - sri->info_refresh);
                if (sri->info)
                    addReplyBulkCBuffer(c,sri->info,sdslen(sri->info));
                else
                    addReplyNull(c);
            }
            dictReleaseIterator(sdi);
        }
        dictReleaseIterator(di);
        if (masters_local != sentinel.masters) dictRelease(masters_local);
    } else if (!strcasecmp(c->argv[1]->ptr,"simulate-failure")) {
        /* SENTINEL SIMULATE-FAILURE <flag> <flag> ... <flag> */
        int j;

        sentinel.simfailure_flags = SENTINEL_SIMFAILURE_NONE;
        for (j = 2; j < c->argc; j++) {
            if (!strcasecmp(c->argv[j]->ptr,"crash-after-election")) {
                sentinel.simfailure_flags |=
                    SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION;
                serverLog(LL_WARNING,"Failure simulation: this Sentinel "
                    "will crash after being successfully elected as failover "
                    "leader");
            } else if (!strcasecmp(c->argv[j]->ptr,"crash-after-promotion")) {
                sentinel.simfailure_flags |=
                    SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
                serverLog(LL_WARNING,"Failure simulation: this Sentinel "
                    "will crash after promoting the selected replica to master");
            } else if (!strcasecmp(c->argv[j]->ptr,"help")) {
                addReplyArrayLen(c,2);
                addReplyBulkCString(c,"crash-after-election");
                addReplyBulkCString(c,"crash-after-promotion");
            } else {
                addReplyError(c,"Unknown failure simulation specified");
                return;
            }
        }
        addReply(c,shared.ok);
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
    }
    return;

numargserr:
    addReplyErrorFormat(c,"Wrong number of arguments for 'sentinel %s'",
                          (char*)c->argv[1]->ptr);
}