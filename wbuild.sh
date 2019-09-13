#/bin/sh

# Spectrogram: I managed to get this to compile using mingw-w64 using this command line:
gcc src/spectrogram.c src/spectrum.c src/window.c src/common.c -Ilibsndfile/include -Ifftw64 -Icairo/include -Lfftw64 -llibfftw3-3 -Llibsndfile/lib -llibsndfile-1 -Lcairo/lib/x64 -lcairo -o spectrogram.exe -O3

mv spectrogram.exe bin/