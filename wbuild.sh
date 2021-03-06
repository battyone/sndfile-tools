#/bin/sh

# Spectrogram: I managed to get this to compile using mingw-w64 using this command line:
#gcc src/spectrogram.c src/spectrum.c src/window.c src/common.c -Ilibsndfile/include -Ifftw64 -Icairo/include -Lfftw64 -llibfftw3-3 -Llibsndfile/lib -llibsndfile-1 -Lcairo/lib/x64 -lcairo -o spectrogram.exe -O3

#CUDA version (WIP)
#R2R transforms not supported by cufftw, so need to use r2c instead
#see https://docs.nvidia.com/cuda/cufft/index.html

gcc -DCUFFTW src/spectrogram.c src/spectrum.c src/window.c src/common.c -Ilibsndfile/include -I"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/include" -Icairo/include -L"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64" -lcufftw -Llibsndfile/lib -llibsndfile-1 -Lcairo/lib/x64 -lcairo -o spectrogram.exe -O3

mv spectrogram.exe bin/

# thanks to https://github.com/preshing/cairo-windows/releases for building the Cairo library on Windows
