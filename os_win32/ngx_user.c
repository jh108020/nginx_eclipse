/*
 * Copyright (C) Igor Sysoev
 */


#include "../core/ngx_config.h"
#include "../core/ngx_core.h"


#if (NGX_CRYPT)

ngx_int_t
ngx_libc_crypt(ngx_pool_t *pool, u_char *key, u_char *salt, u_char **encrypted)
{
    /* STUB: a plain text password */

    *encrypted = key;

    return NGX_OK;
}

#endif /* NGX_CRYPT */
