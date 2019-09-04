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
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  _addReplyProtoToList (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ _addReplyToBuffer (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ prepareClientToWrite (int /*<<< orphan*/ *) ; 

void addReplyProto(client *c, const char *s, size_t len) {
    if (prepareClientToWrite(c) != C_OK) return;
    if (_addReplyToBuffer(c,s,len) != C_OK)
        _addReplyProtoToList(c,s,len);
}