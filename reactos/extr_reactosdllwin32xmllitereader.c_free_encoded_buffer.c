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
typedef  int /*<<< orphan*/  xmlreaderinput ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ encoded_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  readerinput_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_encoded_buffer(xmlreaderinput *input, encoded_buffer *buffer)
{
    readerinput_free(input, buffer->data);
}