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
struct symt {int dummy; } ;
struct ParseTypedefData {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTS_ABORTIF (struct ParseTypedefData*,int) ; 
 int stabs_pts_read_number (struct ParseTypedefData*,long*) ; 
 int stabs_pts_read_type_def (struct ParseTypedefData*,int /*<<< orphan*/ *,struct symt**) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static inline int stabs_pts_read_method_info(struct ParseTypedefData* ptd)
{
    struct symt*        dt;
    const char*         tmp;
    char                mthd;

    do
    {
        /* get type of return value */
        PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &dt) == -1);
        if (*ptd->ptr == ';') ptd->ptr++;

        /* get types of parameters */
        if (*ptd->ptr == ':')
        {
            PTS_ABORTIF(ptd, !(tmp = strchr(ptd->ptr + 1, ';')));
            ptd->ptr = tmp + 1;
        }
        PTS_ABORTIF(ptd, !(*ptd->ptr >= '0' && *ptd->ptr <= '9'));
        ptd->ptr++;
        PTS_ABORTIF(ptd, !(ptd->ptr[0] >= 'A' && *ptd->ptr <= 'D'));
        mthd = *++ptd->ptr;
        PTS_ABORTIF(ptd, mthd != '.' && mthd != '?' && mthd != '*');
        ptd->ptr++;
        if (mthd == '*')
        {
            long int            ofs;

            PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &ofs) == -1);
            PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
            PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &dt) == -1);
            PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
        }
    } while (*ptd->ptr != ';');
    ptd->ptr++;

    return 0;
}