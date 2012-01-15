/*
** Copyright (C) 2007-2012 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 or version 3 of the
** License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"

#include <string.h>
#include <math.h>

#include "common.h"

/* Global. */
const char *font_family = "DejaVu Sans Mono" ;

sf_count_t
sfx_mix_mono_read_double (SNDFILE * file, double * data, sf_count_t datalen)
{
	SF_INFO info ;

	sf_command (file, SFC_GET_CURRENT_SF_INFO, &info, sizeof (info)) ;

	if (info.channels == 1)
		return sf_read_double (file, data, datalen) ;

	static double multi_data [2048] ;
	int k, ch, frames_read ;
	sf_count_t dataout = 0 ;

	while (dataout < datalen)
	{	int this_read ;

		this_read = MIN (ARRAY_LEN (multi_data) / info.channels, datalen) ;

		frames_read = sf_readf_double (file, multi_data, this_read) ;
		if (frames_read == 0)
			break ;

		for (k = 0 ; k < frames_read ; k++)
		{	double mix = 0.0 ;

			for (ch = 0 ; ch < info.channels ; ch++)
				mix += multi_data [k * info.channels + ch] ;
			data [dataout + k] = mix / info.channels ;
			} ;

		dataout += frames_read ;
		} ;

	return dataout ;
} /* sfx_mix_mono_read_double */


double
calc_magnitude (const double * freq, int freqlen, double * magnitude)
{
	int k ;
	double max = 0.0 ;

	for (k = 1 ; k < freqlen / 2 ; k++)
	{	magnitude [k] = sqrt (freq [k] * freq [k] + freq [freqlen - k - 1] * freq [freqlen - k - 1]) ;
		max = MAX (max, magnitude [k]) ;
		} ;
	magnitude [0] = 0.0 ;

	return max ;
} /* calc_magnitude */

