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
struct parsed_param {char* val; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int latency; char* passphrase; int key_length; int payload_size; int bandwidth_overhead_limit; } ;
typedef  TYPE_1__ srt_params_t ;
typedef  int /*<<< orphan*/  local_params ;

/* Variables and functions */
 int /*<<< orphan*/  SRT_PARAM_BANDWIDTH_OVERHEAD_LIMIT ; 
 int /*<<< orphan*/  SRT_PARAM_KEY_LENGTH ; 
 int /*<<< orphan*/  SRT_PARAM_LATENCY ; 
 int /*<<< orphan*/  SRT_PARAM_PASSPHRASE ; 
 int /*<<< orphan*/  SRT_PARAM_PAYLOAD_SIZE ; 
 int atoi (char*) ; 
 char* find (char*,char) ; 
 int* srt_key_lengths ; 
 int srt_url_parse_query (char*,char*,struct parsed_param*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool srt_parse_url(char* url, srt_params_t* params)
{
    char* query = NULL;
    struct parsed_param local_params[32];
    int num_params = 0;
    int i = 0;
    bool rc = false;

    if (!url || !url[0] || !params)
        return false;

    /* initialize params */
    params->latency = -1;
    params->passphrase = NULL;
    params->key_length = -1;
    params->payload_size = -1;
    params->bandwidth_overhead_limit = -1;

    /* Parse URL parameters */
    query = find( url, '?' );
    if (query) {
        num_params = srt_url_parse_query( query, "&", local_params,
                sizeof(local_params) / sizeof(struct parsed_param) );
        if (num_params > 0) {
            rc = true;
            for (i = 0; i < num_params; ++i) {
                char* val = local_params[i].val;
                if (!val)
                    continue;

                if (strcmp( local_params[i].key, SRT_PARAM_LATENCY ) == 0) {
                    int temp = atoi( val );
                    if (temp >= 0)
                        params->latency = temp;
                } else if (strcmp( local_params[i].key, SRT_PARAM_PASSPHRASE )
                        == 0) {
                    params->passphrase = val;
                } else if (strcmp( local_params[i].key, SRT_PARAM_PAYLOAD_SIZE )
                        == 0) {
                    int temp = atoi( val );
                    if (temp >= 0)
                        params->payload_size = temp;
                } else if (strcmp( local_params[i].key, SRT_PARAM_KEY_LENGTH )
                        == 0) {
                    int temp = atoi( val );
                    if (temp == srt_key_lengths[0] || temp == srt_key_lengths[1]
                            || temp == srt_key_lengths[2]) {
                        params->key_length = temp;
                    }
                } else if (strcmp( local_params[i].key,
                SRT_PARAM_BANDWIDTH_OVERHEAD_LIMIT ) == 0) {
                    int temp = atoi( val );
                    if (temp >= 0)
                        params->bandwidth_overhead_limit = temp;

                }
            }
        }
    }

    return rc;
}