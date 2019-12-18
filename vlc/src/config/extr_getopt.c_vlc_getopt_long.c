#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* arg; int ind; int first_nonopt; int last_nonopt; char* nextchar; char opt; } ;
typedef  TYPE_1__ vlc_getopt_t ;
struct vlc_option {char* name; char val; char* flag; scalar_t__ has_arg; } ;

/* Variables and functions */
 scalar_t__ NONOPTION_P ; 
 int /*<<< orphan*/  exchange (char**,TYPE_1__*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char* const,char*) ; 
 unsigned int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int vlc_getopt_long(int argc, char *const *argv,
                    const char *optstring,
                    const struct vlc_option *restrict longopts, int *longind,
                    vlc_getopt_t *restrict state)
{
    state->arg = NULL;

    if (state->ind == 0)
    {
        /* Initialize the internal data when the first call is made.  */
        /* Start processing options with ARGV-element 1 (since ARGV-element 0
           is the program name); the sequence of previously skipped
           non-option ARGV-elements is empty.  */
        state->first_nonopt = state->last_nonopt = state->ind = 1;
        state->nextchar = NULL;
    }

#define NONOPTION_P (argv[state->ind][0] != '-' || argv[state->ind][1] == '\0')

    if (state->nextchar == NULL || *state->nextchar == '\0')
    {
        /* Advance to the next ARGV-element.  */

        /* Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
           moved back by the user (who may also have changed the arguments).  */
        if (state->last_nonopt > state->ind)
            state->last_nonopt = state->ind;
        if (state->first_nonopt > state->ind)
            state->first_nonopt = state->ind;

        /* If we have just processed some options following some non-options,
           exchange them so that the options come first.  */

        if (state->first_nonopt != state->last_nonopt
            && state->last_nonopt != state->ind)
            exchange((char **) argv, state);
        else if (state->last_nonopt != state->ind)
            state->first_nonopt = state->ind;

        /* Skip any additional non-options
           and extend the range of non-options previously skipped.  */

        while (state->ind < argc && NONOPTION_P)
            state->ind++;
        state->last_nonopt = state->ind;

        /* The special ARGV-element `--' means premature end of options.
           Skip it like a null option,
           then exchange with previous non-options as if it were an option,
           then skip everything else like a non-option.  */

        if (state->ind != argc && !strcmp(argv[state->ind], "--"))
        {
            state->ind++;

            if (state->first_nonopt != state->last_nonopt
                && state->last_nonopt != state->ind)
                exchange((char **) argv, state);
            else if (state->first_nonopt == state->last_nonopt)
                state->first_nonopt = state->ind;
            state->last_nonopt = argc;

            state->ind = argc;
        }

        /* If we have done all the ARGV-elements, stop the scan
           and back over any non-options that we skipped and permuted.  */

        if (state->ind == argc)
        {
            /* Set the next-arg-index to point at the non-options
               that we previously skipped, so the caller will digest them.  */
            if (state->first_nonopt != state->last_nonopt)
                state->ind = state->first_nonopt;
            return -1;
        }

        /* If we have come to a non-option and did not permute it,
           either stop the scan or describe it to the caller and pass it by.  */

        if (NONOPTION_P)
        {
            state->arg = argv[state->ind++];
            return 1;
        }

        /* We have found another option-ARGV-element.
           Skip the initial punctuation.  */

        state->nextchar = (argv[state->ind] + 1
                        + (argv[state->ind][1] == '-'));
    }

    /* Decode the current option-ARGV-element.  */

    /* Check whether the ARGV-element is a long option.  */

    if (argv[state->ind][1] == '-')
    {
        char *nameend;
        const struct vlc_option *p;
        const struct vlc_option *pfound = NULL;
        int exact = 0;
        int ambig = 0;
        int indfound = -1;
        int option_index;

        for (nameend = state->nextchar; *nameend && *nameend != '='; nameend++)
            /* Do nothing.  */ ;

        /* Test all long options for either exact match
           or abbreviated matches.  */
        for (p = longopts, option_index = 0; p->name; p++, option_index++)
            if (!strncmp(p->name, state->nextchar, nameend - state->nextchar))
            {
                if ((unsigned int) (nameend - state->nextchar)
                    == (unsigned int) strlen(p->name))
                {
                    /* Exact match found.  */
                    pfound = p;
                    indfound = option_index;
                    exact = 1;
                    break;
                }
                else if (pfound == NULL)
                {
                    /* First nonexact match found.  */
                    pfound = p;
                    indfound = option_index;
                }
                else
                    /* Second or later nonexact match found.  */
                    ambig = 1;
            }

        if (ambig && !exact)
        {
            state->nextchar += strlen(state->nextchar);
            state->ind++;
            state->opt = 0;
            return '?';
        }

        if (pfound != NULL)
        {
            option_index = indfound;
            state->ind++;
            if (*nameend)
            {
                if (pfound->has_arg)
                    state->arg = nameend + 1;
                else
                {
                    state->nextchar += strlen(state->nextchar);

                    state->opt = pfound->val;
                    return '?';
                }
            }
            else if (pfound->has_arg)
            {
                if (state->ind < argc)
                    state->arg = argv[state->ind++];
                else
                {
                    state->nextchar += strlen(state->nextchar);
                    state->opt = pfound->val;
                    return optstring[0] == ':' ? ':' : '?';
                }
            }
            state->nextchar += strlen(state->nextchar);
            if (longind != NULL)
                *longind = option_index;
            if (pfound->flag)
            {
                *(pfound->flag) = pfound->val;
                return 0;
            }
            return pfound->val;
        }

        state->nextchar = (char *) "";
        state->ind++;
        state->opt = 0;
        return '?';
    }

    /* Look at and handle the next short option-character.  */

    {
        char c = *(state->nextchar)++;
        char *temp = strchr(optstring, c);

        /* Increment `optind' when we start to process its last character.  */
        if (*state->nextchar == '\0')
            ++state->ind;

        if (temp == NULL || c == ':')
        {
            state->opt = c;
            return '?';
        }
        /* Convenience. Treat POSIX -W foo same as long option --foo */
        if (temp[0] == 'W' && temp[1] == ';')
        {
            char *nameend;
            const struct vlc_option *p;
            const struct vlc_option *pfound = NULL;
            int exact = 0;
            int ambig = 0;
            int indfound = 0;
            int option_index;

            /* This is an option that requires an argument.  */
            if (*state->nextchar != '\0')
            {
                state->arg = state->nextchar;
                /* If we end this ARGV-element by taking the rest as an arg,
                   we must advance to the next element now.  */
                state->ind++;
            }
            else if (state->ind == argc)
            {
                state->opt = c;
                if (optstring[0] == ':')
                    c = ':';
                else
                    c = '?';
                return c;
            }
            else
                /* We already incremented `optind' once;
                   increment it again when taking next ARGV-elt as argument.  */
                state->arg = argv[state->ind++];

            /* optarg is now the argument, see if it's in the
               table of longopts.  */

            for (state->nextchar = nameend = state->arg; *nameend && *nameend != '='; nameend++)
                /* Do nothing.  */ ;

            /* Test all long options for either exact match
               or abbreviated matches.  */
            for (p = longopts, option_index = 0; p->name; p++, option_index++)
                if (!strncmp(p->name, state->nextchar, nameend - state->nextchar))
                {
                    if ((unsigned int) (nameend - state->nextchar)
                        == strlen(p->name))
                    {
                        /* Exact match found.  */
                        pfound = p;
                        indfound = option_index;
                        exact = 1;
                        break;
                    }
                    else if (pfound == NULL)
                    {
                        /* First nonexact match found.  */
                        pfound = p;
                        indfound = option_index;
                    }
                    else
                        /* Second or later nonexact match found.  */
                        ambig = 1;
                }
            if (ambig && !exact)
            {
                state->nextchar += strlen(state->nextchar);
                state->ind++;
                return '?';
            }
            if (pfound != NULL)
            {
                option_index = indfound;
                if (*nameend)
                {
                    if (pfound->has_arg)
                        state->arg = nameend + 1;
                    else
                    {
                        state->nextchar += strlen(state->nextchar);
                        return '?';
                    }
                }
                else if (pfound->has_arg)
                {
                    if (state->ind < argc)
                        state->arg = argv[state->ind++];
                    else
                    {
                        state->nextchar += strlen(state->nextchar);
                        return optstring[0] == ':' ? ':' : '?';
                    }
                }
                state->nextchar += strlen(state->nextchar);
                if (longind != NULL)
                    *longind = option_index;
                if (pfound->flag)
                {
                    *(pfound->flag) = pfound->val;
                    return 0;
                }
                return pfound->val;
            }
            state->nextchar = NULL;
            return 'W';    /* Let the application handle it.   */
        }
        if (temp[1] == ':')
        {
            /* This is an option that requires an argument.  */
            if (*state->nextchar != '\0')
            {
                state->arg = state->nextchar;
                /* If we end this ARGV-element by taking the rest as an arg,
                   we must advance to the next element now.  */
                state->ind++;
            }
            else if (state->ind == argc)
            {
                state->opt = c;
                if (optstring[0] == ':')
                    c = ':';
                else
                    c = '?';
            }
            else
                /* We already incremented `optind' once;
                   increment it again when taking next ARGV-elt as argument.  */
                state->arg = argv[state->ind++];
            state->nextchar = NULL;
        }
        return c;
    }
}