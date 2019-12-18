#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int type; } ;
struct conf {int /*<<< orphan*/  fname; TYPE_1__ event; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CONF_MAX_DEPTH ; 
 int CONF_ROOT_DEPTH ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  NOT_REACHED () ; 
#define  YAML_DOCUMENT_END_EVENT 136 
#define  YAML_DOCUMENT_START_EVENT 135 
#define  YAML_MAPPING_END_EVENT 134 
#define  YAML_MAPPING_START_EVENT 133 
#define  YAML_SCALAR_EVENT 132 
#define  YAML_SEQUENCE_END_EVENT 131 
#define  YAML_SEQUENCE_START_EVENT 130 
#define  YAML_STREAM_END_EVENT 129 
#define  YAML_STREAM_START_EVENT 128 
 int /*<<< orphan*/  conf_event_done (struct conf*) ; 
 scalar_t__ conf_event_next (struct conf*) ; 
 int /*<<< orphan*/  conf_yaml_deinit (struct conf*) ; 
 scalar_t__ conf_yaml_init (struct conf*) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static rstatus_t
conf_validate_structure(struct conf *cf)
{
    rstatus_t status;
    int type, depth;
    uint32_t i, count[CONF_MAX_DEPTH + 1];
    bool done, error, seq;

    status = conf_yaml_init(cf);
    if (status != NC_OK) {
        return status;
    }

    done = false;
    error = false;
    seq = false;
    depth = 0;
    for (i = 0; i < CONF_MAX_DEPTH + 1; i++) {
        count[i] = 0;
    }

    /*
     * Validate that the configuration conforms roughly to the following
     * yaml tree structure:
     *
     * keyx:
     *   key1: value1
     *   key2: value2
     *   seq:
     *     - elem1
     *     - elem2
     *     - elem3
     *   key3: value3
     *
     * keyy:
     *   key1: value1
     *   key2: value2
     *   seq:
     *     - elem1
     *     - elem2
     *     - elem3
     *   key3: value3
     */
    do {
        status = conf_event_next(cf);
        if (status != NC_OK) {
            return status;
        }

        type = cf->event.type;

        log_debug(LOG_VVERB, "next event %d depth %d seq %d", type, depth, seq);

        switch (type) {
        case YAML_STREAM_START_EVENT:
        case YAML_DOCUMENT_START_EVENT:
            break;

        case YAML_DOCUMENT_END_EVENT:
            break;

        case YAML_STREAM_END_EVENT:
            done = true;
            break;

        case YAML_MAPPING_START_EVENT:
            if (depth == CONF_ROOT_DEPTH && count[depth] != 1) {
                error = true;
                log_error("conf: '%s' has more than one \"key:value\" at depth"
                          " %d", cf->fname, depth);
            } else if (depth >= CONF_MAX_DEPTH) {
                error = true;
                log_error("conf: '%s' has a depth greater than %d", cf->fname,
                          CONF_MAX_DEPTH);
            }
            depth++;
            break;

        case YAML_MAPPING_END_EVENT:
            if (depth == CONF_MAX_DEPTH) {
                if (seq) {
                    seq = false;
                } else {
                    error = true;
                    log_error("conf: '%s' missing sequence directive at depth "
                              "%d", cf->fname, depth);
                }
            }
            depth--;
            count[depth] = 0;
            break;

        case YAML_SEQUENCE_START_EVENT:
            if (seq) {
                error = true;
                log_error("conf: '%s' has more than one sequence directive",
                          cf->fname);
            } else if (depth != CONF_MAX_DEPTH) {
                error = true;
                log_error("conf: '%s' has sequence at depth %d instead of %d",
                          cf->fname, depth, CONF_MAX_DEPTH);
            } else if (count[depth] != 1) {
                error = true;
                log_error("conf: '%s' has invalid \"key:value\" at depth %d",
                          cf->fname, depth);
            }
            seq = true;
            break;

        case YAML_SEQUENCE_END_EVENT:
            ASSERT(depth == CONF_MAX_DEPTH);
            count[depth] = 0;
            break;

        case YAML_SCALAR_EVENT:
            if (depth == 0) {
                error = true;
                log_error("conf: '%s' has invalid empty \"key:\" at depth %d",
                          cf->fname, depth);
            } else if (depth == CONF_ROOT_DEPTH && count[depth] != 0) {
                error = true;
                log_error("conf: '%s' has invalid mapping \"key:\" at depth %d",
                          cf->fname, depth);
            } else if (depth == CONF_MAX_DEPTH && count[depth] == 2) {
                /* found a "key: value", resetting! */
                count[depth] = 0;
            }
            count[depth]++;
            break;

        default:
            NOT_REACHED();
        }

        conf_event_done(cf);
    } while (!done && !error);

    conf_yaml_deinit(cf);

    return !error ? NC_OK : NC_ERROR;
}