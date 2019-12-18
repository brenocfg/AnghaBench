#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  patterns; int /*<<< orphan*/  passwords; int /*<<< orphan*/  allowed_commands; } ;
typedef  TYPE_1__ user ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  listNode ;

/* Variables and functions */
 int /*<<< orphan*/  ACLAddAllowedSubcommand (TYPE_1__*,unsigned long,char*) ; 
 unsigned long ACLGetCommandID (char const*) ; 
 int ACLGetUserCommandBit (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  ACLHashPassword (unsigned char*,int) ; 
 int /*<<< orphan*/ * ACLLookupCommand (char const*) ; 
 int /*<<< orphan*/  ACLResetSubcommands (TYPE_1__*) ; 
 int /*<<< orphan*/  ACLResetSubcommandsForCommand (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  ACLSetUserCommandBit (TYPE_1__*,unsigned long,int) ; 
 int ACLSetUserCommandBitsForCategory (TYPE_1__*,char const*,int) ; 
 int C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int HASH_PASSWORD_LEN ; 
 int USER_FLAG_ALLCOMMANDS ; 
 int USER_FLAG_ALLKEYS ; 
 int USER_FLAG_DISABLED ; 
 int USER_FLAG_ENABLED ; 
 int USER_FLAG_NOPASS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (char const*,int) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zfree (char*) ; 
 char* zstrdup (char const*) ; 

int ACLSetUser(user *u, const char *op, ssize_t oplen) {
    if (oplen == -1) oplen = strlen(op);
    if (!strcasecmp(op,"on")) {
        u->flags |= USER_FLAG_ENABLED;
        u->flags &= ~USER_FLAG_DISABLED;
    } else if (!strcasecmp(op,"off")) {
        u->flags |= USER_FLAG_DISABLED;
        u->flags &= ~USER_FLAG_ENABLED;
    } else if (!strcasecmp(op,"allkeys") ||
               !strcasecmp(op,"~*"))
    {
        u->flags |= USER_FLAG_ALLKEYS;
        listEmpty(u->patterns);
    } else if (!strcasecmp(op,"resetkeys")) {
        u->flags &= ~USER_FLAG_ALLKEYS;
        listEmpty(u->patterns);
    } else if (!strcasecmp(op,"allcommands") ||
               !strcasecmp(op,"+@all"))
    {
        memset(u->allowed_commands,255,sizeof(u->allowed_commands));
        u->flags |= USER_FLAG_ALLCOMMANDS;
        ACLResetSubcommands(u);
    } else if (!strcasecmp(op,"nocommands") ||
               !strcasecmp(op,"-@all"))
    {
        memset(u->allowed_commands,0,sizeof(u->allowed_commands));
        u->flags &= ~USER_FLAG_ALLCOMMANDS;
        ACLResetSubcommands(u);
    } else if (!strcasecmp(op,"nopass")) {
        u->flags |= USER_FLAG_NOPASS;
        listEmpty(u->passwords);
    } else if (!strcasecmp(op,"resetpass")) {
        u->flags &= ~USER_FLAG_NOPASS;
        listEmpty(u->passwords);
    } else if (op[0] == '>' || op[0] == '#') {
        sds newpass;
        if (op[0] == '>') {
            newpass = ACLHashPassword((unsigned char*)op+1,oplen-1);
        } else {
            if (oplen != HASH_PASSWORD_LEN + 1) {
                errno = EBADMSG;
                return C_ERR;
            }

            /* Password hashes can only be characters that represent
             * hexadecimal values, which are numbers and lowercase
             * characters 'a' through 'f'.
             */
            for(int i = 1; i < HASH_PASSWORD_LEN + 1; i++) {
                char c = op[i];
                if ((c < 'a' || c > 'f') && (c < '0' || c > '9')) {
                    errno = EBADMSG;
                    return C_ERR;
                }
            }
            newpass = sdsnewlen(op+1,oplen-1);
        }

        listNode *ln = listSearchKey(u->passwords,newpass);
        /* Avoid re-adding the same password multiple times. */
        if (ln == NULL)
            listAddNodeTail(u->passwords,newpass);
        else
            sdsfree(newpass);
        u->flags &= ~USER_FLAG_NOPASS;
    } else if (op[0] == '<' || op[0] == '!') {
        sds delpass;
        if (op[0] == '<') {
            delpass = ACLHashPassword((unsigned char*)op+1,oplen-1);
        } else {
            if (oplen != HASH_PASSWORD_LEN + 1) {
                errno = EBADMSG;
                return C_ERR;
            }
            delpass = sdsnewlen(op+1,oplen-1);
        }
        listNode *ln = listSearchKey(u->passwords,delpass);
        sdsfree(delpass);
        if (ln) {
            listDelNode(u->passwords,ln);
        } else {
            errno = ENODEV;
            return C_ERR;
        }
    } else if (op[0] == '~') {
        if (u->flags & USER_FLAG_ALLKEYS) {
            errno = EEXIST;
            return C_ERR;
        }
        sds newpat = sdsnewlen(op+1,oplen-1);
        listNode *ln = listSearchKey(u->patterns,newpat);
        /* Avoid re-adding the same pattern multiple times. */
        if (ln == NULL)
            listAddNodeTail(u->patterns,newpat);
        else
            sdsfree(newpat);
        u->flags &= ~USER_FLAG_ALLKEYS;
    } else if (op[0] == '+' && op[1] != '@') {
        if (strchr(op,'|') == NULL) {
            if (ACLLookupCommand(op+1) == NULL) {
                errno = ENOENT;
                return C_ERR;
            }
            unsigned long id = ACLGetCommandID(op+1);
            ACLSetUserCommandBit(u,id,1);
            ACLResetSubcommandsForCommand(u,id);
        } else {
            /* Split the command and subcommand parts. */
            char *copy = zstrdup(op+1);
            char *sub = strchr(copy,'|');
            sub[0] = '\0';
            sub++;

            /* Check if the command exists. We can't check the
             * subcommand to see if it is valid. */
            if (ACLLookupCommand(copy) == NULL) {
                zfree(copy);
                errno = ENOENT;
                return C_ERR;
            }
            unsigned long id = ACLGetCommandID(copy);

            /* The subcommand cannot be empty, so things like DEBUG|
             * are syntax errors of course. */
            if (strlen(sub) == 0) {
                zfree(copy);
                errno = EINVAL;
                return C_ERR;
            }

            /* The command should not be set right now in the command
             * bitmap, because adding a subcommand of a fully added
             * command is probably an error on the user side. */
            if (ACLGetUserCommandBit(u,id) == 1) {
                zfree(copy);
                errno = EBUSY;
                return C_ERR;
            }

            /* Add the subcommand to the list of valid ones. */
            ACLAddAllowedSubcommand(u,id,sub);

            /* We have to clear the command bit so that we force the
             * subcommand check. */
            ACLSetUserCommandBit(u,id,0);
            zfree(copy);
        }
    } else if (op[0] == '-' && op[1] != '@') {
        if (ACLLookupCommand(op+1) == NULL) {
            errno = ENOENT;
            return C_ERR;
        }
        unsigned long id = ACLGetCommandID(op+1);
        ACLSetUserCommandBit(u,id,0);
        ACLResetSubcommandsForCommand(u,id);
    } else if ((op[0] == '+' || op[0] == '-') && op[1] == '@') {
        int bitval = op[0] == '+' ? 1 : 0;
        if (ACLSetUserCommandBitsForCategory(u,op+2,bitval) == C_ERR) {
            errno = ENOENT;
            return C_ERR;
        }
    } else if (!strcasecmp(op,"reset")) {
        serverAssert(ACLSetUser(u,"resetpass",-1) == C_OK);
        serverAssert(ACLSetUser(u,"resetkeys",-1) == C_OK);
        serverAssert(ACLSetUser(u,"off",-1) == C_OK);
        serverAssert(ACLSetUser(u,"-@all",-1) == C_OK);
    } else {
        errno = EINVAL;
        return C_ERR;
    }
    return C_OK;
}