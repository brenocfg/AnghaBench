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
typedef  int /*<<< orphan*/  user ;
typedef  char* sds ;
typedef  int /*<<< orphan*/  rax ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  acl_filename; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCopyUser (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ACLCreateUnlinkedUser () ; 
 int /*<<< orphan*/ * ACLCreateUser (char*,scalar_t__) ; 
 int /*<<< orphan*/  ACLFreeUser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACLFreeUsersSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ACLGetUserByName (char*,int) ; 
 int /*<<< orphan*/  ACLInitDefaultUser () ; 
 scalar_t__ ACLSetUser (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 char* ACLSetUserStringError () ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/ * DefaultUser ; 
 int /*<<< orphan*/ * Users ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * raxNew () ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatprintf (char*,char*,char const*,int,...) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdsfreesplitres (char**,int) ; 
 scalar_t__ sdslen (char*) ; 
 char** sdssplitargs (char*,int*) ; 
 char** sdssplitlen (char*,int /*<<< orphan*/ ,char*,int,int*) ; 
 char* sdstrim (char*,char*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

sds ACLLoadFromFile(const char *filename) {
    FILE *fp;
    char buf[1024];

    /* Open the ACL file. */
    if ((fp = fopen(filename,"r")) == NULL) {
        sds errors = sdscatprintf(sdsempty(),
            "Error loading ACLs, opening file '%s': %s",
            filename, strerror(errno));
        return errors;
    }

    /* Load the whole file as a single string in memory. */
    sds acls = sdsempty();
    while(fgets(buf,sizeof(buf),fp) != NULL)
        acls = sdscat(acls,buf);
    fclose(fp);

    /* Split the file into lines and attempt to load each line. */
    int totlines;
    sds *lines, errors = sdsempty();
    lines = sdssplitlen(acls,strlen(acls),"\n",1,&totlines);
    sdsfree(acls);

    /* We need a fake user to validate the rules before making changes
     * to the real user mentioned in the ACL line. */
    user *fakeuser = ACLCreateUnlinkedUser();

    /* We do all the loading in a fresh instance of the Users radix tree,
     * so if there are errors loading the ACL file we can rollback to the
     * old version. */
    rax *old_users = Users;
    user *old_default_user = DefaultUser;
    Users = raxNew();
    ACLInitDefaultUser();

    /* Load each line of the file. */
    for (int i = 0; i < totlines; i++) {
        sds *argv;
        int argc;
        int linenum = i+1;

        lines[i] = sdstrim(lines[i]," \t\r\n");

        /* Skip blank lines */
        if (lines[i][0] == '\0') continue;

        /* Split into arguments */
        argv = sdssplitargs(lines[i],&argc);
        if (argv == NULL) {
            errors = sdscatprintf(errors,
                     "%s:%d: unbalanced quotes in acl line. ",
                     server.acl_filename, linenum);
            continue;
        }

        /* Skip this line if the resulting command vector is empty. */
        if (argc == 0) {
            sdsfreesplitres(argv,argc);
            continue;
        }

        /* The line should start with the "user" keyword. */
        if (strcmp(argv[0],"user") || argc < 2) {
            errors = sdscatprintf(errors,
                     "%s:%d should start with user keyword followed "
                     "by the username. ", server.acl_filename,
                     linenum);
            sdsfreesplitres(argv,argc);
            continue;
        }

        /* Try to process the line using the fake user to validate iif
         * the rules are able to apply cleanly. */
        ACLSetUser(fakeuser,"reset",-1);
        int j;
        for (j = 2; j < argc; j++) {
            if (ACLSetUser(fakeuser,argv[j],sdslen(argv[j])) != C_OK) {
                char *errmsg = ACLSetUserStringError();
                errors = sdscatprintf(errors,
                         "%s:%d: %s. ",
                         server.acl_filename, linenum, errmsg);
                continue;
            }
        }

        /* Apply the rule to the new users set only if so far there
         * are no errors, otherwise it's useless since we are going
         * to discard the new users set anyway. */
        if (sdslen(errors) != 0) {
            sdsfreesplitres(argv,argc);
            continue;
        }

        /* We can finally lookup the user and apply the rule. If the
         * user already exists we always reset it to start. */
        user *u = ACLCreateUser(argv[1],sdslen(argv[1]));
        if (!u) {
            u = ACLGetUserByName(argv[1],sdslen(argv[1]));
            serverAssert(u != NULL);
            ACLSetUser(u,"reset",-1);
        }

        /* Note that the same rules already applied to the fake user, so
         * we just assert that everything goes well: it should. */
        for (j = 2; j < argc; j++)
            serverAssert(ACLSetUser(u,argv[j],sdslen(argv[j])) == C_OK);

        sdsfreesplitres(argv,argc);
    }

    ACLFreeUser(fakeuser);
    sdsfreesplitres(lines,totlines);
    DefaultUser = old_default_user; /* This pointer must never change. */

    /* Check if we found errors and react accordingly. */
    if (sdslen(errors) == 0) {
        /* The default user pointer is referenced in different places: instead
         * of replacing such occurrences it is much simpler to copy the new
         * default user configuration in the old one. */
        user *new = ACLGetUserByName("default",7);
        serverAssert(new != NULL);
        ACLCopyUser(DefaultUser,new);
        ACLFreeUser(new);
        raxInsert(Users,(unsigned char*)"default",7,DefaultUser,NULL);
        raxRemove(old_users,(unsigned char*)"default",7,NULL);
        ACLFreeUsersSet(old_users);
        sdsfree(errors);
        return NULL;
    } else {
        ACLFreeUsersSet(Users);
        Users = old_users;
        errors = sdscat(errors,"WARNING: ACL errors detected, no change to the previously active ACL rules was performed");
        return errors;
    }
}