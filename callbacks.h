/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:51:45 by mribouch          #+#    #+#             */
/*   Updated: 2019/06/26 14:58:05 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLBACKS_H
# define CALLBACKS_H
# include "wolf.h"

/*
** Input Event Masks. Used as event-mask window attribute and as arguments
** to Grab requests.  Not to be confused with event names.
*/

# define NO_EVENT_MASK                    (0L<<0)
# define KEY_PRESS_MASK                    (1L<<0)
# define KEY_RELEASE_MASK                (1L<<1)
# define BUTTON_PRESS_MASK                (1L<<2)
# define BUTTON_RELEASE_MASK            (1L<<3)
# define ENTER_WINDOW_MASK                (1L<<4)
# define LEAVE_WINDOW_MASK                (1L<<5)
# define POINTER_MOTION_MASK            (1L<<6)
# define POINTER_MOTION_HINT_MASK        (1L<<7)
# define BUTTON_1_MOTION_MASK            (1L<<8)
# define BUTTON_2_MOTION_MASK            (1L<<9)
# define BUTTON_3_MOTION_MASK            (1L<<10)
# define BUTTON_4_MOTION_MASK            (1L<<11)
# define BUTTON_5_MOTION_MASK            (1L<<12)
# define BUTTON_MOTION_MASK                (1L<<13)
# define KEYMAP_STATE_MASK                (1L<<14)
# define EXPOSURE_MASK                    (1L<<15)
# define VISIBILITY_CHANGE_MASK            (1L<<16)
# define STRUCTURE_NOTIFY_MASK            (1L<<17)
# define RESIZED_REDIRECT_MASK            (1L<<18)
# define SUBSTRUCTURE_NOTIFY_MASK        (1L<<19)
# define SUBSTRUCTURE_REDIRECT_MASK	(1L<<20)
# define FOCUS_CHANGE_MASK                (1L<<21)
# define PROPERTY_CHANGE_MASK            (1L<<22)
# define COLORMAP_CHANGE_MASK            (1L<<23)
# define OWNER_GRAB_BUTTON_MASK            (1L<<24)

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