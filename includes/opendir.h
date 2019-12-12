/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:23:57 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/12 18:21:55 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// typedef struct                  s_opendir
// {
// 	int                         dd_fd;	/* file descriptor associated with directory */
// 	long                        dd_loc;	/* offset in current buffer */
// 	long                        dd_size;	/* amount of data returned */
// 	char                        *dd_buf;	/* data buffer */
// 	int                         dd_len;	/* size of data buffer */
// 	long                        dd_seek;	/* magic cookie returned */
// 	long                        dd_rewind;	/* magic cookie for rewinding */
// 	int                         dd_flags;	/* flags for readdir */
// 	__darwin_pthread_mutex_t    dd_lock; /* for thread locking */
// 	struct _telldir             *dd_td; /* telldir position recording */
// }                               t_opendir;