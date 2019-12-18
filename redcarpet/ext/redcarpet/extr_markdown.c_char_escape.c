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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* normal_text ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufputc (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
char_escape(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t offset, size_t size)
{
	static const char *escape_chars = "\\`*_{}[]()#+-.!:|&<>^~=";
	struct buf work = { 0, 0, 0, 0 };

	if (size > 1) {
		if (strchr(escape_chars, data[1]) == NULL)
			return 0;

		if (rndr->cb.normal_text) {
			work.data = data + 1;
			work.size = 1;
			rndr->cb.normal_text(ob, &work, rndr->opaque);
		}
		else bufputc(ob, data[1]);
	} else if (size == 1) {
		bufputc(ob, data[0]);
	}

	return 2;
}