#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_4__ {int type; char* str; int len; char* integer; size_t elements; struct TYPE_4__** element; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_5__ {int eval_ldb_end; char* mb_delim; int /*<<< orphan*/  output; int /*<<< orphan*/  eval_ldb; int /*<<< orphan*/  enable_ldb_on_eval; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_STANDARD ; 
#define  REDIS_REPLY_ARRAY 137 
#define  REDIS_REPLY_BOOL 136 
#define  REDIS_REPLY_DOUBLE 135 
#define  REDIS_REPLY_ERROR 134 
#define  REDIS_REPLY_INTEGER 133 
#define  REDIS_REPLY_MAP 132 
#define  REDIS_REPLY_NIL 131 
#define  REDIS_REPLY_STATUS 130 
#define  REDIS_REPLY_STRING 129 
#define  REDIS_REPLY_VERB 128 
 int /*<<< orphan*/  cliRefreshPrompt () ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int const) ; 
 char* sdsCatColorizedLdbReply (char*,char*,int) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatlen (char*,char*,int) ; 
 char* sdscatprintf (char*,char*,char*) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int sdslen (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static sds cliFormatReplyRaw(redisReply *r) {
    sds out = sdsempty(), tmp;
    size_t i;

    switch (r->type) {
    case REDIS_REPLY_NIL:
        /* Nothing... */
        break;
    case REDIS_REPLY_ERROR:
        out = sdscatlen(out,r->str,r->len);
        out = sdscatlen(out,"\n",1);
        break;
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_STRING:
    case REDIS_REPLY_VERB:
        if (r->type == REDIS_REPLY_STATUS && config.eval_ldb) {
            /* The Lua debugger replies with arrays of simple (status)
             * strings. We colorize the output for more fun if this
             * is a debugging session. */

            /* Detect the end of a debugging session. */
            if (strstr(r->str,"<endsession>") == r->str) {
                config.enable_ldb_on_eval = 0;
                config.eval_ldb = 0;
                config.eval_ldb_end = 1; /* Signal the caller session ended. */
                config.output = OUTPUT_STANDARD;
                cliRefreshPrompt();
            } else {
                out = sdsCatColorizedLdbReply(out,r->str,r->len);
            }
        } else {
            out = sdscatlen(out,r->str,r->len);
        }
        break;
    case REDIS_REPLY_BOOL:
        out = sdscat(out,r->integer ? "(true)" : "(false)");
    break;
    case REDIS_REPLY_INTEGER:
        out = sdscatprintf(out,"%lld",r->integer);
        break;
    case REDIS_REPLY_DOUBLE:
        out = sdscatprintf(out,"%s",r->str);
        break;
    case REDIS_REPLY_ARRAY:
        for (i = 0; i < r->elements; i++) {
            if (i > 0) out = sdscat(out,config.mb_delim);
            tmp = cliFormatReplyRaw(r->element[i]);
            out = sdscatlen(out,tmp,sdslen(tmp));
            sdsfree(tmp);
        }
        break;
    case REDIS_REPLY_MAP:
        for (i = 0; i < r->elements; i += 2) {
            if (i > 0) out = sdscat(out,config.mb_delim);
            tmp = cliFormatReplyRaw(r->element[i]);
            out = sdscatlen(out,tmp,sdslen(tmp));
            sdsfree(tmp);

            out = sdscatlen(out," ",1);
            tmp = cliFormatReplyRaw(r->element[i+1]);
            out = sdscatlen(out,tmp,sdslen(tmp));
            sdsfree(tmp);
        }
        break;
    default:
        fprintf(stderr,"Unknown reply type: %d\n", r->type);
        exit(1);
    }
    return out;
}