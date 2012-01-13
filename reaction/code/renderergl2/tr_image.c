/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// tr_image.c
#include "tr_local.h"

static byte			 s_intensitytable[256];
static unsigned char s_gammatable[256];

int		gl_filter_min = GL_LINEAR_MIPMAP_NEAREST;
int		gl_filter_max = GL_LINEAR;

#define FILE_HASH_SIZE		1024
static	image_t*		hashTable[FILE_HASH_SIZE];

/*
** R_GammaCorrect
*/
void R_GammaCorrect( byte *buffer, int bufSize ) {
	int i;

	for ( i = 0; i < bufSize; i++ ) {
		buffer[i] = s_gammatable[buffer[i]];
	}
}

typedef struct {
	char *name;
	int	minimize, maximize;
} textureMode_t;

textureMode_t modes[] = {
	{"GL_NEAREST", GL_NEAREST, GL_NEAREST},
	{"GL_LINEAR", GL_LINEAR, GL_LINEAR},
	{"GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST},
	{"GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR},
	{"GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST},
	{"GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR}
};

/*
================
return a hash value for the filename
================
*/
static long generateHashValue( const char *fname ) {
	int		i;
	long	hash;
	char	letter;

	hash = 0;
	i = 0;
	while (fname[i] != '\0') {
		letter = tolower(fname[i]);
		if (letter =='.') break;				// don't include extension
		if (letter =='\\') letter = '/';		// damn path names
		hash+=(long)(letter)*(i+119);
		i++;
	}
	hash &= (FILE_HASH_SIZE-1);
	return hash;
}

/*
===============
GL_TextureMode
===============
*/
void GL_TextureMode( const char *string ) {
	int		i;
	image_t	*glt;

	for ( i=0 ; i< 6 ; i++ ) {
		if ( !Q_stricmp( modes[i].name, string ) ) {
			break;
		}
	}

	// hack to prevent trilinear from being set on voodoo,
	// because their driver freaks...
	if ( i == 5 && glConfig.hardwareType == GLHW_3DFX_2D3D ) {
		ri.Printf( PRINT_ALL, "Refusing to set trilinear on a voodoo.\n" );
		i = 3;
	}


	if ( i == 6 ) {
		ri.Printf (PRINT_ALL, "bad filter name\n");
		return;
	}

	gl_filter_min = modes[i].minimize;
	gl_filter_max = modes[i].maximize;

	// change all the existing mipmap texture objects
	for ( i = 0 ; i < tr.numImages ; i++ ) {
		glt = tr.images[ i ];
		if ( glt->flags & IMGFLAG_MIPMAP ) {
			GL_Bind (glt);
			qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter_min);
			qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter_max);
		}
	}
}

/*
===============
R_SumOfUsedImages
===============
*/
int R_SumOfUsedImages( void ) {
	int	total;
	int i;

	total = 0;
	for ( i = 0; i < tr.numImages; i++ ) {
		if ( tr.images[i]->frameUsed == tr.frameCount ) {
			total += tr.images[i]->uploadWidth * tr.images[i]->uploadHeight;
		}
	}

	return total;
}

/*
===============
R_ImageList_f
===============
*/
void R_ImageList_f( void ) {
	int		i;
	image_t	*image;
	int		texels;
	const char *yesno[] = {
		"no ", "yes"
	};

	ri.Printf (PRINT_ALL, "\n      -w-- -h-- -mm- -TMU- -if-- wrap --name-------\n");
	texels = 0;

	for ( i = 0 ; i < tr.numImages ; i++ ) {
		image = tr.images[ i ];

		texels += image->uploadWidth*image->uploadHeight;
		ri.Printf (PRINT_ALL,  "%4i: %4i %4i  %s   %d   ",
			i, image->uploadWidth, image->uploadHeight, yesno[(image->flags & IMGFLAG_MIPMAP) ? 1 : 0], image->TMU );
		switch ( image->internalFormat ) {
		case 1:
			ri.Printf( PRINT_ALL, "I    " );
			break;
		case 2:
			ri.Printf( PRINT_ALL, "IA   " );
			break;
		case 3:
			ri.Printf( PRINT_ALL, "RGB  " );
			break;
		case 4:
			ri.Printf( PRINT_ALL, "RGBA " );
			break;
		case GL_RGBA8:
			ri.Printf( PRINT_ALL, "RGBA8" );
			break;
		case GL_RGB8:
			ri.Printf( PRINT_ALL, "RGB8" );
			break;
		case GL_RGB4_S3TC:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
			ri.Printf( PRINT_ALL, "S3TC " );
			break;
		case GL_RGBA4:
			ri.Printf( PRINT_ALL, "RGBA4" );
			break;
		case GL_RGB5:
			ri.Printf( PRINT_ALL, "RGB5 " );
			break;
		default:
			ri.Printf( PRINT_ALL, "???? " );
		}

		switch ( image->wrapClampMode ) {
		case GL_REPEAT:
			ri.Printf( PRINT_ALL, "rept " );
			break;
		case GL_CLAMP_TO_EDGE:
			ri.Printf( PRINT_ALL, "clmp " );
			break;
		default:
			ri.Printf( PRINT_ALL, "%4i ", image->wrapClampMode );
			break;
		}
		
		ri.Printf( PRINT_ALL, " %s\n", image->imgName );
	}
	ri.Printf (PRINT_ALL, " ---------\n");
	ri.Printf (PRINT_ALL, " %i total texels (not including mipmaps)\n", texels);
	ri.Printf (PRINT_ALL, " %i total images\n\n", tr.numImages );
}

//=======================================================================

/*
================
ResampleTexture

Used to resample images in a more general than quartering fashion.

This will only be filtered properly if the resampled size
is greater than half the original size.

If a larger shrinking is needed, use the mipmap function 
before or after.
================
*/
static void ResampleTexture( byte *in, int inwidth, int inheight, byte *out,  
							int outwidth, int outheight ) {
	int		i, j;
	byte	*inrow, *inrow2;
	int		frac, fracstep;
	int		p1[2048], p2[2048];
	byte	*pix1, *pix2, *pix3, *pix4;

	if (outwidth>2048)
		ri.Error(ERR_DROP, "ResampleTexture: max width");
								
	fracstep = inwidth*0x10000/outwidth;

	frac = fracstep>>2;
	for ( i=0 ; i<outwidth ; i++ ) {
		p1[i] = 4*(frac>>16);
		frac += fracstep;
	}
	frac = 3*(fracstep>>2);
	for ( i=0 ; i<outwidth ; i++ ) {
		p2[i] = 4*(frac>>16);
		frac += fracstep;
	}

	for (i=0 ; i<outheight ; i++) {
		inrow = in + 4*inwidth*(int)((i+0.25)*inheight/outheight);
		inrow2 = in + 4*inwidth*(int)((i+0.75)*inheight/outheight);
		frac = fracstep >> 1;
		for (j=0 ; j<outwidth ; j++) {
			pix1 = inrow + p1[j];
			pix2 = inrow + p2[j];
			pix3 = inrow2 + p1[j];
			pix4 = inrow2 + p2[j];
			*out++ = (pix1[0] + pix2[0] + pix3[0] + pix4[0])>>2;
			*out++ = (pix1[1] + pix2[1] + pix3[1] + pix4[1])>>2;
			*out++ = (pix1[2] + pix2[2] + pix3[2] + pix4[2])>>2;
			*out++ = (pix1[3] + pix2[3] + pix3[3] + pix4[3])>>2;
		}
	}
}

#define COPYSAMPLE(a,b) *(unsigned int *)(a) = *(unsigned int *)(b)

// based on Fast Curve Based Interpolation
// from Fast Artifacts-Free Image Interpolation (http://www.andreagiachetti.it/icbi/)
// assumes data has a 2 pixel thick border of clamped or wrapped data
// expects data to be a grid with even (0, 0), (2, 0), (0, 2), (2, 2) etc pixels filled
static void DoFCBI(byte *in, byte *out, int width, int height)
{
	int x, y, i;
	byte *outbyte, *inbyte;

	//copy in to out
	for (y = 0; y < height; y+=2)
	{
		inbyte = in + y * width * 4;
		outbyte = out + y * width * 4;

		for (x = width / 2; x > 0; x--)
		{
			COPYSAMPLE(outbyte, inbyte);
			outbyte += 8;
			inbyte += 8;
		}
	}

	//for (y = 1; y < height; y += 2)
	for (y = 3; y < height - 4; y += 2)
	{
		// diagonals
		//
		// NWp  - northwest interpolated pixel
		// NEp  - northeast interpolated pixel
		// NWd  - northwest first derivative
		// NEd  - northeast first derivative
		// NWdd - northwest second derivative
		// NEdd - northeast second derivative
		//
		// Uses these samples:
		//
		//         0
		//   - - a - b - -
		//   - - - - - - -
		//   c - d - e - f
		// 0 - - - - - - -
		//   g - h - i - j
		//   - - - - - - -
		//   - - k - l - -
		//
		// x+2 uses these samples:
		//
		//         0
		//   - - - - a - b - -
		//   - - - - - - - - -
		//   - - c - d - e - f
		// 0 - - - - - - - - -
		//   - - g - h - i - j
		//   - - - - - - - - -
		//   - - - - k - l - -
		//
		// so we can reuse 8 of them on next iteration
		//
		// a=b, c=d, d=e, e=f, g=h, h=i, i=j, k=l
		//
		// only b, f, j, and l need to be sampled on next iteration

		byte sa[4], sb[4], sc[4], sd[4], se[4], sf[4], sg[4], sh[4], si[4], sj[4], sk[4], sl[4];
		byte *line1, *line2, *line3, *line4;

		//x = 1;
		x = 3;

		// optimization one
		//                       SAMPLE2(sa, x-1, y-3);
		//SAMPLE2(sc, x-3, y-1); SAMPLE2(sd, x-1, y-1); SAMPLE2(se, x+1, y-1);
		//SAMPLE2(sg, x-3, y+1); SAMPLE2(sh, x-1, y+1); SAMPLE2(si, x+1, y+1);
		//                       SAMPLE2(sk, x-1, y+3);

		// optimization two
		line1 = in + ((y - 3) * width + (x - 1)) * 4;
		line2 = in + ((y - 1) * width + (x - 3)) * 4;
		line3 = in + ((y + 1) * width + (x - 3)) * 4;
		line4 = in + ((y + 3) * width + (x - 1)) * 4;

		                                   COPYSAMPLE(sa, line1); line1 += 8;
		COPYSAMPLE(sc, line2); line2 += 8; COPYSAMPLE(sd, line2); line2 += 8; COPYSAMPLE(se, line2); line2 += 8;
		COPYSAMPLE(sg, line3); line3 += 8; COPYSAMPLE(sh, line3); line3 += 8; COPYSAMPLE(si, line3); line3 += 8;
		                                   COPYSAMPLE(sk, line4); line4 += 8;

	   outbyte = &out[(y * width + x) << 2];

		//for ( ; x < width; x += 2)
		for ( ; x < width - 4; x += 2)
		{
			// original
			//                       SAMPLE2(sa, x-1, y-3); SAMPLE2(sb, x+1, y-3);
			//SAMPLE2(sc, x-3, y-1); SAMPLE2(sd, x-1, y-1); SAMPLE2(se, x+1, y-1); SAMPLE2(sf, x+3, y-1);
			//SAMPLE2(sg, x-3, y+1); SAMPLE2(sh, x-1, y+1); SAMPLE2(si, x+1, y+1); SAMPLE2(sj, x+3, y+1);
			//                       SAMPLE2(sk, x-1, y+3); SAMPLE2(sl, x+1, y+3);

			// optimization one
			//SAMPLE2(sb, x+1, y-3);
			//SAMPLE2(sf, x+3, y-1);
			//SAMPLE2(sj, x+3, y+1);
			//SAMPLE2(sl, x+1, y+3);

			// optimization two
			COPYSAMPLE(sb, line1); line1 += 8;
			COPYSAMPLE(sf, line2); line2 += 8;
			COPYSAMPLE(sj, line3); line3 += 8;
			COPYSAMPLE(sl, line4); line4 += 8;

			for (i = 0; i < 4; i++)
			{	
				int NWd, NEd, NWp, NEp;

				NWp = sd[i] + si[i];
				NEp = se[i] + sh[i];
				NWd = abs(sd[i] - si[i]);
				NEd = abs(se[i] - sh[i]);

				if (NWd > 100 || NEd > 100 || abs(NWp-NEp) > 200)
				{
					if (NWd < NEd)
						*outbyte = NWp >> 1;
					else
						*outbyte = NEp >> 1;
				}
				else
				{
					int NWdd, NEdd;

					//NEdd = abs(sg + sd + sb - 3 * (se + sh) + sk + si + sf);
					//NWdd = abs(sa + se + sj - 3 * (sd + si) + sc + sh + sl);
					NEdd = abs(sg[i] + sb[i] - 3 * NEp + sk[i] + sf[i] + NWp);
					NWdd = abs(sa[i] + sj[i] - 3 * NWp + sc[i] + sl[i] + NEp);

					if (NWdd > NEdd)
						*outbyte = NWp >> 1;
					else
						*outbyte = NEp >> 1;
				}

				outbyte++;
			}

			outbyte += 4;

			                    COPYSAMPLE(sa, sb);
			COPYSAMPLE(sc, sd); COPYSAMPLE(sd, se); COPYSAMPLE(se, sf);
			COPYSAMPLE(sg, sh); COPYSAMPLE(sh, si); COPYSAMPLE(si, sj);
								COPYSAMPLE(sk, sl);
		}
	}

	// hack: copy out to in again
	for (y = 1; y < height; y+=2)
	{
		inbyte = out + y * width * 4 + 4;
		outbyte = in + y * width * 4 + 4;

		for (x = width / 2; x > 0; x--)
		{
			COPYSAMPLE(outbyte, inbyte);
			outbyte += 8;
			inbyte += 8;
		}
	}
	
	//for (y = 0; y < height; y++)
	for (y = 2; y < height - 3; y++)
	{
		// horizontal & vertical
		//
		// hp  - horizontally interpolated pixel
		// vp  - vertically interpolated pixel
		// hd  - horizontal first derivative
		// vd  - vertical first derivative
		// hdd - horizontal second derivative
		// vdd - vertical second derivative
		// Uses these samples:
		//
		//       0
		//   - a - b -
		//   c - d - e
		// 0 - f - g -
		//   h - i - j
		//   - k - l -
		//
		// x+2 uses these samples:
		//
		//       0
		//   - - - a - b -
		//   - - c - d - e
		// 0 - - - f - g -
		//   - - h - i - j
		//   - - - k - l -
		//
		// so we can reuse 7 of them on next iteration
		//
		// a=b, c=d, d=e, f=g, h=i, i=j, k=l
		//
		// only b, e, g, j, and l need to be sampled on next iteration

		byte sa[4], sb[4], sc[4], sd[4], se[4], sf[4], sg[4], sh[4], si[4], sj[4], sk[4], sl[4];
		byte *line1, *line2, *line3, *line4, *line5;

		//x = (y + 1) % 2;
		x = (y + 1) % 2 + 2;
		
		// optimization one
		//            SAMPLE2(sa, x-1, y-2);
		//SAMPLE2(sc, x-2, y-1); SAMPLE2(sd, x,   y-1);
		//            SAMPLE2(sf, x-1, y  );
		//SAMPLE2(sh, x-2, y+1); SAMPLE2(si, x,   y+1);
		//            SAMPLE2(sk, x-1, y+2);

		line1 = in + ((y - 2) * width + (x - 1)) * 4;
		line2 = in + ((y - 1) * width + (x - 2)) * 4;
		line3 = in + ((y    ) * width + (x - 1)) * 4;
		line4 = in + ((y + 1) * width + (x - 2)) * 4;
		line5 = in + ((y + 2) * width + (x - 1)) * 4;

		                 COPYSAMPLE(sa, line1); line1 += 8;
		COPYSAMPLE(sc, line2); line2 += 8; COPYSAMPLE(sd, line2); line2 += 8;
		                 COPYSAMPLE(sf, line3); line3 += 8;
		COPYSAMPLE(sh, line4); line4 += 8; COPYSAMPLE(si, line4); line4 += 8;
                         COPYSAMPLE(sk, line5); line5 += 8;

		outbyte = &out[(y * width + x) << 2];

		//for ( ; x < width; x+=2)
		for ( ; x < width - 3; x+=2)
		{
			//            SAMPLE2(sa, x-1, y-2); SAMPLE2(sb, x+1, y-2);
			//SAMPLE2(sc, x-2, y-1); SAMPLE2(sd, x,   y-1); SAMPLE2(se, x+2, y-1);
			//            SAMPLE2(sf, x-1, y  ); SAMPLE2(sg, x+1, y  );
			//SAMPLE2(sh, x-2, y+1); SAMPLE2(si, x,   y+1); SAMPLE2(sj, x+2, y+1);
			//            SAMPLE2(sk, x-1, y+2); SAMPLE2(sl, x+1, y+2);

			// optimization one
			//SAMPLE2(sb, x+1, y-2);
			//SAMPLE2(se, x+2, y-1);
			//SAMPLE2(sg, x+1, y  );
			//SAMPLE2(sj, x+2, y+1);
			//SAMPLE2(sl, x+1, y+2);

			COPYSAMPLE(sb, line1); line1 += 8;
			COPYSAMPLE(se, line2); line2 += 8;
			COPYSAMPLE(sg, line3); line3 += 8;
			COPYSAMPLE(sj, line4); line4 += 8;
			COPYSAMPLE(sl, line5); line5 += 8;

			for (i = 0; i < 4; i++)
			{
				int hd, vd, hp, vp;
				
				hp = sf[i] + sg[i]; 
				vp = sd[i] + si[i];
				hd = abs(sf[i] - sg[i]);
				vd = abs(sd[i] - si[i]);

				if (hd > 100 || vd > 100 || abs(hp-vp) > 200)
				{
					if (hd < vd)
						*outbyte = hp >> 1;
					else
						*outbyte = vp >> 1;
				}
				else
				{
					int hdd, vdd;

					//hdd = abs(sc[i] + sd[i] + se[i] - 3 * (sf[i] + sg[i]) + sh[i] + si[i] + sj[i]);
					//vdd = abs(sa[i] + sf[i] + sk[i] - 3 * (sd[i] + si[i]) + sb[i] + sg[i] + sl[i]);

					hdd = abs(sc[i] + se[i] - 3 * hp + sh[i] + sj[i] + vp);
					vdd = abs(sa[i] + sk[i] - 3 * vp + sb[i] + sl[i] + hp);

					if (hdd > vdd)
						*outbyte = hp >> 1;
					else 
						*outbyte = vp >> 1;
				}

				outbyte++;
			}

			outbyte += 4;

			          COPYSAMPLE(sa, sb);
			COPYSAMPLE(sc, sd); COPYSAMPLE(sd, se);
			          COPYSAMPLE(sf, sg);
			COPYSAMPLE(sh, si); COPYSAMPLE(si, sj);
			          COPYSAMPLE(sk, sl);
		}
	}
}

// Similar to FCBI, but throws out the second order derivatives for speed
static void DoFCBIQuick(byte *in, byte *out, int width, int height)
{
	int x, y, i;
	byte *outbyte, *inbyte;

	//copy in to out
	for (y = 0; y < height; y+=2)
	{
		inbyte = in + y * width * 4;
		outbyte = out + y * width * 4;

		for (x = width / 2; x > 0; x--)
		{
			COPYSAMPLE(outbyte, inbyte);
			outbyte += 8;
			inbyte += 8;
		}
	}

	for (y = 3; y < height - 4; y += 2)
	{
		byte sd[4], se[4], sh[4], si[4];
		byte *line2, *line3;

		x = 3;

		line2 = in + ((y - 1) * width + (x - 1)) * 4;
		line3 = in + ((y + 1) * width + (x - 1)) * 4;

		COPYSAMPLE(sd, line2); line2 += 8;
		COPYSAMPLE(sh, line3); line3 += 8;

	   outbyte = &out[(y * width + x) << 2];

		//for ( ; x < width; x += 2)
		for ( ; x < width - 4; x += 2)
		{
			COPYSAMPLE(se, line2); line2 += 8;
			COPYSAMPLE(si, line3); line3 += 8;

			for (i = 0; i < 4; i++)
			{	
				int NWd, NEd, NWp, NEp;

				NWp = sd[i] + si[i];
				NEp = se[i] + sh[i];
				NWd = abs(sd[i] - si[i]);
				NEd = abs(se[i] - sh[i]);

				if (NWd < NEd)
					*outbyte = NWp >> 1;
				else
					*outbyte = NEp >> 1;

				outbyte++;
			}

			outbyte += 4;

			COPYSAMPLE(sd, se);
			COPYSAMPLE(sh, si);
		}
	}

	// hack: copy out to in again
	for (y = 1; y < height; y+=2)
	{
		inbyte = out + y * width * 4 + 4;
		outbyte = in + y * width * 4 + 4;

		for (x = width / 2; x > 0; x--)
		{
			COPYSAMPLE(outbyte, inbyte);
			outbyte += 8;
			inbyte += 8;
		}
	}
	
	for (y = 2; y < height - 3; y++)
	{

		byte sd[4], sf[4], sg[4], si[4];
		byte *line2, *line3, *line4;

		x = (y + 1) % 2 + 2;

		line2 = in + ((y - 1) * width + (x    )) * 4;
		line3 = in + ((y    ) * width + (x - 1)) * 4;
		line4 = in + ((y + 1) * width + (x    )) * 4;

		outbyte = &out[(y * width + x) << 2];

		COPYSAMPLE(sf, line3); line3 += 8;

		for ( ; x < width - 3; x+=2)
		{
			COPYSAMPLE(sd, line2); line2 += 8;
			COPYSAMPLE(sg, line3); line3 += 8;
			COPYSAMPLE(si, line4); line4 += 8;

			for (i = 0; i < 4; i++)
			{
				int hd, vd, hp, vp;
				
				hp = sf[i] + sg[i]; 
				vp = sd[i] + si[i];
				hd = abs(sf[i] - sg[i]);
				vd = abs(sd[i] - si[i]);

				if (hd < vd)
					*outbyte = hp >> 1;
				else
					*outbyte = vp >> 1;

				outbyte++;
			}

			outbyte += 4;

			COPYSAMPLE(sf, sg);
		}
	}
}


static void ExpandHalfTextureToGrid( byte *data, int width, int height)
{
	int x, y;

	for (y = height / 2; y > 0; y--)
	{
		byte *outbyte = &data[((y * 2 - 1) * (width) - 2) * 4];
		byte *inbyte = &data[(y * (width / 2) - 1) * 4];

		for (x = width / 2; x > 0; x--)
		{
			outbyte[0] = inbyte[0];
			outbyte[1] = inbyte[1];
			outbyte[2] = inbyte[2];
			outbyte[3] = inbyte[3];

			outbyte -= 8;
			inbyte -= 4;
		}
	}
}

// size must be even
#define WORKBLOCK_SIZE     128
#define WORKBLOCK_BORDER   4
#define WORKBLOCK_REALSIZE (WORKBLOCK_SIZE + WORKBLOCK_BORDER * 2)

// assumes that data has already been expanded into a 2x2 grid
static void FCBIByBlock(byte *data, int width, int height, qboolean clampToEdge)
{
	byte workdata[WORKBLOCK_REALSIZE * WORKBLOCK_REALSIZE * 4];
	byte outdata[WORKBLOCK_REALSIZE * WORKBLOCK_REALSIZE * 4];
	byte *inbyte, *outbyte;
	int x, y, i;
	int srcx, srcy, dstx, dsty;

	for (y = 0; y < height; y += WORKBLOCK_SIZE)
	{
		for (x = 0; x < width; x += WORKBLOCK_SIZE)
		{
			int x2, y2;
			int workwidth, workheight, fullworkwidth, fullworkheight;

			workwidth =  MIN(WORKBLOCK_SIZE, width  - x);
			workheight = MIN(WORKBLOCK_SIZE, height - y);

			fullworkwidth =  workwidth  + WORKBLOCK_BORDER * 2;
			fullworkheight = workheight + WORKBLOCK_BORDER * 2;

			//memset(workdata, 0, WORKBLOCK_REALSIZE * WORKBLOCK_REALSIZE * 4);

			// fill in work block
			for (y2 = 0; y2 < fullworkheight; y2 += 2)
			{
				for (x2 = 0; x2 < fullworkwidth; x2 += 2)
				{
					srcx = x + x2 - WORKBLOCK_BORDER;
					srcy = y + y2 - WORKBLOCK_BORDER;
					dstx = x2;
					dsty = y2;

					if (clampToEdge)
					{
						srcx = CLAMP(srcx, 0, width - 2);
						srcy = CLAMP(srcy, 0, height - 2);
					}
					else
					{
						srcx = srcx % width;
						srcy = srcy % height;
					}

					for (i = 0; i < 4; i++)
					{
						workdata[(dsty * fullworkwidth + dstx) * 4 + i] = data[(srcy * width + srcx) * 4 + i];
					}
				}
			}

			// submit work block
			if (r_imageUpsampleType->integer == 1)
				DoFCBIQuick(workdata, outdata, fullworkwidth, fullworkheight);
			else
				DoFCBI(workdata, outdata, fullworkwidth, fullworkheight);

			// copy back work block
			for (y2 = 0; y2 < workheight; y2++)
			{
				inbyte = &outdata[((y2 + WORKBLOCK_BORDER) * fullworkwidth + WORKBLOCK_BORDER) * 4];
				outbyte = &data[((y + y2) * width + x) * 4];
				for (x2 = 0; x2 < workwidth; x2++)
				{
					COPYSAMPLE(outbyte, inbyte);
					outbyte += 4;
					inbyte += 4;
				}
			}
		}
	}
}
#undef COPYSAMPLE

/*
================
R_LightScaleTexture

Scale up the pixel values in a texture to increase the
lighting range
================
*/
void R_LightScaleTexture (byte *in, int inwidth, int inheight, qboolean only_gamma )
{
	if ( only_gamma )
	{
		if ( !glConfig.deviceSupportsGamma )
		{
			int		i, c;
			byte	*p;

			p = in;

			c = inwidth*inheight;
			for (i=0 ; i<c ; i++, p+=4)
			{
				p[0] = s_gammatable[p[0]];
				p[1] = s_gammatable[p[1]];
				p[2] = s_gammatable[p[2]];
			}
		}
	}
	else
	{
		int		i, c;
		byte	*p;

		p = in;

		c = inwidth*inheight;

		if ( glConfig.deviceSupportsGamma )
		{
			for (i=0 ; i<c ; i++, p+=4)
			{
				p[0] = s_intensitytable[p[0]];
				p[1] = s_intensitytable[p[1]];
				p[2] = s_intensitytable[p[2]];
			}
		}
		else
		{
			for (i=0 ; i<c ; i++, p+=4)
			{
				p[0] = s_gammatable[s_intensitytable[p[0]]];
				p[1] = s_gammatable[s_intensitytable[p[1]]];
				p[2] = s_gammatable[s_intensitytable[p[2]]];
			}
		}
	}
}


/*
================
R_MipMap2

Operates in place, quartering the size of the texture
Proper linear filter
================
*/
static void R_MipMap2( byte *in, int inWidth, int inHeight ) {
	int			i, j, k;
	byte		*outpix;
	int			inWidthMask, inHeightMask;
	int			total;
	int			outWidth, outHeight;
	unsigned	*temp;

	outWidth = inWidth >> 1;
	outHeight = inHeight >> 1;
	temp = ri.Hunk_AllocateTempMemory( outWidth * outHeight * 4 );

	inWidthMask = inWidth - 1;
	inHeightMask = inHeight - 1;

	for ( i = 0 ; i < outHeight ; i++ ) {
		for ( j = 0 ; j < outWidth ; j++ ) {
			outpix = (byte *) ( temp + i * outWidth + j );
			for ( k = 0 ; k < 4 ; k++ ) {
				total = 
					1 * (&in[ 4*(((i*2-1)&inHeightMask)*inWidth + ((j*2-1)&inWidthMask)) ])[k] +
					2 * (&in[ 4*(((i*2-1)&inHeightMask)*inWidth + ((j*2  )&inWidthMask)) ])[k] +
					2 * (&in[ 4*(((i*2-1)&inHeightMask)*inWidth + ((j*2+1)&inWidthMask)) ])[k] +
					1 * (&in[ 4*(((i*2-1)&inHeightMask)*inWidth + ((j*2+2)&inWidthMask)) ])[k] +

					2 * (&in[ 4*(((i*2  )&inHeightMask)*inWidth + ((j*2-1)&inWidthMask)) ])[k] +
					4 * (&in[ 4*(((i*2  )&inHeightMask)*inWidth + ((j*2  )&inWidthMask)) ])[k] +
					4 * (&in[ 4*(((i*2  )&inHeightMask)*inWidth + ((j*2+1)&inWidthMask)) ])[k] +
					2 * (&in[ 4*(((i*2  )&inHeightMask)*inWidth + ((j*2+2)&inWidthMask)) ])[k] +

					2 * (&in[ 4*(((i*2+1)&inHeightMask)*inWidth + ((j*2-1)&inWidthMask)) ])[k] +
					4 * (&in[ 4*(((i*2+1)&inHeightMask)*inWidth + ((j*2  )&inWidthMask)) ])[k] +
					4 * (&in[ 4*(((i*2+1)&inHeightMask)*inWidth + ((j*2+1)&inWidthMask)) ])[k] +
					2 * (&in[ 4*(((i*2+1)&inHeightMask)*inWidth + ((j*2+2)&inWidthMask)) ])[k] +

					1 * (&in[ 4*(((i*2+2)&inHeightMask)*inWidth + ((j*2-1)&inWidthMask)) ])[k] +
					2 * (&in[ 4*(((i*2+2)&inHeightMask)*inWidth + ((j*2  )&inWidthMask)) ])[k] +
					2 * (&in[ 4*(((i*2+2)&inHeightMask)*inWidth + ((j*2+1)&inWidthMask)) ])[k] +
					1 * (&in[ 4*(((i*2+2)&inHeightMask)*inWidth + ((j*2+2)&inWidthMask)) ])[k];
				outpix[k] = total / 36;
			}
		}
	}

	Com_Memcpy( in, temp, outWidth * outHeight * 4 );
	ri.Hunk_FreeTempMemory( temp );
}

/*
================
R_MipMap

Operates in place, quartering the size of the texture
================
*/
static void R_MipMap (byte *in, int width, int height) {
	int		i, j;
	byte	*out;
	int		row;

	if ( !r_simpleMipMaps->integer ) {
		R_MipMap2( in, width, height );
		return;
	}

	if ( width == 1 && height == 1 ) {
		return;
	}

	row = width * 4;
	out = in;
	width >>= 1;
	height >>= 1;

	if ( width == 0 || height == 0 ) {
		width += height;	// get largest
		for (i=0 ; i<width ; i++, out+=4, in+=8 ) {
			out[0] = ( in[0] + in[4] )>>1;
			out[1] = ( in[1] + in[5] )>>1;
			out[2] = ( in[2] + in[6] )>>1;
			out[3] = ( in[3] + in[7] )>>1;
		}
		return;
	}

	for (i=0 ; i<height ; i++, in+=row) {
		for (j=0 ; j<width ; j++, out+=4, in+=8) {
			out[0] = (in[0] + in[4] + in[row+0] + in[row+4])>>2;
			out[1] = (in[1] + in[5] + in[row+1] + in[row+5])>>2;
			out[2] = (in[2] + in[6] + in[row+2] + in[row+6])>>2;
			out[3] = (in[3] + in[7] + in[row+3] + in[row+7])>>2;
		}
	}
}


static void R_MipMapNormalHeight (byte *in, int width, int height, qboolean swizzle) {
	int		i, j;
	byte	*out;
	int		row;
	int sx = swizzle ? 3 : 0;
	int sa = swizzle ? 0 : 3;

	if ( width == 1 && height == 1 ) {
		return;
	}

	row = width * 4;
	out = in;
	width >>= 1;
	height >>= 1;

	if ( width == 0 || height == 0 ) {
		width += height;	// get largest
		for (i=0 ; i<width ; i++, out+=4, in+=8 ) {
			vec3_t v;

			v[0] =  OffsetByteToFloat(in[sx  ]);
			v[1] =  OffsetByteToFloat(in[1   ]);
			v[2] =  OffsetByteToFloat(in[2   ]);

			v[0] += OffsetByteToFloat(in[sx+4]);
			v[1] += OffsetByteToFloat(in[   5]);
			v[2] += OffsetByteToFloat(in[   6]);

			VectorNormalizeFast(v);

			out[sx] = FloatToOffsetByte(v[0]);
			out[1 ] = FloatToOffsetByte(v[1]);
			out[2 ] = FloatToOffsetByte(v[2]);
			out[sa] = MAX(in[sa], in[sa+4]);
		}
		return;
	}

	for (i=0 ; i<height ; i++, in+=row) {
		for (j=0 ; j<width ; j++, out+=4, in+=8) {
			vec3_t v;

			v[0] =  OffsetByteToFloat(in[sx      ]);
			v[1] =  OffsetByteToFloat(in[       1]);
			v[2] =  OffsetByteToFloat(in[       2]);

			v[0] += OffsetByteToFloat(in[sx    +4]);
			v[1] += OffsetByteToFloat(in[       5]);
			v[2] += OffsetByteToFloat(in[       6]);

			v[0] += OffsetByteToFloat(in[sx+row  ]);
			v[1] += OffsetByteToFloat(in[   row+1]);
			v[2] += OffsetByteToFloat(in[   row+2]);

			v[0] += OffsetByteToFloat(in[sx+row+4]);
			v[1] += OffsetByteToFloat(in[   row+5]);
			v[2] += OffsetByteToFloat(in[   row+6]);

			VectorNormalizeFast(v);

			out[sx] = FloatToOffsetByte(v[0]);
			out[1 ] = FloatToOffsetByte(v[1]);
			out[2 ] = FloatToOffsetByte(v[2]);
			out[sa] = MAX(MAX(in[sa], in[sa+4]), MAX(in[sa+row], in[sa+row+4]));
		}
	}
}


/*
==================
R_BlendOverTexture

Apply a color blend over a set of pixels
==================
*/
static void R_BlendOverTexture( byte *data, int pixelCount, byte blend[4] ) {
	int		i;
	int		inverseAlpha;
	int		premult[3];

	inverseAlpha = 255 - blend[3];
	premult[0] = blend[0] * blend[3];
	premult[1] = blend[1] * blend[3];
	premult[2] = blend[2] * blend[3];

	for ( i = 0 ; i < pixelCount ; i++, data+=4 ) {
		data[0] = ( data[0] * inverseAlpha + premult[0] ) >> 9;
		data[1] = ( data[1] * inverseAlpha + premult[1] ) >> 9;
		data[2] = ( data[2] * inverseAlpha + premult[2] ) >> 9;
	}
}

byte	mipBlendColors[16][4] = {
	{0,0,0,0},
	{255,0,0,128},
	{0,255,0,128},
	{0,0,255,128},
	{255,0,0,128},
	{0,255,0,128},
	{0,0,255,128},
	{255,0,0,128},
	{0,255,0,128},
	{0,0,255,128},
	{255,0,0,128},
	{0,255,0,128},
	{0,0,255,128},
	{255,0,0,128},
	{0,255,0,128},
	{0,0,255,128},
};

static void RawImage_SwizzleRA( byte *data, int width, int height )
{
	int i;
	byte *ptr = data, swap;

	for (i=0; i<width*height; i++, ptr+=4)
	{
		// swap red and alpha
		swap = ptr[0];
		ptr[0] = ptr[3];
		ptr[3] = swap;
	}
}

#if 0
static void RawImage_Normalize( byte *data, int width, int height, qboolean swizzle )
{
	int i;
	byte *ptr = data;
	int s = swizzle ? 3 : 0;

	for (i=0; i<width*height; i++, ptr+=4)
	{
		vec3_t v;

		v[0] = (float)ptr[s] * 1.0f/127.5f - 1.0f;
		v[1] = (float)ptr[1] * 1.0f/127.5f - 1.0f;
		v[2] = (float)ptr[2] * 1.0f/127.5f - 1.0f;

		VectorNormalizeFast(v);

		ptr[s] = (byte)(v[0] * 127.5f + 127.5f);
		ptr[1] = (byte)(v[1] * 127.5f + 127.5f);
		ptr[2] = (byte)(v[2] * 127.5f + 127.5f);
	}
}
#endif

/*
===============
RawImage_ScaleToPower2

===============
*/
static void RawImage_ScaleToPower2( byte **data, int *inout_width, int *inout_height, int *inout_scaled_width, int *inout_scaled_height, imgFlags_t flags, byte **resampledBuffer)
{
	int width =         *inout_width;
	int height =        *inout_height;
	int scaled_width =  *inout_scaled_width;
	int scaled_height = *inout_scaled_height;
	qboolean picmip = flags & IMGFLAG_PICMIP;
	qboolean mipmap = flags & IMGFLAG_MIPMAP;
	qboolean clampToEdge = flags & IMGFLAG_CLAMPTOEDGE;

	//
	// convert to exact power of 2 sizes
	//
	if (glRefConfig.textureNonPowerOfTwo && !mipmap)
	{
		scaled_width = width;
		scaled_height = height;
	}
	else
	{
		scaled_width = NextPowerOfTwo(width);
		scaled_height = NextPowerOfTwo(height);
	}

	if ( r_roundImagesDown->integer && scaled_width > width )
		scaled_width >>= 1;
	if ( r_roundImagesDown->integer && scaled_height > height )
		scaled_height >>= 1;

	if ( picmip && data && resampledBuffer && r_imageUpsample->integer && 
	     scaled_width < r_imageUpsampleMaxSize->integer && scaled_height < r_imageUpsampleMaxSize->integer)
	{
		int finalwidth, finalheight;
		//int startTime, endTime;

		//startTime = ri.Milliseconds();

		finalwidth = scaled_width << r_imageUpsample->integer;
		finalheight = scaled_height << r_imageUpsample->integer;

		while ( finalwidth > r_imageUpsampleMaxSize->integer
			|| finalheight > r_imageUpsampleMaxSize->integer ) {
			finalwidth >>= 1;
			finalheight >>= 1;
		}

		while ( finalwidth > glConfig.maxTextureSize
			|| finalheight > glConfig.maxTextureSize ) {
			finalwidth >>= 1;
			finalheight >>= 1;
		}

		*resampledBuffer = ri.Hunk_AllocateTempMemory( finalwidth * finalheight * 4 );

		if (scaled_width != width || scaled_height != height)
		{
			ResampleTexture (*data, width, height, *resampledBuffer, scaled_width, scaled_height);
		}
		else
		{
			byte *inbyte, *outbyte;
			int i;

			inbyte = *data;
			outbyte = *resampledBuffer;

			for (i = width * height * 4; i > 0; i--)
			{
				*outbyte++ = *inbyte++;
			}
		}

		while (scaled_width < finalwidth || scaled_height < finalheight)
		{
			scaled_width <<= 1;
			scaled_height <<= 1;

			ExpandHalfTextureToGrid(*resampledBuffer, scaled_width, scaled_height);
			/*DoFCBI(*resampledBuffer, scaled_width, scaled_height);*/
			FCBIByBlock(*resampledBuffer, scaled_width, scaled_height, clampToEdge);
		}

		//endTime = ri.Milliseconds();

		//ri.Printf(PRINT_ALL, "upsampled %dx%d to %dx%d in %dms\n", width, height, scaled_width, scaled_height, endTime - startTime);

		*data = *resampledBuffer;
		width = scaled_width;
		height = scaled_height;
	}
	else if ( scaled_width != width || scaled_height != height ) {
		if (data && resampledBuffer)
		{
			*resampledBuffer = ri.Hunk_AllocateTempMemory( scaled_width * scaled_height * 4 );
			ResampleTexture (*data, width, height, *resampledBuffer, scaled_width, scaled_height);
			*data = *resampledBuffer;
		}
		width = scaled_width;
		height = scaled_height;
	}

	//
	// perform optional picmip operation
	//
	if ( picmip ) {
		scaled_width >>= r_picmip->integer;
		scaled_height >>= r_picmip->integer;
	}

	//
	// clamp to minimum size
	//
	if (scaled_width < 1) {
		scaled_width = 1;
	}
	if (scaled_height < 1) {
		scaled_height = 1;
	}

	//
	// clamp to the current upper OpenGL limit
	// scale both axis down equally so we don't have to
	// deal with a half mip resampling
	//
	while ( scaled_width > glConfig.maxTextureSize
		|| scaled_height > glConfig.maxTextureSize ) {
		scaled_width >>= 1;
		scaled_height >>= 1;
	}

	*inout_width         = width;
	*inout_height        = height;
	*inout_scaled_width  = scaled_width;
	*inout_scaled_height = scaled_height;
}


static qboolean RawImage_HasAlpha(const byte *scan, int numPixels)
{
	int i;

	if (!scan)
		return qtrue;

	for ( i = 0; i < numPixels; i++ )
	{
		if ( scan[i*4 + 3] != 255 ) 
		{
			return qtrue;
		}
	}

	return qfalse;
}

static GLenum RawImage_GetFormat(const byte *data, int numPixels, qboolean lightMap, imgFlags_t flags)
{
	int samples = 3;
	GLenum internalFormat = GL_RGB;
	qboolean forceNoCompression = (flags & IMGFLAG_NO_COMPRESSION);
	qboolean normalmap4 = (flags & IMGFLAG_SWIZZLE) && (flags & IMGFLAG_NORMALIZED);

	if(lightMap)
	{
		samples = 4;
		if(r_greyscale->integer)
			internalFormat = GL_LUMINANCE;
		else
			internalFormat = GL_RGBA;
	}
	else
	{
		if (normalmap4 || RawImage_HasAlpha(data, numPixels))
		{
			samples = 4;
		}

		// select proper internal format
		if ( samples == 3 )
		{
			if(r_greyscale->integer)
			{
				if(r_texturebits->integer == 16)
					internalFormat = GL_LUMINANCE8;
				else if(r_texturebits->integer == 32)
					internalFormat = GL_LUMINANCE16;
				else
					internalFormat = GL_LUMINANCE;
			}
			else
			{
				if ( !forceNoCompression && glConfig.textureCompression == TC_S3TC_ARB )
				{
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				}
				else if ( !forceNoCompression && glConfig.textureCompression == TC_S3TC )
				{
					internalFormat = GL_RGB4_S3TC;
				}
				else if ( r_texturebits->integer == 16 )
				{
					internalFormat = GL_RGB5;
				}
				else if ( r_texturebits->integer == 32 )
				{
					internalFormat = GL_RGB8;
				}
				else
				{
					internalFormat = GL_RGB;
				}
			}
		}
		else if ( samples == 4 )
		{
			if(r_greyscale->integer)
			{
				if(r_texturebits->integer == 16)
					internalFormat = GL_LUMINANCE8_ALPHA8;
				else if(r_texturebits->integer == 32)
					internalFormat = GL_LUMINANCE16_ALPHA16;
				else
					internalFormat = GL_LUMINANCE_ALPHA;
			}
			else
			{
				if ( !forceNoCompression && glConfig.textureCompression == TC_S3TC_ARB )
				{
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				}
				else if ( r_texturebits->integer == 16 )
				{
					internalFormat = GL_RGBA4;
				}
				else if ( r_texturebits->integer == 32 )
				{
					internalFormat = GL_RGBA8;
				}
				else
				{
					internalFormat = GL_RGBA;
				}
			}
		}
	}

	return internalFormat;
}


static void RawImage_UploadTexture( byte *data, int x, int y, int width, int height, GLenum internalFormat, imgFlags_t flags, qboolean subtexture )
{
	int dataFormat, dataType;

	switch(internalFormat)
	{
		case GL_DEPTH_COMPONENT:
		case GL_DEPTH_COMPONENT16_ARB:
		case GL_DEPTH_COMPONENT24_ARB:
		case GL_DEPTH_COMPONENT32_ARB:
			dataFormat = GL_DEPTH_COMPONENT;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GL_RGBA16F_ARB:
			dataFormat = GL_RGBA;
			dataType = GL_HALF_FLOAT_ARB;
			break;
		default:
			dataFormat = GL_RGBA;
			dataType = GL_UNSIGNED_BYTE;
			break;
	}

	if ( subtexture )
		qglTexSubImage2D( GL_TEXTURE_2D, 0, x, y, width, height, dataFormat, dataType, data );
	else
		qglTexImage2D (GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, dataType, data );

	if (flags & IMGFLAG_MIPMAP)
	{
		int miplevel;

		miplevel = 0;
		while (width > 1 || height > 1)
		{
			if (data)
			{
				if (flags & IMGFLAG_NORMALIZED)
				{
					R_MipMapNormalHeight( data, width, height, flags & IMGFLAG_SWIZZLE );
				}
				else
				{
					R_MipMap( data, width, height );
				}
			}
			
			width >>= 1;
			height >>= 1;
			if (width < 1)
				width = 1;
			if (height < 1)
				height = 1;
			miplevel++;

			if ( data && r_colorMipLevels->integer )
				R_BlendOverTexture( (byte *)data, width * height, mipBlendColors[miplevel] );

			if ( subtexture )
			{
				x >>= 1;
				y >>= 1;
				qglTexSubImage2D( GL_TEXTURE_2D, miplevel, x, y, width, height, dataFormat, dataType, data );
			}
			else
			{
				qglTexImage2D (GL_TEXTURE_2D, miplevel, internalFormat, width, height, 0, dataFormat, dataType, data );
			}
		}
	}
}


/*
===============
Upload32

===============
*/
extern qboolean charSet;
static void Upload32( byte *data, int width, int height, imgFlags_t flags,
	qboolean lightMap, int *format, int *pUploadWidth, int *pUploadHeight)
{
	byte		*scaledBuffer = NULL;
	byte		*resampledBuffer = NULL;
	int			scaled_width, scaled_height;
	int			i, c;
	byte		*scan;
	GLenum		internalFormat = *format;

	RawImage_ScaleToPower2(&data, &width, &height, &scaled_width, &scaled_height, flags, &resampledBuffer);

	scaledBuffer = ri.Hunk_AllocateTempMemory( sizeof( unsigned ) * scaled_width * scaled_height );

	//
	// scan the texture for each channel's max values
	// and verify if the alpha channel is being used or not
	//
	c = width*height;
	scan = data;
	
	if( r_greyscale->integer )
	{
		for ( i = 0; i < c; i++ )
		{
			byte luma = LUMA(scan[i*4], scan[i*4 + 1], scan[i*4 + 2]);
			scan[i*4] = luma;
			scan[i*4 + 1] = luma;
			scan[i*4 + 2] = luma;
		}
	}
	else if( r_greyscale->value )
	{
		for ( i = 0; i < c; i++ )
		{
			float luma = LUMA(scan[i*4], scan[i*4 + 1], scan[i*4 + 2]);
			scan[i*4] = LERP(scan[i*4], luma, r_greyscale->value);
			scan[i*4 + 1] = LERP(scan[i*4 + 1], luma, r_greyscale->value);
			scan[i*4 + 2] = LERP(scan[i*4 + 2], luma, r_greyscale->value);
		}
	}

	if (!internalFormat)
		internalFormat = RawImage_GetFormat(scan, c, lightMap, flags);

	if (flags & IMGFLAG_SWIZZLE)
	{
		RawImage_SwizzleRA(data, width, height);
	}

	// copy or resample data as appropriate for first MIP level
	if ( ( scaled_width == width ) && 
		( scaled_height == height ) ) {
		if (!(flags & IMGFLAG_MIPMAP))
		{
			RawImage_UploadTexture( data, 0, 0, scaled_width, scaled_height, internalFormat, flags, qfalse );
			//qglTexImage2D (GL_TEXTURE_2D, 0, internalFormat, scaled_width, scaled_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			*pUploadWidth = scaled_width;
			*pUploadHeight = scaled_height;
			*format = internalFormat;

			goto done;
		}
		Com_Memcpy (scaledBuffer, data, width*height*4);
	}
	else
	{
		// use the normal mip-mapping function to go down from here
		while ( width > scaled_width || height > scaled_height ) {
			R_MipMap( (byte *)data, width, height );
			width >>= 1;
			height >>= 1;
			if ( width < 1 ) {
				width = 1;
			}
			if ( height < 1 ) {
				height = 1;
			}
		}
		Com_Memcpy( scaledBuffer, data, width * height * 4 );
	}

	if (!(flags & IMGFLAG_NOLIGHTSCALE))
		R_LightScaleTexture (scaledBuffer, scaled_width, scaled_height, !(flags & IMGFLAG_MIPMAP) );

	*pUploadWidth = scaled_width;
	*pUploadHeight = scaled_height;
	*format = internalFormat;

	RawImage_UploadTexture(scaledBuffer, 0, 0, scaled_width, scaled_height, internalFormat, flags, qfalse);

done:

	if (flags & IMGFLAG_MIPMAP)
	{
		if ( textureFilterAnisotropic )
			qglTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
					(GLint)Com_Clamp( 1, maxAnisotropy, r_ext_max_anisotropy->integer ) );

		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter_min);
		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter_max);
	}
	else
	{
		if ( textureFilterAnisotropic )
			qglTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1 );

		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	GL_CheckErrors();

	if ( scaledBuffer != 0 )
		ri.Hunk_FreeTempMemory( scaledBuffer );
	if ( resampledBuffer != 0 )
		ri.Hunk_FreeTempMemory( resampledBuffer );
}


static void EmptyTexture( int width, int height, imgFlags_t flags,
	qboolean lightMap, int *format, int *pUploadWidth, int *pUploadHeight )
{
	int			scaled_width, scaled_height;
	GLenum		internalFormat = *format;

	RawImage_ScaleToPower2(NULL, &width, &height, &scaled_width, &scaled_height, flags, NULL);

	if (!internalFormat)
		internalFormat = RawImage_GetFormat(NULL, 0, lightMap, flags);

	*pUploadWidth = scaled_width;
	*pUploadHeight = scaled_height;
	*format = internalFormat;

	RawImage_UploadTexture(NULL, 0, 0, scaled_width, scaled_height, internalFormat, flags, qfalse);

	if (flags & IMGFLAG_MIPMAP)
	{
		if ( textureFilterAnisotropic )
			qglTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
					(GLint)Com_Clamp( 1, maxAnisotropy, r_ext_max_anisotropy->integer ) );

		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter_min);
		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter_max);
	}
	else
	{
		if ( textureFilterAnisotropic )
			qglTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1 );

		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	GL_CheckErrors();
}


/*
================
R_CreateImage

This is the only way any image_t are created
================
*/
image_t *R_CreateImage2( const char *name, byte *pic, int width, int height, imgFlags_t flags, int internalFormat ) {
	image_t		*image;
	qboolean	isLightmap = qfalse;
	long		hash;
	int         glWrapClampMode;

	if (strlen(name) >= MAX_QPATH ) {
		ri.Error (ERR_DROP, "R_CreateImage: \"%s\" is too long", name);
	}
	if ( !strncmp( name, "*lightmap", 9 ) ) {
		isLightmap = qtrue;
	}

	if ( tr.numImages == MAX_DRAWIMAGES ) {
		ri.Error( ERR_DROP, "R_CreateImage: MAX_DRAWIMAGES hit");
	}

	image = tr.images[tr.numImages] = ri.Hunk_Alloc( sizeof( image_t ), h_low );
	image->texnum = 1024 + tr.numImages;
	tr.numImages++;

	image->flags = flags;

	strcpy (image->imgName, name);

	image->width = width;
	image->height = height;
	if (flags & IMGFLAG_CLAMPTOEDGE)
		glWrapClampMode = GL_CLAMP_TO_EDGE;
	else
		glWrapClampMode = GL_REPEAT;
	image->wrapClampMode = glWrapClampMode;
	image->internalFormat = internalFormat;

	// lightmaps are always allocated on TMU 1
	if ( qglActiveTextureARB && isLightmap ) {
		image->TMU = 1;
	} else {
		image->TMU = 0;
	}

	if ( qglActiveTextureARB ) {
		GL_SelectTexture( image->TMU );
	}

	if (image->flags & IMGFLAG_CUBEMAP)
	{
		GL_BindCubemap(image);
		qglTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		qglTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		qglTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		qglTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		qglTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		qglTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pic);
		qglTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pic);
		qglTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pic);
		qglTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pic);
		qglTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pic);
		qglTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pic);


		if (!internalFormat)
			image->internalFormat = GL_RGBA8;
		image->uploadWidth = width;
		image->uploadHeight = height;
	}
	else
	{
		GL_Bind(image);

		if (pic)
		{
			Upload32( pic, image->width, image->height, image->flags,
				isLightmap, &image->internalFormat, &image->uploadWidth,
				&image->uploadHeight );
		}
		else
		{
			EmptyTexture(image->width, image->height, image->flags,
				isLightmap, &image->internalFormat, &image->uploadWidth,
				&image->uploadHeight );
		}

		qglTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapClampMode );
		qglTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapClampMode );
	}

	GL_SelectTexture( 0 );

	hash = generateHashValue(name);
	image->next = hashTable[hash];
	hashTable[hash] = image;

	return image;
}

image_t *R_CreateImage( const char *name, byte *pic, int width, int height, 
					   qboolean mipmap, qboolean allowPicmip, int glWrapClampMode )
{
	imgFlags_t flags = IMGFLAG_NONE;

	if (mipmap)
		flags |= IMGFLAG_MIPMAP;

	if (allowPicmip)
		flags |= IMGFLAG_PICMIP;

	if (glWrapClampMode == GL_CLAMP_TO_EDGE)
		flags |= IMGFLAG_CLAMPTOEDGE;

	return R_CreateImage2( name, pic, width, height, flags, 0 );
}

image_t *R_CreateCubeImage( const char *name, byte *pic, int width, int height, 
					   qboolean mipmap, qboolean allowPicmip, int glWrapClampMode )
{
	imgFlags_t flags = IMGFLAG_CUBEMAP;

	if (mipmap)
		flags |= IMGFLAG_MIPMAP;

	if (allowPicmip)
		flags |= IMGFLAG_PICMIP;

	if (glWrapClampMode == GL_CLAMP_TO_EDGE)
		flags |= IMGFLAG_CLAMPTOEDGE;

	return R_CreateImage2( name, pic, width, height, flags, 0 );
}

void R_UpdateSubImage( image_t *image, byte *pic, int x, int y, int width, int height )
{
	byte *scaledBuffer = NULL;
	byte *resampledBuffer = NULL;
	int	 scaled_width, scaled_height, scaled_x, scaled_y;
	byte *data = pic;

	if (image->flags & IMGFLAG_SWIZZLE)
	{
		RawImage_SwizzleRA(pic, width, height);
	}

	RawImage_ScaleToPower2(&pic, &width, &height, &scaled_width, &scaled_height, image->flags, &resampledBuffer);

	scaledBuffer = ri.Hunk_AllocateTempMemory( sizeof( unsigned ) * scaled_width * scaled_height );

	if ( qglActiveTextureARB ) {
		GL_SelectTexture( image->TMU );
	}

	GL_Bind(image);	

	// copy or resample data as appropriate for first MIP level
	if ( ( scaled_width == width ) && 
		( scaled_height == height ) ) {
		if (!(image->flags & IMGFLAG_MIPMAP))
		{
			scaled_x = x * scaled_width / width;
			scaled_y = y * scaled_height / height;
			RawImage_UploadTexture( data, scaled_x, scaled_y, scaled_width, scaled_height, image->internalFormat, image->flags, qtrue );
			//qglTexSubImage2D( GL_TEXTURE_2D, 0, scaled_x, scaled_y, scaled_width, scaled_height, GL_RGBA, GL_UNSIGNED_BYTE, data );

			GL_CheckErrors();
			goto done;
		}
		Com_Memcpy (scaledBuffer, data, width*height*4);
	}
	else
	{
		// use the normal mip-mapping function to go down from here
		while ( width > scaled_width || height > scaled_height ) {
			R_MipMap( (byte *)data, width, height );
			width >>= 1;
			height >>= 1;
			x >>= 1;
			y >>= 1;
			if ( width < 1 ) {
				width = 1;
			}
			if ( height < 1 ) {
				height = 1;
			}
		}
		Com_Memcpy( scaledBuffer, data, width * height * 4 );
	}

	if (!(image->flags & IMGFLAG_NOLIGHTSCALE))
		R_LightScaleTexture (scaledBuffer, scaled_width, scaled_height, !(image->flags & IMGFLAG_MIPMAP) );

	scaled_x = x * scaled_width / width;
	scaled_y = y * scaled_height / height;
	RawImage_UploadTexture( (byte *)data, scaled_x, scaled_y, scaled_width, scaled_height, image->internalFormat, image->flags, qtrue );

done:
	
	GL_SelectTexture( 0 );

	GL_CheckErrors();

	if ( scaledBuffer != 0 )
		ri.Hunk_FreeTempMemory( scaledBuffer );
	if ( resampledBuffer != 0 )
		ri.Hunk_FreeTempMemory( resampledBuffer );
}

//===================================================================

typedef struct
{
	char *ext;
	void (*ImageLoader)( const char *, unsigned char **, int *, int * );
} imageExtToLoaderMap_t;

// Note that the ordering indicates the order of preference used
// when there are multiple images of different formats available
static imageExtToLoaderMap_t imageLoaders[ ] =
{
	{ "tga",  R_LoadTGA },
	{ "jpg",  R_LoadJPG },
	{ "jpeg", R_LoadJPG },
	{ "png",  R_LoadPNG },
	{ "pcx",  R_LoadPCX },
	{ "bmp",  R_LoadBMP }
};

static int numImageLoaders = ARRAY_LEN( imageLoaders );

/*
=================
R_LoadImage

Loads any of the supported image types into a cannonical
32 bit format.
=================
*/
void R_LoadImage( const char *name, byte **pic, int *width, int *height )
{
	qboolean orgNameFailed = qfalse;
	int orgLoader = -1;
	int i;
	char localName[ MAX_QPATH ];
	const char *ext;
	char *altName;

	*pic = NULL;
	*width = 0;
	*height = 0;

	Q_strncpyz( localName, name, MAX_QPATH );

	ext = COM_GetExtension( localName );

	if( *ext )
	{
		// Look for the correct loader and use it
		for( i = 0; i < numImageLoaders; i++ )
		{
			if( !Q_stricmp( ext, imageLoaders[ i ].ext ) )
			{
				// Load
				imageLoaders[ i ].ImageLoader( localName, pic, width, height );
				break;
			}
		}

		// A loader was found
		if( i < numImageLoaders )
		{
			if( *pic == NULL )
			{
				// Loader failed, most likely because the file isn't there;
				// try again without the extension
				orgNameFailed = qtrue;
				orgLoader = i;
				COM_StripExtension( name, localName, MAX_QPATH );
			}
			else
			{
				// Something loaded
				return;
			}
		}
	}

	// Try and find a suitable match using all
	// the image formats supported
	for( i = 0; i < numImageLoaders; i++ )
	{
		if (i == orgLoader)
			continue;

		altName = va( "%s.%s", localName, imageLoaders[ i ].ext );

		// Load
		imageLoaders[ i ].ImageLoader( altName, pic, width, height );

		if( *pic )
		{
			if( orgNameFailed )
			{
				ri.Printf( PRINT_DEVELOPER, "WARNING: %s not present, using %s instead\n",
						name, altName );
			}

			break;
		}
	}
}


/*
===============
R_FindImageFile

Finds or loads the given image.
Returns NULL if it fails, not a default image.
==============
*/
image_t	*R_FindImageFile2( const char *name, imgFlags_t flags )
{
	image_t	*image;
	int		width, height;
	byte	*pic;
	long	hash;

	if (!name) {
		return NULL;
	}

	hash = generateHashValue(name);

	//
	// see if the image is already loaded
	//
	for (image=hashTable[hash]; image; image=image->next) {
		if ( !strcmp( name, image->imgName ) ) {
			// the white image can be used with any set of parms, but other mismatches are errors
			if ( strcmp( name, "*white" ) ) {
				if ( image->flags != flags ) {
					ri.Printf( PRINT_DEVELOPER, "WARNING: reused image %s with mixed flags (%i vs %i)\n", name, image->flags, flags );
				}
			}
			return image;
		}
	}

	//
	// load the pic from disk
	//
	R_LoadImage( name, &pic, &width, &height );
	if ( pic == NULL ) {
		return NULL;
	}

	image = R_CreateImage2( ( char * ) name, pic, width, height, flags, 0 );
	ri.Free( pic );
	return image;
}


image_t	*R_FindImageFile( const char *name, qboolean mipmap, qboolean allowPicmip, int glWrapClampMode ) {
	imgFlags_t flags = IMGFLAG_NONE;

	flags = IMGFLAG_NONE;

	if (mipmap)
		flags |= IMGFLAG_MIPMAP;

	if (allowPicmip)
		flags |= IMGFLAG_PICMIP;

	if (glWrapClampMode == GL_CLAMP_TO_EDGE)
		flags |= IMGFLAG_CLAMPTOEDGE;

	return R_FindImageFile2( name, flags );
}


/*
================
R_CreateDlightImage
================
*/
#define	DLIGHT_SIZE	16
static void R_CreateDlightImage( void ) {
	int		x,y;
	byte	data[DLIGHT_SIZE][DLIGHT_SIZE][4];
	int		b;

	// make a centered inverse-square falloff blob for dynamic lighting
	for (x=0 ; x<DLIGHT_SIZE ; x++) {
		for (y=0 ; y<DLIGHT_SIZE ; y++) {
			float	d;

			d = ( DLIGHT_SIZE/2 - 0.5f - x ) * ( DLIGHT_SIZE/2 - 0.5f - x ) +
				( DLIGHT_SIZE/2 - 0.5f - y ) * ( DLIGHT_SIZE/2 - 0.5f - y );
			b = 4000 / d;
			if (b > 255) {
				b = 255;
			} else if ( b < 75 ) {
				b = 0;
			}
			data[y][x][0] = 
			data[y][x][1] = 
			data[y][x][2] = b;
			data[y][x][3] = 255;			
		}
	}
	tr.dlightImage = R_CreateImage("*dlight", (byte *)data, DLIGHT_SIZE, DLIGHT_SIZE, qfalse, qfalse, GL_CLAMP_TO_EDGE );
}


/*
=================
R_InitFogTable
=================
*/
void R_InitFogTable( void ) {
	int		i;
	float	d;
	float	exp;
	
	exp = 0.5;

	for ( i = 0 ; i < FOG_TABLE_SIZE ; i++ ) {
		d = pow ( (float)i/(FOG_TABLE_SIZE-1), exp );

		tr.fogTable[i] = d;
	}
}

/*
================
R_FogFactor

Returns a 0.0 to 1.0 fog density value
This is called for each texel of the fog texture on startup
and for each vertex of transparent shaders in fog dynamically
================
*/
float	R_FogFactor( float s, float t ) {
	float	d;

	s -= 1.0/512;
	if ( s < 0 ) {
		return 0;
	}
	if ( t < 1.0/32 ) {
		return 0;
	}
	if ( t < 31.0/32 ) {
		s *= (t - 1.0f/32.0f) / (30.0f/32.0f);
	}

	// we need to leave a lot of clamp range
	s *= 8;

	if ( s > 1.0 ) {
		s = 1.0;
	}

	d = tr.fogTable[ (int)(s * (FOG_TABLE_SIZE-1)) ];

	return d;
}

/*
================
R_CreateFogImage
================
*/
#define	FOG_S	256
#define	FOG_T	32
static void R_CreateFogImage( void ) {
	int		x,y;
	byte	*data;
	float	d;
	float	borderColor[4];

	data = ri.Hunk_AllocateTempMemory( FOG_S * FOG_T * 4 );

	// S is distance, T is depth
	for (x=0 ; x<FOG_S ; x++) {
		for (y=0 ; y<FOG_T ; y++) {
			d = R_FogFactor( ( x + 0.5f ) / FOG_S, ( y + 0.5f ) / FOG_T );

			data[(y*FOG_S+x)*4+0] = 
			data[(y*FOG_S+x)*4+1] = 
			data[(y*FOG_S+x)*4+2] = 255;
			data[(y*FOG_S+x)*4+3] = 255*d;
		}
	}
	// standard openGL clamping doesn't really do what we want -- it includes
	// the border color at the edges.  OpenGL 1.2 has clamp-to-edge, which does
	// what we want.
	tr.fogImage = R_CreateImage("*fog", (byte *)data, FOG_S, FOG_T, qfalse, qfalse, GL_CLAMP_TO_EDGE );
	ri.Hunk_FreeTempMemory( data );

	borderColor[0] = 1.0;
	borderColor[1] = 1.0;
	borderColor[2] = 1.0;
	borderColor[3] = 1;

	qglTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );
}

/*
==================
R_CreateDefaultImage
==================
*/
#define	DEFAULT_SIZE	16
static void R_CreateDefaultImage( void ) {
	int		x;
	byte	data[DEFAULT_SIZE][DEFAULT_SIZE][4];

	// the default image will be a box, to allow you to see the mapping coordinates
	Com_Memset( data, 32, sizeof( data ) );
	for ( x = 0 ; x < DEFAULT_SIZE ; x++ ) {
		data[0][x][0] =
		data[0][x][1] =
		data[0][x][2] =
		data[0][x][3] = 255;

		data[x][0][0] =
		data[x][0][1] =
		data[x][0][2] =
		data[x][0][3] = 255;

		data[DEFAULT_SIZE-1][x][0] =
		data[DEFAULT_SIZE-1][x][1] =
		data[DEFAULT_SIZE-1][x][2] =
		data[DEFAULT_SIZE-1][x][3] = 255;

		data[x][DEFAULT_SIZE-1][0] =
		data[x][DEFAULT_SIZE-1][1] =
		data[x][DEFAULT_SIZE-1][2] =
		data[x][DEFAULT_SIZE-1][3] = 255;
	}
	tr.defaultImage = R_CreateImage("*default", (byte *)data, DEFAULT_SIZE, DEFAULT_SIZE, qtrue, qfalse, GL_REPEAT );
}

/*
==================
R_CreateBuiltinImages
==================
*/
void R_CreateBuiltinImages( void ) {
	int		x,y;
	byte	data[DEFAULT_SIZE][DEFAULT_SIZE][4];

	R_CreateDefaultImage();

	// we use a solid white image instead of disabling texturing
	Com_Memset( data, 255, sizeof( data ) );
	tr.whiteImage = R_CreateImage("*white", (byte *)data, 8, 8, qfalse, qfalse, GL_REPEAT );

	if (r_dlightMode->integer >= 2)
	{
		for( x = 0; x < MAX_DLIGHTS; x++)
		{
			tr.shadowCubemaps[x] = R_CreateCubeImage(va("*shadowcubemap%i", x), (byte *)data, DEFAULT_SIZE, DEFAULT_SIZE, qfalse, qfalse, GL_CLAMP_TO_EDGE );
		}
	}

	// with overbright bits active, we need an image which is some fraction of full color,
	// for default lightmaps, etc
	for (x=0 ; x<DEFAULT_SIZE ; x++) {
		for (y=0 ; y<DEFAULT_SIZE ; y++) {
			data[y][x][0] = 
			data[y][x][1] = 
			data[y][x][2] = tr.identityLightByte;
			data[y][x][3] = 255;			
		}
	}

	tr.identityLightImage = R_CreateImage("*identityLight", (byte *)data, 8, 8, qfalse, qfalse, GL_REPEAT );


	for(x=0;x<32;x++) {
		// scratchimage is usually used for cinematic drawing
		tr.scratchImage[x] = R_CreateImage("*scratch", (byte *)data, DEFAULT_SIZE, DEFAULT_SIZE, qfalse, qtrue, GL_CLAMP_TO_EDGE );
	}

	R_CreateDlightImage();
	R_CreateFogImage();

	{
		int width, height, hdrFormat;

		if(glRefConfig.textureNonPowerOfTwo)
		{
			width = glConfig.vidWidth;
			height = glConfig.vidHeight;
		}
		else
		{
			width = NextPowerOfTwo(glConfig.vidWidth);
			height = NextPowerOfTwo(glConfig.vidHeight);
		}

		hdrFormat = GL_RGBA8;
		if (r_hdr->integer && glRefConfig.framebufferObject && glRefConfig.textureFloat)
			hdrFormat = GL_RGBA16F_ARB;

		tr.renderImage = R_CreateImage2("_render", NULL, width, height, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, hdrFormat);
#ifdef REACTION
		tr.godRaysImage = R_CreateImage2("*godRays", NULL, width, height, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_RGBA8);
#endif

		tr.screenScratchImage = R_CreateImage2("*screenScratch", NULL, width, height, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_RGBA8);

		if (glRefConfig.framebufferObject)
		{
			tr.renderDepthImage  = R_CreateImage2("*renderdepth",  NULL, width, height, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_DEPTH_COMPONENT24_ARB);
			tr.textureDepthImage = R_CreateImage2("*texturedepth", NULL, 256, 256, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_DEPTH_COMPONENT24_ARB);
		}

		{
			unsigned short sdata[4];
			void *p;

			if (hdrFormat == GL_RGBA16F_ARB)
			{
				sdata[0] = FloatToHalf(0.0f);
				sdata[1] = FloatToHalf(0.45f);
				sdata[2] = FloatToHalf(1.0f);
				sdata[3] = FloatToHalf(1.0f);
				p = &sdata[0];
			}
			else
			{
				data[0][0][0] = 0;
				data[0][0][1] = 0.45f * 255;
				data[0][0][2] = 255;
				data[0][0][3] = 255;
				p = data;
			}

			tr.calcLevelsImage =  R_CreateImage2("*calcLevels",  p, 1, 1,IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, hdrFormat);
			tr.fixedLevelsImage = R_CreateImage2("*fixedLevels", p, 1, 1, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, hdrFormat);
		}

		for (x = 0; x < 2; x++)
		{
			tr.textureScratchImage[x] = R_CreateImage2(va("*textureScratch%d", x), NULL, 256, 256, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_RGBA8);
		}
		for (x = 0; x < 2; x++)
		{
			tr.quarterImage[x] = R_CreateImage2(va("*quarter%d", x), NULL, 512, 512, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_RGBA8);
		}
	}

	for( x = 0; x < MAX_DRAWN_PSHADOWS; x++)
	{
		tr.pshadowMaps[x] = R_CreateImage2(va("*shadowmap%i", x), NULL, 256, 256, IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, GL_RGBA8);
	}
}


/*
===============
R_SetColorMappings
===============
*/
void R_SetColorMappings( void ) {
	int		i, j;
	float	g;
	int		inf;
	int		shift;

	// setup the overbright lighting
	tr.overbrightBits = r_overBrightBits->integer;
	if ( !glConfig.deviceSupportsGamma ) {
		tr.overbrightBits = 0;		// need hardware gamma for overbright
	}

	// never overbright in windowed mode
	if ( 0 /* !glConfig.isFullscreen */ ) 
	{
		tr.overbrightBits = 0;
	}

	// allow 2 overbright bits in 24 bit, but only 1 in 16 bit
	if ( glConfig.colorBits > 16 ) {
		if ( tr.overbrightBits > 2 ) {
			tr.overbrightBits = 2;
		}
	} else {
		if ( tr.overbrightBits > 1 ) {
			tr.overbrightBits = 1;
		}
	}
	if ( tr.overbrightBits < 0 ) {
		tr.overbrightBits = 0;
	}

	tr.identityLight = 1.0f / ( 1 << tr.overbrightBits );
	tr.identityLightByte = 255 * tr.identityLight;


	if ( r_intensity->value <= 1 ) {
		ri.Cvar_Set( "r_intensity", "1" );
	}

	if ( r_gamma->value < 0.5f ) {
		ri.Cvar_Set( "r_gamma", "0.5" );
	} else if ( r_gamma->value > 3.0f ) {
		ri.Cvar_Set( "r_gamma", "3.0" );
	}

	g = r_gamma->value;

	shift = tr.overbrightBits;

	if (glRefConfig.framebufferObject)
		shift = 0;

	for ( i = 0; i < 256; i++ ) {
		if ( g == 1 ) {
			inf = i;
		} else {
			inf = 255 * pow ( i/255.0f, 1.0f / g ) + 0.5f;
		}
		inf <<= shift;
		if (inf < 0) {
			inf = 0;
		}
		if (inf > 255) {
			inf = 255;
		}
		s_gammatable[i] = inf;
	}

	for (i=0 ; i<256 ; i++) {
		j = i * r_intensity->value;
		if (j > 255) {
			j = 255;
		}
		s_intensitytable[i] = j;
	}

	if ( glConfig.deviceSupportsGamma )
	{
		GLimp_SetGamma( s_gammatable, s_gammatable, s_gammatable );
	}
}

/*
===============
R_InitImages
===============
*/
void	R_InitImages( void ) {
	Com_Memset(hashTable, 0, sizeof(hashTable));
	// build brightness translation tables
	R_SetColorMappings();

	// create default texture and white texture
	R_CreateBuiltinImages();
}

/*
===============
R_DeleteTextures
===============
*/
void R_DeleteTextures( void ) {
	int		i;

	for ( i=0; i<tr.numImages ; i++ ) {
		qglDeleteTextures( 1, &tr.images[i]->texnum );
	}
	Com_Memset( tr.images, 0, sizeof( tr.images ) );

	tr.numImages = 0;

	Com_Memset( glState.currenttextures, 0, sizeof( glState.currenttextures ) );
	if ( qglActiveTextureARB ) {
		GL_SelectTexture( 1 );
		qglBindTexture( GL_TEXTURE_2D, 0 );
		GL_SelectTexture( 0 );
		qglBindTexture( GL_TEXTURE_2D, 0 );
	} else {
		qglBindTexture( GL_TEXTURE_2D, 0 );
	}
}

/*
============================================================================

SKINS

============================================================================
*/

/*
==================
CommaParse

This is unfortunate, but the skin files aren't
compatable with our normal parsing rules.
==================
*/
static char *CommaParse( char **data_p ) {
	int c = 0, len;
	char *data;
	static	char	com_token[MAX_TOKEN_CHARS];

	data = *data_p;
	len = 0;
	com_token[0] = 0;

	// make sure incoming data is valid
	if ( !data ) {
		*data_p = NULL;
		return com_token;
	}

	while ( 1 ) {
		// skip whitespace
		while( (c = *data) <= ' ') {
			if( !c ) {
				break;
			}
			data++;
		}


		c = *data;

		// skip double slash comments
		if ( c == '/' && data[1] == '/' )
		{
			while (*data && *data != '\n')
				data++;
		}
		// skip /* */ comments
		else if ( c=='/' && data[1] == '*' ) 
		{
			while ( *data && ( *data != '*' || data[1] != '/' ) ) 
			{
				data++;
			}
			if ( *data ) 
			{
				data += 2;
			}
		}
		else
		{
			break;
		}
	}

	if ( c == 0 ) {
		return "";
	}

	// handle quoted strings
	if (c == '\"')
	{
		data++;
		while (1)
		{
			c = *data++;
			if (c=='\"' || !c)
			{
				com_token[len] = 0;
				*data_p = ( char * ) data;
				return com_token;
			}
			if (len < MAX_TOKEN_CHARS)
			{
				com_token[len] = c;
				len++;
			}
		}
	}

	// parse a regular word
	do
	{
		if (len < MAX_TOKEN_CHARS)
		{
			com_token[len] = c;
			len++;
		}
		data++;
		c = *data;
	} while (c>32 && c != ',' );

	if (len == MAX_TOKEN_CHARS)
	{
//		ri.Printf (PRINT_DEVELOPER, "Token exceeded %i chars, discarded.\n", MAX_TOKEN_CHARS);
		len = 0;
	}
	com_token[len] = 0;

	*data_p = ( char * ) data;
	return com_token;
}


/*
===============
RE_RegisterSkin

===============
*/
qhandle_t RE_RegisterSkin( const char *name ) {
	qhandle_t	hSkin;
	skin_t		*skin;
	skinSurface_t	*surf;
	union {
		char *c;
		void *v;
	} text;
	char		*text_p;
	char		*token;
	char		surfName[MAX_QPATH];

	if ( !name || !name[0] ) {
		ri.Printf( PRINT_DEVELOPER, "Empty name passed to RE_RegisterSkin\n" );
		return 0;
	}

	if ( strlen( name ) >= MAX_QPATH ) {
		ri.Printf( PRINT_DEVELOPER, "Skin name exceeds MAX_QPATH\n" );
		return 0;
	}


	// see if the skin is already loaded
	for ( hSkin = 1; hSkin < tr.numSkins ; hSkin++ ) {
		skin = tr.skins[hSkin];
		if ( !Q_stricmp( skin->name, name ) ) {
			if( skin->numSurfaces == 0 ) {
				return 0;		// default skin
			}
			return hSkin;
		}
	}

	// allocate a new skin
	if ( tr.numSkins == MAX_SKINS ) {
		ri.Printf( PRINT_WARNING, "WARNING: RE_RegisterSkin( '%s' ) MAX_SKINS hit\n", name );
		return 0;
	}
	tr.numSkins++;
	skin = ri.Hunk_Alloc( sizeof( skin_t ), h_low );
	tr.skins[hSkin] = skin;
	Q_strncpyz( skin->name, name, sizeof( skin->name ) );
	skin->numSurfaces = 0;

	// make sure the render thread is stopped
	R_SyncRenderThread();

	// If not a .skin file, load as a single shader
	if ( strcmp( name + strlen( name ) - 5, ".skin" ) ) {
		skin->numSurfaces = 1;
		skin->surfaces[0] = ri.Hunk_Alloc( sizeof(skin->surfaces[0]), h_low );
		skin->surfaces[0]->shader = R_FindShader( name, LIGHTMAP_NONE, qtrue );
		return hSkin;
	}

	// load and parse the skin file
    ri.FS_ReadFile( name, &text.v );
	if ( !text.c ) {
		return 0;
	}

	text_p = text.c;
	while ( text_p && *text_p ) {
		// get surface name
		token = CommaParse( &text_p );
		Q_strncpyz( surfName, token, sizeof( surfName ) );

		if ( !token[0] ) {
			break;
		}
		// lowercase the surface name so skin compares are faster
		Q_strlwr( surfName );

		if ( *text_p == ',' ) {
			text_p++;
		}

		if ( strstr( token, "tag_" ) ) {
			continue;
		}
		
		// parse the shader name
		token = CommaParse( &text_p );

		surf = skin->surfaces[ skin->numSurfaces ] = ri.Hunk_Alloc( sizeof( *skin->surfaces[0] ), h_low );
		Q_strncpyz( surf->name, surfName, sizeof( surf->name ) );
		surf->shader = R_FindShader( token, LIGHTMAP_NONE, qtrue );
		skin->numSurfaces++;
	}

	ri.FS_FreeFile( text.v );


	// never let a skin have 0 shaders
	if ( skin->numSurfaces == 0 ) {
		return 0;		// use default skin
	}

	return hSkin;
}


/*
===============
R_InitSkins
===============
*/
void	R_InitSkins( void ) {
	skin_t		*skin;

	tr.numSkins = 1;

	// make the default skin have all default shaders
	skin = tr.skins[0] = ri.Hunk_Alloc( sizeof( skin_t ), h_low );
	Q_strncpyz( skin->name, "<default skin>", sizeof( skin->name )  );
	skin->numSurfaces = 1;
	skin->surfaces[0] = ri.Hunk_Alloc( sizeof( *skin->surfaces ), h_low );
	skin->surfaces[0]->shader = tr.defaultShader;
}

/*
===============
R_GetSkinByHandle
===============
*/
skin_t	*R_GetSkinByHandle( qhandle_t hSkin ) {
	if ( hSkin < 1 || hSkin >= tr.numSkins ) {
		return tr.skins[0];
	}
	return tr.skins[ hSkin ];
}

/*
===============
R_SkinList_f
===============
*/
void	R_SkinList_f( void ) {
	int			i, j;
	skin_t		*skin;

	ri.Printf (PRINT_ALL, "------------------\n");

	for ( i = 0 ; i < tr.numSkins ; i++ ) {
		skin = tr.skins[i];

		ri.Printf( PRINT_ALL, "%3i:%s\n", i, skin->name );
		for ( j = 0 ; j < skin->numSurfaces ; j++ ) {
			ri.Printf( PRINT_ALL, "       %s = %s\n", 
				skin->surfaces[j]->name, skin->surfaces[j]->shader->name );
		}
	}
	ri.Printf (PRINT_ALL, "------------------\n");
}


