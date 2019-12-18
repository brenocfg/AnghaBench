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

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  snd_device_name_free_hint (void**) ; 
 char* snd_device_name_get_hint (void*,char*) ; 
 scalar_t__ snd_device_name_hint (int,char*,void***) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char** xrealloc (char**,unsigned int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int EnumDevices(char const *varname,
                       char ***restrict idp, char ***restrict namep)
{
    void **hints;

    if (snd_device_name_hint(-1, "pcm", &hints) < 0)
        return -1;

    char **ids = NULL, **names = NULL;
    unsigned n = 0;
    bool hinted_default = false;

    for (size_t i = 0; hints[i] != NULL; i++)
    {
        void *hint = hints[i];

        char *name = snd_device_name_get_hint(hint, "NAME");
        if (unlikely(name == NULL))
            continue;

        char *desc = snd_device_name_get_hint(hint, "DESC");
        if (desc == NULL)
            desc = xstrdup (name);
        for (char *lf = strchr(desc, '\n'); lf; lf = strchr(lf, '\n'))
            *lf = ' ';

        ids = xrealloc (ids, (n + 1) * sizeof (*ids));
        names = xrealloc (names, (n + 1) * sizeof (*names));
        ids[n] = name;
        names[n] = desc;
        n++;

        if (!strcmp(name, "default"))
            hinted_default = true;
    }

    snd_device_name_free_hint(hints);

    if (!hinted_default)
    {
        ids = xrealloc (ids, (n + 1) * sizeof (*ids));
        names = xrealloc (names, (n + 1) * sizeof (*names));
        ids[n] = xstrdup ("default");
        names[n] = xstrdup (_("Default"));
        n++;
    }

    *idp = ids;
    *namep = names;
    (void) varname;
    return n;
}