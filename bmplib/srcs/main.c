/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:50:49 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/13 12:47:26 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"
#include <sys/stat.h>

void			generate_bitmap_image(unsigned char *img, int h, int w,
										char *fn)
{
	unsigned char	padding[3];
	int				i[2];
	FILE			*imgfile;

	if (!(mkdir("Screen Shots", S_IRWXU|S_IRWXG|S_IROTH)))
		return ;
	imgfile = fopen(fn, "wb");
	if (!imgfile)
		return ;
	padding[0] = 0;
	padding[1] = 0;
	padding[2] = 0;
	fwrite(create_file_header(h, w), 1, FILEHEADERSIZE, imgfile);
	fwrite(create_info_header(h, w), 1, INFOHEADERSIZE, imgfile);
	i[1] = (4 - (w * BYTESPERPIXEL) % 4) % 4;
	i[0] = 0;
	while (i[0] < h)
	{
		fwrite(img + (i[0] * w * BYTESPERPIXEL), BYTESPERPIXEL, w, imgfile);
		fwrite(padding, 1, i[1], imgfile);
		i[0]++;
	}
	fclose(imgfile);
	free(fn);
}

unsigned char	*create_file_header(int h, int w)
{
	int						filesize;
	static unsigned char	fileheader[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
												0, 0, 0, 0, 0, 0};

	filesize = FILEHEADERSIZE + INFOHEADERSIZE + BYTESPERPIXEL * w * h;
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(filesize);
	fileheader[3] = (unsigned char)(filesize >> 8);
	fileheader[4] = (unsigned char)(filesize >> 16);
	fileheader[5] = (unsigned char)(filesize >> 24);
	fileheader[10] = (unsigned char)(FILEHEADERSIZE + INFOHEADERSIZE);
	return (fileheader);
}

unsigned char	*create_info_header(int h, int w)
{
	static unsigned char	infohead[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	infohead[0] = (unsigned char)(INFOHEADERSIZE);
	infohead[4] = (unsigned char)(w);
	infohead[5] = (unsigned char)(w >> 8);
	infohead[6] = (unsigned char)(w >> 16);
	infohead[7] = (unsigned char)(w >> 24);
	infohead[8] = (unsigned char)(h);
	infohead[9] = (unsigned char)(h >> 8);
	infohead[10] = (unsigned char)(h >> 16);
	infohead[11] = (unsigned char)(h >> 24);
	infohead[12] = (unsigned char)(1);
	infohead[14] = (unsigned char)(BYTESPERPIXEL * 8);

	return (infohead);
}
