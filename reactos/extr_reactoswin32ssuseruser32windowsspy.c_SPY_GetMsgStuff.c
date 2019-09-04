#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* name; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ USER_MSG ;
struct TYPE_9__ {int /*<<< orphan*/  count; int /*<<< orphan*/  classmsg; scalar_t__ classname; } ;
struct TYPE_8__ {int msgnum; char* msg_name; int /*<<< orphan*/  data_len; int /*<<< orphan*/ * wnd_class; } ;
typedef  TYPE_2__ SPY_INSTANCE ;
typedef  size_t INT ;

/* Variables and functions */
 scalar_t__ GlobalGetAtomNameA (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* SPY_Bsearch_Msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPY_GetClassName (TYPE_2__*) ; 
 char* SPY_GetMsgInternal (int) ; 
 int WM_APP ; 
 int WM_USER ; 
 TYPE_3__* cc_array ; 
 int /*<<< orphan*/  lstrcpynA (char*,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmpiW (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SPY_GetMsgStuff( SPY_INSTANCE *sp_e )
{
    const USER_MSG *p;
    const char *msg_name = SPY_GetMsgInternal( sp_e->msgnum );

    sp_e->data_len = 0;
    if (!msg_name)
    {
        INT i = 0;

        if (sp_e->msgnum >= 0xc000)
        {
            if (GlobalGetAtomNameA( sp_e->msgnum, sp_e->msg_name+1, sizeof(sp_e->msg_name)-2 ))
            {
                sp_e->msg_name[0] = '\"';
                strcat( sp_e->msg_name, "\"" );
                return;
            }
        }
        if (!sp_e->wnd_class[0]) SPY_GetClassName(sp_e);

#if DEBUG_SPY
        TRACE("looking class %s\n", debugstr_w(sp_e->wnd_class));
#endif

        while (cc_array[i].classname &&
               strcmpiW(cc_array[i].classname, sp_e->wnd_class) != 0) i++;

        if (cc_array[i].classname)
        {
#if DEBUG_SPY
            TRACE("process class %s, first %p, last %p\n",
                  debugstr_w(cc_array[i].classname), cc_array[i].classmsg,
                  cc_array[i].lastmsg);
#endif
            p = SPY_Bsearch_Msg (cc_array[i].classmsg, cc_array[i].count, sp_e->msgnum);
            if (p) {
                lstrcpynA (sp_e->msg_name, p->name, sizeof(sp_e->msg_name));
                sp_e->data_len = p->len;
                return;
            }
        }
        if (sp_e->msgnum >= WM_USER && sp_e->msgnum <= WM_APP)
            sprintf( sp_e->msg_name, "WM_USER+%d", sp_e->msgnum - WM_USER );
        else
            sprintf( sp_e->msg_name, "%04x", sp_e->msgnum );
    }
    else
    {
        lstrcpynA(sp_e->msg_name, msg_name, sizeof(sp_e->msg_name));
    }
}