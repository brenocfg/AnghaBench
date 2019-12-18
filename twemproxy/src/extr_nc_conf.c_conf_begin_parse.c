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
struct TYPE_2__ {int type; } ;
struct conf {scalar_t__ depth; TYPE_1__ event; int /*<<< orphan*/  parsed; scalar_t__ sound; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ CONF_MAX_DEPTH ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  NOT_REACHED () ; 
#define  YAML_DOCUMENT_START_EVENT 130 
#define  YAML_MAPPING_START_EVENT 129 
#define  YAML_STREAM_START_EVENT 128 
 int /*<<< orphan*/  conf_event_done (struct conf*) ; 
 scalar_t__ conf_event_next (struct conf*) ; 
 scalar_t__ conf_yaml_init (struct conf*) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static rstatus_t
conf_begin_parse(struct conf *cf)
{
    rstatus_t status;
    bool done;

    ASSERT(cf->sound && !cf->parsed);
    ASSERT(cf->depth == 0);

    status = conf_yaml_init(cf);
    if (status != NC_OK) {
        return status;
    }

    done = false;
    do {
        status = conf_event_next(cf);
        if (status != NC_OK) {
            return status;
        }

        log_debug(LOG_VVERB, "next begin event %d", cf->event.type);

        switch (cf->event.type) {
        case YAML_STREAM_START_EVENT:
        case YAML_DOCUMENT_START_EVENT:
            break;

        case YAML_MAPPING_START_EVENT:
            ASSERT(cf->depth < CONF_MAX_DEPTH);
            cf->depth++;
            done = true;
            break;

        default:
            NOT_REACHED();
        }

        conf_event_done(cf);

    } while (!done);

    return NC_OK;
}