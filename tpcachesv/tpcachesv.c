/* 
** Cache event receiver, but what we do not want is to subscribe on local events
** if subscribed by mask, but if it is local node, then just ignore
** Also we advertise service name with node id in it. So that remote node in future
** may call service directly.
** -----
** Also server provides management services (like cache lookup and delete)
**
** @file tpcachesv.c
** 
** -----------------------------------------------------------------------------
** Enduro/X Middleware Platform for Distributed Transaction Processing
** Copyright (C) 2018 Mavimax, Ltd. All Rights Reserved.
** This software is released under one of the following licenses:
** GPL or Mavimax's license for commercial use.
** -----------------------------------------------------------------------------
** GPL license:
** 
** This program is free software; you can redistribute it and/or modify it under
** the terms of the GNU General Public License as published by the Free Software
** Foundation; either version 2 of the License, or (at your option) any later
** version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
** PARTICULAR PURPOSE. See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with
** this program; if not, write to the Free Software Foundation, Inc., 59 Temple
** Place, Suite 330, Boston, MA 02111-1307 USA
**
** -----------------------------------------------------------------------------
** A commercial use license is available from Mavimax, Ltd
** contact@mavimax.com
** -----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <regex.h>
#include <utlist.h>

#include <ndebug.h>
#include <atmi.h>
#include <sys_unix.h>
#include <atmi_int.h>
#include <typed_buf.h>
#include <ndrstandard.h>
#include <ubf.h>
#include <Exfields.h>
#include <atmi_shm.h>
#include <exregex.h>
#include "tpcachesv.h"
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/

/**
 * Process incoming events - put and delete
 * @param p_svc
 */
void CACHEEV (TPSVCINFO *p_svc)
{
    int ret=EXSUCCEED;

out:
    tpreturn(  ret==EXSUCCEED?TPSUCCESS:TPFAIL,
                0,
                NULL,
                0L,
                0L);
}

/**
 * Process management requests (list headers, list all, list 
 * single, delete all, delete single).
 * The dump shall be provided in tpexport format.
 * 
 * @param p_svc
 */
void CACHEMG (TPSVCINFO *p_svc)
{
    int ret=EXSUCCEED;

out:
    tpreturn(  ret==EXSUCCEED?TPSUCCESS:TPFAIL,
                0,
                NULL,
                0L,
                0L);
}

/**
 * Standard server init
 */
int NDRX_INTEGRA(tpsvrinit)(int argc, char **argv)
{
    int ret=EXSUCCEED;
    char tmpsvc[MAXTIDENT+1];             
    long nodeid;
    
    NDRX_LOG(log_debug, "%s called", __func__);
    
    nodeid = tpgetnodeid();
    
    if (EXFAIL==nodeid)
    {
        NDRX_LOG(log_error, "Failed to get nodeid: %s", tpstrerror(tperrno));
        EXFAIL_OUT(ret);
    }
    
    snprintf(tmpsvc, sizeof(tmpsvc), NDRX_CACHE_EVSVC, nodeid);

    if (EXSUCCEED!=tpadvertise(tmpsvc, CACHEEV))
    {
        NDRX_LOG(log_error, "Failed to initialize [%s]!", tmpsvc);
        ret=EXFAIL;
        goto out;
    }
    
    snprintf(tmpsvc, sizeof(tmpsvc), NDRX_CACHE_MGSVC, nodeid);
    
    if (EXSUCCEED!=tpadvertise(tmpsvc, CACHEEV))
    {
        NDRX_LOG(log_error, "Failed to initialize [%s]!", tmpsvc);
        ret=EXFAIL;
        goto out;
    }
    
out:
    return ret;
}

void NDRX_INTEGRA(tpsvrdone) (void)
{
    NDRX_LOG(log_debug, "%s called", __func__);
}
