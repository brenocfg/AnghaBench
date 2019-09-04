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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 char* get_nscategory_entry (char*,char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_strdupWtoA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsfree (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static BOOL is_supported_doc_mime(const WCHAR *mime)
{
    char *nscat, *mimea;
    BOOL ret;

    mimea = heap_strdupWtoA(mime);
    if(!mimea)
        return FALSE;

    nscat = get_nscategory_entry("Gecko-Content-Viewers", mimea);

    ret = nscat != NULL && !strcmp(nscat, "@mozilla.org/content/document-loader-factory;1");

    heap_free(mimea);
    nsfree(nscat);
    return ret;
}