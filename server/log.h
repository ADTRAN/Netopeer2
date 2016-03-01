/**
 * @file log.h
 * @author Radek Krejci <rkrejci@cesnet.cz>
 * @brief netopeer2-server log functions
 *
 * Copyright (c) 2016 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef NP2SRV_LOG_H_
#define NP2SRV_LOG_H_

#include <libyang/libyang.h>
#include <nc_server.h>

/**
 * @brief Verbose level variable
 */
extern volatile uint8_t verbose_level;

/**
 * @brief internal printing function, follows the levels from libnetconf2
 * @param[in] level Verbose level
 * @param[in] format Formatting string
 */
void prv_printf(NC_VERB_LEVEL level, const char *format, ...);

/*
 * Verbose printing macros
 */
#define ERR(format,args...) prv_printf(NC_VERB_ERROR,format,##args)
#define WRN(format,args...) if(verbose_level>=NC_VERB_WARNING){prv_printf(NC_VERB_WARNING,format,##args);}
#define VRB(format,args...) if(verbose_level>=NC_VERB_VERBOSE){prv_printf(NC_VERB_VERBOSE,format,##args);}
#define DBG(format,args...) if(verbose_level>=NC_VERB_DEBUG){prv_printf(NC_VERB_DEBUG,format,##args);}

#define EMEM ERR("Memory allocation failed (%s:%d)", __FILE__, __LINE__)

/**
 * @brief printer callback for libnetconf2
 */
void print_clb_nc2(NC_VERB_LEVEL level, const char *msg);

/**
 * @brief printer callback for libyang
 */
void print_clb_ly(LY_LOG_LEVEL level, const char *msg, const char *path);

/**
 * @brief printer callback for sysrepo
 */
void print_clb_sr(sr_log_level_t level, const char *msg);

#endif /* NP2SRV_LOG_H_ */