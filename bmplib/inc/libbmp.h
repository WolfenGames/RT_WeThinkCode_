/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:52:32 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/12 17:10:46 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBMP_H
# define LIBBMP_H

# include "libft.h"
# include <stdio.h>
# define BYTESPERPIXEL	3
# define FILEHEADERSIZE	14
# define INFOHEADERSIZE	40
# define FILENAME		"Best RT you ever did see.bmp"

void			generate_bitmap_image(unsigned char *img, int h, int w,
										char *fn);
unsigned char	*create_info_header(int h, int w);
unsigned char	*create_file_header(int h, int w);

#endif