/**
 * @brief TPNULL buffer type support
 *
 * @file typed_null.c
 */
/* -----------------------------------------------------------------------------
 * Enduro/X Middleware Platform for Distributed Transaction Processing
 * Copyright (C) 2009-2016, ATR Baltic, Ltd. All Rights Reserved.
 * Copyright (C) 2017-2018, Mavimax, Ltd. All Rights Reserved.
 * This software is released under one of the following licenses:
 * AGPL or Mavimax's license for commercial use.
 * -----------------------------------------------------------------------------
 * AGPL license:
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License, version 3 as published
 * by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Affero General Public License, version 3
 * for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * -----------------------------------------------------------------------------
 * A commercial use license is available from Mavimax, Ltd
 * contact@mavimax.com
 * -----------------------------------------------------------------------------
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <ndrstandard.h>
#include <typed_buf.h>
#include <ndebug.h>
#include <tperror.h>
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/

/**
 * Basic init data structure allocator
 * @param subtype
 * @param len
 * @return
 */
expublic char	* TPNULL_tpalloc (typed_buffer_descr_t *descr, 
        char *subtype, long *len)
{
    char *ret=NULL;
    char fn[] = "TPNULL_tpalloc";

    /* Allocate UBF buffer, 1 byte, what so ever.. */
    ret=NDRX_MALLOC(1);

    if (NULL==ret)
    {
        NDRX_LOG(log_error, "%s: Failed to allocate TPNULL buffer!", fn);
        ndrx_TPset_error_fmt(TPEOS, "TPNULL failed to allocate: %d bytes", 
                sizeof(TPINIT));
        goto out;
    }

out:
    return ret;
}

/**
 * Gracefully remove free up the buffer
 * @param descr
 * @param buf
 */
expublic void TPNULL_tpfree(typed_buffer_descr_t *descr, char *buf)
{
    NDRX_FREE(buf);
}
/* vim: set ts=4 sw=4 et smartindent: */
