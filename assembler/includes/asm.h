/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 21:47:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/29 21:57:54 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

typedef enum
{
    LABEL,
    OPERATION,
    DIRECT,
    DIRECT_LABEL,
    INDIRECT,
    INDIRECT_LABEL,
    REGISTER,
    SEPARATOR
}   t_type;

#endif
