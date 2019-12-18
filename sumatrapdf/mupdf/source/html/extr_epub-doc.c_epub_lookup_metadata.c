#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {char* dc_title; char* dc_creator; } ;
typedef  TYPE_1__ epub_document ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_META_FORMAT ; 
 int /*<<< orphan*/  FZ_META_INFO_AUTHOR ; 
 int /*<<< orphan*/  FZ_META_INFO_TITLE ; 
 scalar_t__ fz_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
epub_lookup_metadata(fz_context *ctx, fz_document *doc_, const char *key, char *buf, int size)
{
	epub_document *doc = (epub_document*)doc_;
	if (!strcmp(key, FZ_META_FORMAT))
		return (int)fz_strlcpy(buf, "EPUB", size);
	if (!strcmp(key, FZ_META_INFO_TITLE) && doc->dc_title)
		return (int)fz_strlcpy(buf, doc->dc_title, size);
	if (!strcmp(key, FZ_META_INFO_AUTHOR) && doc->dc_creator)
		return (int)fz_strlcpy(buf, doc->dc_creator, size);
	return -1;
}