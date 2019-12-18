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
struct passwd {char const* pw_dir; } ;
typedef  int /*<<< orphan*/  new_path ;

/* Variables and functions */
 int SEAF_PATH_MAX ; 
 char* g_get_home_dir () ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  geteuid () ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 

char*
ccnet_expand_path (const char *src)
{
#ifdef WIN32
    char new_path[SEAF_PATH_MAX + 1];
    char *p = new_path;
    const char *q = src;

    memset(new_path, 0, sizeof(new_path));
    if (*src == '~') {
        const char *home = g_get_home_dir();
        memcpy(new_path, home, strlen(home));
        p += strlen(new_path);
        q++;
    }
    memcpy(p, q, strlen(q));

    /* delete the charactor '\' or '/' at the end of the path
     * because the function stat faied to deal with directory names
     * with '\' or '/' in the end */
    p = new_path + strlen(new_path) - 1;
    while(*p == '\\' || *p == '/') *p-- = '\0';

    return strdup (new_path);
#else
    const char *next_in, *ntoken;
    char new_path[SEAF_PATH_MAX + 1];
    char *next_out;
    int len;

   /* special cases */
    if (!src || *src == '\0')
        return NULL;
    if (strlen(src) > SEAF_PATH_MAX)
        return NULL;

    next_in = src;
    next_out = new_path;
    *next_out = '\0';

    if (*src == '~') {
        /* handle src start with '~' or '~<user>' like '~plt' */
        struct passwd *pw = NULL;

        for ( ; *next_in != '/' && *next_in != '\0'; next_in++) ;
        
        len = next_in - src;
        if (len == 1) {
            pw = getpwuid (geteuid());
        } else {
            /* copy '~<user>' to new_path */
            memcpy (new_path, src, len);
            new_path[len] = '\0';
            pw = getpwnam (new_path + 1);
        }
        if (pw == NULL)
            return NULL;
       
        len = strlen (pw->pw_dir);
        memcpy (new_path, pw->pw_dir, len);
        next_out = new_path + len;
        *next_out = '\0';

        if (*next_in == '\0')
            return strdup (new_path);
    } else if (*src != '/') {
        getcwd (new_path, SEAF_PATH_MAX);
        for ( ; *next_out; next_out++) ; /* to '\0' */
    }
    
    while (*next_in != '\0') {
        /* move ntoken to the next not '/' char  */
        for (ntoken = next_in; *ntoken == '/'; ntoken++) ;

        for (next_in = ntoken; *next_in != '/' 
                 && *next_in != '\0'; next_in++) ;
 
        len = next_in - ntoken;

        if (len == 0) {
            /* the path ends with '/', keep it */
            *next_out++ = '/';
            *next_out = '\0';
            break;
        }

        if (len == 2 && ntoken[0] == '.' && ntoken[1] == '.') 
        {
            /* '..' */
            for (; next_out > new_path && *next_out != '/'; next_out--)
                ;
            *next_out = '\0';
        } else if (ntoken[0] != '.' || len != 1) {
            /* not '.' */
            *next_out++ = '/';
            memcpy (next_out, ntoken, len);
            next_out += len;
            *next_out = '\0';
        }
    }

    /* the final special case */
    if (new_path[0] == '\0') {
        new_path[0] = '/';
        new_path[1] = '\0';
    }
    return strdup (new_path);
#endif
}