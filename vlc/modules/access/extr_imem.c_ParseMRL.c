#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int VLC_VAR_DOINHERIT ; 
#define  VLC_VAR_INTEGER 129 
#define  VLC_VAR_STRING 128 
 scalar_t__ asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void ParseMRL(vlc_object_t *object, const char *psz_path)
{
    static const struct {
        const char *name;
        int        type;
    } options[] = {
        { "id",         VLC_VAR_INTEGER },
        { "group",      VLC_VAR_INTEGER },
        { "cat",        VLC_VAR_INTEGER },
        { "samplerate", VLC_VAR_INTEGER },
        { "channels",   VLC_VAR_INTEGER },
        { "width",      VLC_VAR_INTEGER },
        { "height",     VLC_VAR_INTEGER },
        { "cookie",     VLC_VAR_STRING },
        { "codec",      VLC_VAR_STRING },
        { "language",   VLC_VAR_STRING },
        { "dar",        VLC_VAR_STRING },
        { "fps",        VLC_VAR_STRING },
        { NULL, -1 }
    };

    char *dup = strdup(psz_path);
    if (!dup)
        return;
    char *current = dup;

    while (current) {
        char *next = strchr(current, ':');
        if (next)
            *next++ = '\0';

        char *option = current;
        char *value = strchr(current, '=');
        if (value) {
            *value++ = '\0';
            msg_Dbg(object, "option '%s' value '%s'", option, value);
        } else {
            msg_Dbg(object, "option '%s' without value (unsupported)", option);
        }

        char *name;
        if (asprintf(&name, "imem-%s", option) < 0)
            name = NULL;
        for (unsigned i = 0; name && options[i].name; i++) {
            if (strcmp(options[i].name, option))
                continue;
            /* */
            var_Create(object, name, options[i].type | VLC_VAR_DOINHERIT);
            if (options[i].type == VLC_VAR_INTEGER && value) {
                var_SetInteger(object, name, strtol(value, NULL, 0));
            } else if (options[i].type == VLC_VAR_STRING && value) {
                var_SetString(object, name, value);
            }
            break;
        }
        free(name);

        /* */
        current = next;
    }
    free(dup);
}