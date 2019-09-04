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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  package; scalar_t__ retval; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ IDABORT ; 
 scalar_t__ IDCANCEL ; 
 scalar_t__ IDOK ; 
 scalar_t__ IDRETRY ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  event_cleanup_subscriptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_dialog_end_dialog (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmpW (char const*,char const*) ; 

__attribute__((used)) static UINT event_end_dialog( msi_dialog *dialog, const WCHAR *argument )
{
    static const WCHAR exitW[] = {'E','x','i','t',0};
    static const WCHAR retryW[] = {'R','e','t','r','y',0};
    static const WCHAR ignoreW[] = {'I','g','n','o','r','e',0};
    static const WCHAR returnW[] = {'R','e','t','u','r','n',0};

    if (!strcmpW( argument, exitW ))
        dialog->retval = IDCANCEL;
    else if (!strcmpW( argument, retryW ))
        dialog->retval = IDRETRY;
    else if (!strcmpW( argument, ignoreW ))
        dialog->retval = IDOK;
    else if (!strcmpW( argument, returnW ))
        dialog->retval = 0;
    else
    {
        ERR("Unknown argument string %s\n", debugstr_w(argument));
        dialog->retval = IDABORT;
    }
    event_cleanup_subscriptions( dialog->package, dialog->name );
    msi_dialog_end_dialog( dialog );
    return ERROR_SUCCESS;
}