/*
*    Copyright (C) 2015 Nikhil AP 
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

#include "csperf_network.h"

/* Create asn message with header.
 * message_info argument is used if the 
 * message type is command */
asn_message_pdu*
csperf_network_create_pdu(uint8_t message_type, 
    uint8_t message_info, uint32_t message_len)
{
    int i;
    asn_message_pdu  *header = NULL;
    asn_command_pdu command;

    /* If the message_len is huge (> 1GB), we might need 
     * to use mmap */
    header = calloc(1, message_len + CS_HEADER_PDU_LEN);

    if (!header) {
        return NULL;
    }

    header->total_len = CS_HEADER_PDU_LEN + message_len; 
    header->magic = CS_MAGIC;
    header->message_type = message_type;

    if (message_type == CS_MSG_DATA) {
        /* Randomize the data */
        for (i = 0; i < message_len; i++) {
            header->message[i] = rand(); 
        }
    } else {
        memset(&command, 0, sizeof(asn_command_pdu));
        command.command_type = message_info;

        /* Copy the command as the message payload */
        memcpy(header->message, &command, message_len);
    }
    return header;
}

/* Usually called when the pdu is read from the socket.
   Returns whether pdu is command or data.
   If the complete message is not received, returns 0 */
int 
csperf_network_get_pdu_type(struct evbuffer *buf, uint32_t *len)
{
    asn_message_pdu     header;
    uint32_t            total_len;
    size_t buffer_len = evbuffer_get_length(buf);

    if (buffer_len < CS_HEADER_PDU_LEN) {
        /* The size field hasn't arrived. */
        return 0; 
    }

    /* We use evbuffer_copyout here so that messgae will stay
       in the buffer for now. */
    evbuffer_copyout(buf, &header, CS_HEADER_PDU_LEN);
    total_len = header.total_len;

    if (buffer_len < total_len) {
        /* The pdu hasn't arrived */ 
        return 0; 
    }
    *len = header.total_len;

    /* Check if it is data or command */
    if (header.message_type == CS_MSG_DATA) {
        return CS_MSG_DATA;
    }

    if (header.message_type == CS_MSG_COMMAND) {
        return CS_MSG_COMMAND;
    }

    /* Error! */
    return -1;
}

/* Get time in millisecond */
uint64_t 
csperf_network_get_time(char *buf)
{
    char            fmt[64];
    struct tm       *tm;
    struct timespec tv;
    uint64_t s;

    clock_gettime(CLOCK_MONOTONIC, &tv);
    if (buf) {
        if((tm = localtime(&tv.tv_sec)) != NULL) {
            strftime(fmt, sizeof(fmt), "%Y-%m-%d %H:%M:%S.%03u", tm);
            snprintf(buf, sizeof(fmt), fmt, tv.tv_nsec / 1000LL);
        }
    }
    s = tv.tv_sec * 1000LL;
    return(s + tv.tv_nsec / 1000000LL);
}
