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
typedef  int uint8_t ;
struct AudioState {int* delta; int lastdelta; int lastbyte; int* weight; scalar_t__* error; int count; } ;
typedef  int int8_t ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t rar_decode_audio(struct AudioState *state, int8_t *channeldelta, int8_t delta)
{
    uint8_t predbyte, byte;
    int prederror;

    state->delta[3] = state->delta[2];
    state->delta[2] = state->delta[1];
    state->delta[1] = state->lastdelta - state->delta[0];
    state->delta[0] = state->lastdelta;

    predbyte = ((8 * state->lastbyte + state->weight[0] * state->delta[0] + state->weight[1] * state->delta[1] + state->weight[2] * state->delta[2] + state->weight[3] * state->delta[3] + state->weight[4] * *channeldelta) >> 3) & 0xFF;
    byte = (predbyte - delta) & 0xFF;

    prederror = delta << 3;
    state->error[0] += abs(prederror);
    state->error[1] += abs(prederror - state->delta[0]); state->error[2] += abs(prederror + state->delta[0]);
    state->error[3] += abs(prederror - state->delta[1]); state->error[4] += abs(prederror + state->delta[1]);
    state->error[5] += abs(prederror - state->delta[2]); state->error[6] += abs(prederror + state->delta[2]);
    state->error[7] += abs(prederror - state->delta[3]); state->error[8] += abs(prederror + state->delta[3]);
    state->error[9] += abs(prederror - *channeldelta); state->error[10] += abs(prederror + *channeldelta);

    *channeldelta = state->lastdelta = (int8_t)(byte - state->lastbyte);
    state->lastbyte = byte;

    if (!(++state->count & 0x1F)) {
        uint8_t i, idx = 0;
        for (i = 1; i < 11; i++) {
            if (state->error[i] < state->error[idx])
                idx = i;
        }
        memset(state->error, 0, sizeof(state->error));

        switch (idx) {
        case 1: if (state->weight[0] >= -16) state->weight[0]--; break;
        case 2: if (state->weight[0] < 16) state->weight[0]++; break;
        case 3: if (state->weight[1] >= -16) state->weight[1]--; break;
        case 4: if (state->weight[1] < 16) state->weight[1]++; break;
        case 5: if (state->weight[2] >= -16) state->weight[2]--; break;
        case 6: if (state->weight[2] < 16) state->weight[2]++; break;
        case 7: if (state->weight[3] >= -16) state->weight[3]--; break;
        case 8: if (state->weight[3] < 16) state->weight[3]++; break;
        case 9: if (state->weight[4] >= -16) state->weight[4]--; break;
        case 10: if (state->weight[4] < 16) state->weight[4]++; break;
        }
    }

    return byte;
}