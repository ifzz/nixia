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

#include "log.h"
#include "common.h"

zlog_category_t* common_zc = NULL;
zlog_category_t* http_zc = NULL;
zlog_category_t* csperf_zc = NULL;

int
log_init()
{
	return (zlog_init(LOG_CONFIG_FILE));
}

zlog_category_t* 
log_get_cat()
{
    if (common_zc) {
        return common_zc;
    }
    
    common_zc = zlog_get_category(LOG_CATEGORY);
    return common_zc;
}

zlog_category_t* 
log_get_cat_http()
{
    if (http_zc) {
        return http_zc;
    }
    
    http_zc = zlog_get_category(HTTP_LOG_CATEGORY);
    return http_zc;
}

zlog_category_t* 
log_get_cat_csperf()
{
    if (csperf_zc) {
        return csperf_zc;
    }
    
    csperf_zc = zlog_get_category(CSPERF_LOG_CATEGORY);
    return csperf_zc;
}
