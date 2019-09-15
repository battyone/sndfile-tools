project(sndfile-tools C)
cmake_minimum_required(VERSION 3.6)

#add_executable(sndfile-generate-chirp )
#add_executable(sndfile-jackplay )
add_executable(sndfile-spectrogram src/spectrogram.c src/spectrum.c src/window.c src/common.c)
#add_executable(sndfile-mix-to-mono)

if(WIN32)
    link_directories(libsndfile/lib fftw64 cairo/lib/x64)
    include_directories(libsndfile/include fftw64 cairo/include)
    # note: for Windows, use actual filename of lib file
    target_link_libraries(sndfile-spectrogram libsndfile-1.lib libfftw3-3.lib cairo.lib)
endif()

