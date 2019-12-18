#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {char* data; int len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_17__ {char* logname; int backup_num; int log_max_size; int interval; char* suitpath; int adjust_time; int adjust_time_raw; int /*<<< orphan*/ ** backup; int /*<<< orphan*/  time_now; } ;
typedef  TYPE_3__ ngx_pipe_rollback_conf_t ;
struct TYPE_18__ {TYPE_1__* argv; } ;
typedef  TYPE_4__ ngx_open_pipe_t ;
typedef  size_t ngx_int_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_cycle_t ;
struct TYPE_15__ {int nelts; char** elts; } ;

/* Variables and functions */
 size_t MAX_BACKUP_NUM ; 
 size_t NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 void* ngx_atoi (char*,int) ; 
 scalar_t__ ngx_conf_full_name (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_crc32_short (char*,int) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ngx_parse_offset (TYPE_2__*) ; 
 void* ngx_parse_time (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_pipe_create_suitpath (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_pipe_get_now_sec () ; 
 int /*<<< orphan*/  ngx_snprintf (char*,size_t,char*,char*,size_t) ; 
 int ngx_strlen (char*) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_pipe_rollback_parse_args(ngx_cycle_t *cycle, ngx_open_pipe_t *op,
    ngx_pipe_rollback_conf_t *rbcf)
{
    u_char         **argv;
    ngx_uint_t       i;
    ngx_int_t        j;
    size_t           len;
    ngx_str_t        filename;
    ngx_str_t        value;
    uint32_t         hash;

    if (op->argv->nelts < 3) {
        //no logname
        return NGX_ERROR;
    }

    //parse args
    argv = op->argv->elts;

    //set default param
    filename.data = (u_char *) argv[1];
    filename.len = ngx_strlen(filename.data);
    if (ngx_conf_full_name(cycle, &filename, 0) != NGX_OK) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                      "get fullname failed");
        return NGX_ERROR;
    }
    rbcf->logname = (char *) filename.data;
    rbcf->backup_num = 1;
    rbcf->log_max_size = -1;
    rbcf->interval = -1;
    rbcf->suitpath = NULL;
    rbcf->adjust_time = 60;
    rbcf->adjust_time_raw = 60;
    memset(rbcf->backup, 0, sizeof(rbcf->backup));

    for (i = 2; i < op->argv->nelts; i++) {
        if (argv[i] == NULL) {
            break;
        }
        if (ngx_strncmp((u_char *) "interval=", argv[i], 9) == 0) {
            value.data = argv[i] + 9;
            value.len = ngx_strlen((char *) argv[i]) - 9;
#ifdef T_PIPE_OLD_CONF
            //just compatibility
            rbcf->interval = ngx_atoi(value.data, value.len);
            if (rbcf->interval > 0) {
                rbcf->interval = rbcf->interval * 60;   //convert minute to second
                continue;
            }
#endif
            rbcf->interval = ngx_parse_time(&value, 1);
            if (rbcf->interval <= 0) {
                rbcf->interval = -1;
            }

        } else if (ngx_strncmp((u_char *) "baknum=", argv[i], 7) == 0) {
            rbcf->backup_num = ngx_atoi(argv[i] + 7,
                                        ngx_strlen((char *) argv[i]) - 7);
            if (rbcf->backup_num <= 0) {
                rbcf->backup_num = 1;

            } else if (MAX_BACKUP_NUM < (size_t)rbcf->backup_num) {
                rbcf->backup_num = MAX_BACKUP_NUM;
            }

        } else if (ngx_strncmp((u_char *) "maxsize=", argv[i], 8) == 0) {
            value.data = argv[i] + 8;
            value.len = ngx_strlen((char *) argv[i]) - 8;
#ifdef T_PIPE_OLD_CONF
            //just compatibility
            rbcf->log_max_size = ngx_atoi(value.data, value.len);
            if (rbcf->log_max_size > 0) {
                rbcf->log_max_size = rbcf->log_max_size * 1024 * 1024; //M
                continue;
            }
#endif
            rbcf->log_max_size = ngx_parse_offset(&value);
            if (rbcf->log_max_size <= 0) {
                rbcf->log_max_size = -1;
            } 
        } else if (ngx_strncmp((u_char *) "suitpath=", argv[i], 9) == 0) {
            filename.data = (u_char*)(argv[i] + 9);
            filename.len = ngx_strlen(filename.data);
            if (ngx_conf_full_name(cycle, &filename, 0) != NGX_OK) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                              "get fullname failed");
                return NGX_ERROR;
            }
            rbcf->suitpath = (char*)filename.data;

            rbcf->time_now = ngx_pipe_get_now_sec();
            ngx_pipe_create_suitpath(cycle, rbcf);
        } else if (ngx_strncmp((u_char *) "adjust=", argv[i], 7) == 0) {
            value.data =argv[i] + 7;
            value.len = ngx_strlen((char *) argv[i]) - 7;
            rbcf->adjust_time_raw = ngx_parse_time(&value, 1);
            if (rbcf->adjust_time_raw < 1) {
                rbcf->adjust_time_raw = 1;
            }
        }
    } 

    len = ngx_strlen(rbcf->logname) + 5; //max is ".128"
    for (j = 0; j < rbcf->backup_num; j++) {
        rbcf->backup[j] = ngx_pcalloc(cycle->pool, len);
        if (rbcf->backup[j] == NULL) {
            return NGX_ERROR;
        }
        ngx_snprintf((u_char *) rbcf->backup[j], len, "%s.%i%Z", rbcf->logname, j + 1);
    }

    //use same seed for same log file, when reload may have same adjust time
    hash = ngx_crc32_short((u_char*)rbcf->logname, ngx_strlen(rbcf->logname));
    srand(hash);
    rbcf->adjust_time = rand() % rbcf->adjust_time_raw;

    ngx_log_error(NGX_LOG_INFO, cycle->log, 0,
                  "log rollback param: num [%i], interval %i(S), size %i(B), adjust %i/%i(S)", 
                  rbcf->backup_num, rbcf->interval, rbcf->log_max_size, rbcf->adjust_time, rbcf->adjust_time_raw);

    return NGX_OK;
}