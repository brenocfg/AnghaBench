#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIDocShell ;
typedef  int /*<<< orphan*/  nsIClipboardCommands ;
struct TYPE_5__ {TYPE_1__* window; } ;
struct TYPE_4__ {scalar_t__ nswindow; } ;
typedef  TYPE_2__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  IID_nsIClipboardCommands ; 
 int /*<<< orphan*/  IID_nsIDocShell ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nsinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDocShell_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDocShell_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static nsIClipboardCommands *get_clipboard_commands(HTMLDocument *doc)
{
    nsIClipboardCommands *clipboard_commands;
    nsIDocShell *doc_shell;
    nsresult nsres;

    nsres = get_nsinterface((nsISupports*)doc->window->nswindow, &IID_nsIDocShell, (void**)&doc_shell);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDocShell interface\n");
        return NULL;
    }

    nsres = nsIDocShell_QueryInterface(doc_shell, &IID_nsIClipboardCommands, (void**)&clipboard_commands);
    nsIDocShell_Release(doc_shell);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIClipboardCommands interface\n");
        return NULL;
    }

    return clipboard_commands;
}