
typedef struct
{	int speclen ;
	enum WINDOW_FUNCTION wfunc ;
	fftw_plan plan ;

	double *time_domain ;
	double *window ;

#ifdef CUFFTW
	fftw_complex *freq_domain ;
#else
	double *freq_domain ;
#endif

	double *mag_spec ;

	double data [] ;
} spectrum ;


spectrum * create_spectrum (int speclen, enum WINDOW_FUNCTION window_function) ;

void destroy_spectrum (spectrum * spec) ;

double calc_magnitude_spectrum (spectrum * spec) ;
