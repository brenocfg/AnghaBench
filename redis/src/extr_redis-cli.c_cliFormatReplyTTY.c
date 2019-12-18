#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_3__ {int type; char* str; unsigned int elements; struct TYPE_3__** element; int /*<<< orphan*/  integer; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  _prefixfmt ;

/* Variables and functions */
#define  REDIS_REPLY_ARRAY 138 
#define  REDIS_REPLY_BOOL 137 
#define  REDIS_REPLY_DOUBLE 136 
#define  REDIS_REPLY_ERROR 135 
#define  REDIS_REPLY_INTEGER 134 
#define  REDIS_REPLY_MAP 133 
#define  REDIS_REPLY_NIL 132 
#define  REDIS_REPLY_SET 131 
#define  REDIS_REPLY_STATUS 130 
#define  REDIS_REPLY_STRING 129 
#define  REDIS_REPLY_VERB 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  memset (char*,char,unsigned int) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatlen (char*,char*,int /*<<< orphan*/ ) ; 
 char* sdscatprintf (char*,char*,char*,...) ; 
 char* sdscatrepr (char*,char*,int /*<<< orphan*/ ) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdslen (char*) ; 
 char* sdsnew (char*) ; 
 int /*<<< orphan*/  sdsrange (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,char) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
    sds out = sdsempty();
    switch (r->type) {
    case REDIS_REPLY_ERROR:
        out = sdscatprintf(out,"(error) %s\n", r->str);
    break;
    case REDIS_REPLY_STATUS:
        out = sdscat(out,r->str);
        out = sdscat(out,"\n");
    break;
    case REDIS_REPLY_INTEGER:
        out = sdscatprintf(out,"(integer) %lld\n",r->integer);
    break;
    case REDIS_REPLY_DOUBLE:
        out = sdscatprintf(out,"(double) %s\n",r->str);
    break;
    case REDIS_REPLY_STRING:
    case REDIS_REPLY_VERB:
        /* If you are producing output for the standard output we want
        * a more interesting output with quoted characters and so forth,
        * unless it's a verbatim string type. */
        if (r->type == REDIS_REPLY_STRING) {
            out = sdscatrepr(out,r->str,r->len);
            out = sdscat(out,"\n");
        } else {
            out = sdscatlen(out,r->str,r->len);
            out = sdscat(out,"\n");
        }
    break;
    case REDIS_REPLY_NIL:
        out = sdscat(out,"(nil)\n");
    break;
    case REDIS_REPLY_BOOL:
        out = sdscat(out,r->integer ? "(true)\n" : "(false)\n");
    break;
    case REDIS_REPLY_ARRAY:
    case REDIS_REPLY_MAP:
    case REDIS_REPLY_SET:
        if (r->elements == 0) {
            if (r->type == REDIS_REPLY_ARRAY)
                out = sdscat(out,"(empty array)\n");
            else if (r->type == REDIS_REPLY_MAP)
                out = sdscat(out,"(empty hash)\n");
            else if (r->type == REDIS_REPLY_SET)
                out = sdscat(out,"(empty set)\n");
            else
                out = sdscat(out,"(empty aggregate type)\n");
        } else {
            unsigned int i, idxlen = 0;
            char _prefixlen[16];
            char _prefixfmt[16];
            sds _prefix;
            sds tmp;

            /* Calculate chars needed to represent the largest index */
            i = r->elements;
            if (r->type == REDIS_REPLY_MAP) i /= 2;
            do {
                idxlen++;
                i /= 10;
            } while(i);

            /* Prefix for nested multi bulks should grow with idxlen+2 spaces */
            memset(_prefixlen,' ',idxlen+2);
            _prefixlen[idxlen+2] = '\0';
            _prefix = sdscat(sdsnew(prefix),_prefixlen);

            /* Setup prefix format for every entry */
            char numsep;
            if (r->type == REDIS_REPLY_SET) numsep = '~';
            else if (r->type == REDIS_REPLY_MAP) numsep = '#';
            else numsep = ')';
            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%ud%c ",idxlen,numsep);

            for (i = 0; i < r->elements; i++) {
                unsigned int human_idx = (r->type == REDIS_REPLY_MAP) ?
                                         i/2 : i;
                human_idx++; /* Make it 1-based. */

                /* Don't use the prefix for the first element, as the parent
                 * caller already prepended the index number. */
                out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,human_idx);

                /* Format the multi bulk entry */
                tmp = cliFormatReplyTTY(r->element[i],_prefix);
                out = sdscatlen(out,tmp,sdslen(tmp));
                sdsfree(tmp);

                /* For maps, format the value as well. */
                if (r->type == REDIS_REPLY_MAP) {
                    i++;
                    sdsrange(out,0,-2);
                    out = sdscat(out," => ");
                    tmp = cliFormatReplyTTY(r->element[i],_prefix);
                    out = sdscatlen(out,tmp,sdslen(tmp));
                    sdsfree(tmp);
                }
            }
            sdsfree(_prefix);
        }
    break;
    default:
        fprintf(stderr,"Unknown reply type: %d\n", r->type);
        exit(1);
    }
    return out;
}