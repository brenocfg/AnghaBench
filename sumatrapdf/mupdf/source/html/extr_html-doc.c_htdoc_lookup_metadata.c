#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* html; } ;
typedef  TYPE_2__ html_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {char* title; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_META_FORMAT ; 
 int /*<<< orphan*/  FZ_META_INFO_TITLE ; 
 scalar_t__ fz_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
htdoc_lookup_metadata(fz_context *ctx, fz_document *doc_, const char *key, char *buf, int size)
{
	html_document *doc = (html_document*)doc_;
	if (!strcmp(key, FZ_META_FORMAT))
		return (int)fz_strlcpy(buf, "XHTML", size);
	if (!strcmp(key, FZ_META_INFO_TITLE) && doc->html->title)
		return (int)fz_strlcpy(buf, doc->html->title, size);
	return -1;
}