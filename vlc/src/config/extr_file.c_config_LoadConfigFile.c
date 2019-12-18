#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int ssize_t ;
struct TYPE_8__ {float f; char* psz; int /*<<< orphan*/  i; } ;
struct TYPE_7__ {int /*<<< orphan*/  i; } ;
struct TYPE_6__ {int /*<<< orphan*/  i; } ;
struct TYPE_9__ {TYPE_3__ value; TYPE_2__ min; TYPE_1__ max; int /*<<< orphan*/  i_type; scalar_t__ b_removed; scalar_t__ b_unsaveable; } ;
typedef  TYPE_4__ module_config_t ;
typedef  scalar_t__ locale_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CONFIG_CLASS (int /*<<< orphan*/ ) ; 
#define  CONFIG_ITEM_BOOL 130 
#define  CONFIG_ITEM_FLOAT 129 
#define  CONFIG_ITEM_INTEGER 128 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  LC_NUMERIC_MASK ; 
 int VLC_EGENERIC ; 
 scalar_t__ atof (char const*) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 TYPE_4__* config_FindConfig (char const*) ; 
 int /*<<< orphan*/ * config_OpenConfigFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freelocale (scalar_t__) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memchr (char*,char,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ newlocale (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strdupnull (char const*) ; 
 scalar_t__ uselocale (scalar_t__) ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strtoi (char const*) ; 

int config_LoadConfigFile( vlc_object_t *p_this )
{
    FILE *file;

    file = config_OpenConfigFile (p_this);
    if (file == NULL)
        return VLC_EGENERIC;

    /* Skip UTF-8 Byte Order Mark if present */
    char bom[3];
    if (fread (bom, 1, 3, file) != 3 || memcmp (bom, "\xEF\xBB\xBF", 3))
        rewind (file); /* no BOM, rewind */

    char *line = NULL;
    size_t bufsize;
    ssize_t linelen;

    /* Ensure consistent number formatting... */
    locale_t loc = newlocale (LC_NUMERIC_MASK, "C", NULL);
    locale_t baseloc = uselocale (loc);

    vlc_rwlock_wrlock (&config_lock);
    while ((linelen = getline (&line, &bufsize, file)) != -1)
    {
        line[linelen - 1] = '\0'; /* trim newline */

        /* Ignore comments, section and empty lines */
        if (memchr ("#[", line[0], 3) != NULL)
            continue;

        /* look for option name */
        const char *psz_option_name = line;

        char *ptr = strchr (line, '=');
        if (ptr == NULL)
            continue; /* syntax error */
        *ptr = '\0';

        module_config_t *item = config_FindConfig(psz_option_name);
        if (item == NULL)
            continue;

        /* Reject values of options that are unsaveable */
        if (item->b_unsaveable)
            continue;
        /* Ignore options that are obsolete */
        if (item->b_removed)
            continue;

        const char *psz_option_value = ptr + 1;
        switch (CONFIG_CLASS(item->i_type))
        {
            case CONFIG_ITEM_BOOL:
            case CONFIG_ITEM_INTEGER:
            {
                int64_t l;

                errno = 0;
                l = vlc_strtoi (psz_option_value);
                if ((l > item->max.i) || (l < item->min.i))
                    errno = ERANGE;
                if (errno)
                    msg_Warn (p_this, "Integer value (%s) for %s: %s",
                              psz_option_value, psz_option_name,
                              vlc_strerror_c(errno));
                else
                    item->value.i = l;
                break;
            }

            case CONFIG_ITEM_FLOAT:
                if (!*psz_option_value)
                    break;                    /* ignore empty option */
                item->value.f = (float)atof (psz_option_value);
                break;

            default:
                free (item->value.psz);
                item->value.psz = strdupnull (psz_option_value);
                break;
        }
    }
    vlc_rwlock_unlock (&config_lock);
    free (line);

    if (ferror (file))
    {
        msg_Err (p_this, "error reading configuration: %s",
                 vlc_strerror_c(errno));
        clearerr (file);
    }
    fclose (file);

    if (loc != (locale_t)0)
    {
        uselocale (baseloc);
        freelocale (loc);
    }
    return 0;
}