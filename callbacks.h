/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:51:45 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 15:40:41 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLBACKS_H
# define CALLBACKS_H
# include "wolf.h"

/*
** Event names.  Used in "type" field in XEvent structures.  Not to be
** confused with event masks above.  They start from 2 because 0 and 1
** are reserved in the protocol for errors and replies.
*/

# define KEY_PRESS            2
# define KEY_RELEASE        3
# define BUTTON_PRESS        4
# define BUTTON_RELEASE        5
# define MOTION_NOTIFY        6
# define ENTER_NOTIFY        7
# define LEAVE_NOTIFY        8
# define FOCUS_INT            9
# define FOCUS_OUT            10
# define KEYMAP_NOTIFY        11
# define EXPOSE                12
# define GRAPHICS_EXPOSE    13
# define NO_EXPOSE            14
# define VISIBILITY_NOTIFY    15
# define CREATE_NOTIFY        16
# define DESTROY_NOTIFY        17
# define UNMAP_NOTIFY        18
# define MAP_NOTIFY            19
# define MAP_REQUEST        20
# define REPARENT_NOTIFY    21
# define CONFIGURE_NOTIFY    22
# define CONFIGURE_REQUEST    23
# define GRAVITY_NOTIFY        24
# define RESIZE_REQUEST        25
# define CIRCULATE_NOTIFY    26
# define CIRCULATE_REQUEST    27
# define PROPERTY_NOTIFY    28
# define SELECTION_CLEAR    29
# define SELECTION_REQUEST    30
# define SELECTION_NOTIFY    31
# define COLORMAP_NOTIFY    32
# define CLIENT_MESSAGE        33
# define MAPPING_NOTIFY        34
# define GENERIC_EVENT        35
# define LAST_EVENT            36

#endif
