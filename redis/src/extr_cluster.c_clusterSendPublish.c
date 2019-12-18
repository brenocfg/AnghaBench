#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int uint32_t ;
struct TYPE_17__ {TYPE_5__* ptr; } ;
typedef  TYPE_4__ robj ;
typedef  int /*<<< orphan*/  clusterMsgDataPublish ;
struct TYPE_14__ {unsigned char* bulk_data; void* message_len; void* channel_len; } ;
struct TYPE_15__ {TYPE_1__ msg; } ;
struct TYPE_16__ {TYPE_2__ publish; } ;
struct TYPE_18__ {TYPE_3__ data; void* totlen; } ;
typedef  TYPE_5__ clusterMsg ;
typedef  int /*<<< orphan*/  clusterLink ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_PUBLISH ; 
 int /*<<< orphan*/  clusterBroadcastMessage (unsigned char*,int) ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterSendMessage (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_4__*) ; 
 TYPE_4__* getDecodedObject (TYPE_4__*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_5__*,int) ; 
 int sdslen (TYPE_5__*) ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 
 unsigned char* zmalloc (int) ; 

void clusterSendPublish(clusterLink *link, robj *channel, robj *message) {
    unsigned char *payload;
    clusterMsg buf[1];
    clusterMsg *hdr = (clusterMsg*) buf;
    uint32_t totlen;
    uint32_t channel_len, message_len;

    channel = getDecodedObject(channel);
    message = getDecodedObject(message);
    channel_len = sdslen(channel->ptr);
    message_len = sdslen(message->ptr);

    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_PUBLISH);
    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    totlen += sizeof(clusterMsgDataPublish) - 8 + channel_len + message_len;

    hdr->data.publish.msg.channel_len = htonl(channel_len);
    hdr->data.publish.msg.message_len = htonl(message_len);
    hdr->totlen = htonl(totlen);

    /* Try to use the local buffer if possible */
    if (totlen < sizeof(buf)) {
        payload = (unsigned char*)buf;
    } else {
        payload = zmalloc(totlen);
        memcpy(payload,hdr,sizeof(*hdr));
        hdr = (clusterMsg*) payload;
    }
    memcpy(hdr->data.publish.msg.bulk_data,channel->ptr,sdslen(channel->ptr));
    memcpy(hdr->data.publish.msg.bulk_data+sdslen(channel->ptr),
        message->ptr,sdslen(message->ptr));

    if (link)
        clusterSendMessage(link,payload,totlen);
    else
        clusterBroadcastMessage(payload,totlen);

    decrRefCount(channel);
    decrRefCount(message);
    if (payload != (unsigned char*)buf) zfree(payload);
}