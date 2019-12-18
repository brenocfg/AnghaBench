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
typedef  int /*<<< orphan*/  uint32_t ;
struct ipc_response {int size; int type; char* payload; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ipc_magic ;
typedef  int /*<<< orphan*/  data32 ;

/* Variables and functions */
 int IPC_HEADER_SIZE ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  free (struct ipc_response*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ recv (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_abort (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

struct ipc_response *ipc_recv_response(int socketfd) {
	char data[IPC_HEADER_SIZE];
	uint32_t *data32 = (uint32_t *)(data + sizeof(ipc_magic));

	size_t total = 0;
	while (total < IPC_HEADER_SIZE) {
		ssize_t received = recv(socketfd, data + total, IPC_HEADER_SIZE - total, 0);
		if (received <= 0) {
			sway_abort("Unable to receive IPC response");
		}
		total += received;
	}

	struct ipc_response *response = malloc(sizeof(struct ipc_response));
	if (!response) {
		goto error_1;
	}

	total = 0;
	memcpy(&response->size, &data32[0], sizeof(data32[0]));
	memcpy(&response->type, &data32[1], sizeof(data32[1]));

	char *payload = malloc(response->size + 1);
	if (!payload) {
		goto error_2;
	}

	while (total < response->size) {
		ssize_t received = recv(socketfd, payload + total, response->size - total, 0);
		if (received < 0) {
			sway_abort("Unable to receive IPC response");
		}
		total += received;
	}
	payload[response->size] = '\0';
	response->payload = payload;

	return response;
error_2:
	free(response);
error_1:
	sway_log(SWAY_ERROR, "Unable to allocate memory for IPC response");
	return NULL;
}