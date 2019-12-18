#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_array_t ;
struct TYPE_3__ {char* payload; char* extra; char const** results; scalar_t__ success; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 size_t MAX_RESULT ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int mrl_EscapeFragmentIdentifier (char**,char*) ; 
 int mrl_FragmentSplit (int /*<<< orphan*/ *,char const**,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,scalar_t__) ; 
 TYPE_1__* testcase ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 char* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

int main (void)
{
    for (size_t i = 0; i < ARRAY_SIZE(testcase); ++i)
    {
        vlc_array_t out;
        const char *extra = NULL;
        int ret = mrl_FragmentSplit(&out, &extra, testcase[i].payload);
        if (testcase[i].success)
        {
            assert(ret == VLC_SUCCESS);
            if (extra != NULL)
                assert(strcmp(extra, testcase[i].extra) == 0);
            else
                assert(testcase[i].extra == NULL);

            const char *p = testcase[i].payload + 2;
            for (size_t j = 0; testcase[i].results[j] != NULL; ++j)
            {
                assert(j < vlc_array_count(&out) && j < MAX_RESULT);
                char *res = vlc_array_item_at_index(&out, j);

                assert(strcmp(testcase[i].results[j], res) == 0);

                char *res_escaped = NULL;
                ret = mrl_EscapeFragmentIdentifier(&res_escaped, res);
                assert(ret == VLC_SUCCESS && res_escaped != NULL);
                assert(strncmp(p, res_escaped, strlen(res_escaped)) == 0);
                p += strlen(res_escaped) + 2;

                free(res_escaped);
                free(res);
            }
            vlc_array_clear(&out);
        }
        else
        {
            assert(ret != VLC_SUCCESS);
        }
    }
    return 0;
}