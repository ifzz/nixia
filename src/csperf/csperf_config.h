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

#ifndef __CS_PERF_CONFIG_H
#define __CS_PERF_CONFIG_H

#include <stdint.h>
#include "json_parser.h" 

typedef struct csperf_config_s {
    uint8_t      role; /* Client or server */
    uint8_t      server_echo;
    uint16_t     server_port; 
    uint16_t     mark_interval; 
    uint32_t     data_block_size;   /* Block size of each data segment */
    uint32_t     total_data_blocks; /* Total blocks to be sent */
    uint16_t     client_runtime; /* Total duration of the test. -t */
    uint64_t     data_size;       /* Total size of data to send */
    int          repeat_count;
    char         *server_ip; 
    char         *output_directory;
    char         *client_output_file;
    char         *server_output_file;
}csperf_config_t;

int csperf_config_init(cJSON *root);
void csperf_config_cleanup(csperf_config_t* config);
csperf_config_t *csperf_config_get();
#endif /* __CS_PERF_CONFIG_H */
#
