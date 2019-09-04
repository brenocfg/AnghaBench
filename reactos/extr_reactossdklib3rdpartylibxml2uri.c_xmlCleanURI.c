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
typedef  TYPE_1__* xmlURIPtr ;
struct TYPE_3__ {int /*<<< orphan*/ * query_raw; int /*<<< orphan*/ * query; int /*<<< orphan*/ * authority; int /*<<< orphan*/ * opaque; int /*<<< orphan*/ * fragment; int /*<<< orphan*/ * path; int /*<<< orphan*/ * user; int /*<<< orphan*/ * server; int /*<<< orphan*/ * scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xmlCleanURI(xmlURIPtr uri) {
    if (uri == NULL) return;

    if (uri->scheme != NULL) xmlFree(uri->scheme);
    uri->scheme = NULL;
    if (uri->server != NULL) xmlFree(uri->server);
    uri->server = NULL;
    if (uri->user != NULL) xmlFree(uri->user);
    uri->user = NULL;
    if (uri->path != NULL) xmlFree(uri->path);
    uri->path = NULL;
    if (uri->fragment != NULL) xmlFree(uri->fragment);
    uri->fragment = NULL;
    if (uri->opaque != NULL) xmlFree(uri->opaque);
    uri->opaque = NULL;
    if (uri->authority != NULL) xmlFree(uri->authority);
    uri->authority = NULL;
    if (uri->query != NULL) xmlFree(uri->query);
    uri->query = NULL;
    if (uri->query_raw != NULL) xmlFree(uri->query_raw);
    uri->query_raw = NULL;
}