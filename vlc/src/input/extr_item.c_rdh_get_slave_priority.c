#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {char const* psz_name; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_6__ {scalar_t__ i_type; } ;
typedef  TYPE_2__ input_item_slave_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLAVE_PRIORITY_MATCH_ALL ; 
 int /*<<< orphan*/  SLAVE_PRIORITY_MATCH_LEFT ; 
 int /*<<< orphan*/  SLAVE_PRIORITY_MATCH_NONE ; 
 int /*<<< orphan*/  SLAVE_PRIORITY_MATCH_RIGHT ; 
 scalar_t__ SLAVE_TYPE_SPU ; 
 int /*<<< orphan*/  free (char*) ; 
 char* rdh_name_from_filename (char const*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static uint8_t rdh_get_slave_priority(input_item_t *p_item,
                                      input_item_slave_t *p_slave,
                                      const char *psz_slave_filename)
{
    uint8_t i_priority = SLAVE_PRIORITY_MATCH_NONE;
    char *psz_item_name = rdh_name_from_filename(p_item->psz_name);
    char *psz_slave_name = rdh_name_from_filename(psz_slave_filename);

    if (!psz_item_name || !psz_slave_name)
        goto done;

    size_t i_item_len = strlen(psz_item_name);
    size_t i_slave_len = strlen(psz_slave_name);

    /* The slave name len should not be twice longer than the item name len. */
    if (i_item_len > i_slave_len || i_slave_len > 2 * i_item_len)
        goto done;

    /* check if the names match exactly */
    if (!strcmp(psz_item_name, psz_slave_name))
    {
        i_priority = SLAVE_PRIORITY_MATCH_ALL;
        goto done;
    }

    /* "cdg" slaves have to be a full match */
    if (p_slave->i_type == SLAVE_TYPE_SPU)
    {
        char *psz_ext = strrchr(psz_slave_name, '.');
        if (psz_ext != NULL && strcasecmp(++psz_ext, "cdg") == 0)
            goto done;
    }

    /* check if the item name is a substring of the slave name */
    const char *psz_sub = strstr(psz_slave_name, psz_item_name);

    if (psz_sub)
    {
        /* check if the item name was found at the end of the slave name */
        if (strlen(psz_sub + strlen(psz_item_name)) == 0)
        {
            i_priority = SLAVE_PRIORITY_MATCH_RIGHT;
            goto done;
        }
        else
        {
            i_priority = SLAVE_PRIORITY_MATCH_LEFT;
            goto done;
        }
    }

done:
    free(psz_item_name);
    free(psz_slave_name);
    return i_priority;
}