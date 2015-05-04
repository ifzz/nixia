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

#ifndef __CS_PERF_CSPERF_DEFAULTS_H
#define __CS_PERF_CSPERF_DEFAULTS_H
enum asn_role {
    CS_CLIENT,
    CS_SERVER
};

/* General constants */
#define CSPERF_DEFAULT_DATA_BLOCKLEN (1024) 
#define CSPERF_DEFAULT_SERVER_PORT   5001
#define CSPERF_DEFAULT_DATA_BLOCKS   1000 
#define CSPERF_DEFAULT_CLIENT_OUTPUT_FILE "csperf_client_out.txt" 
#define CSPERF_DEFAULT_SERVER_OUTPUT_FILE "csperf_server_out.txt" 

/* Max constants */
#define MAX_CLIENT_RUNTIME 6000 

#endif /* __CS_PERF_CSPERF_DEFAULTS_H */
