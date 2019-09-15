project(sndfile-tools C)
cmake_minimum_required(VERSION 3.6)

#common
add_executable(sndfile-generate-chirp src/generate-chirp.c src/common.c)
add_executable(sndfile-waveform src/waveform.c src/common.c)
add_executable(sndfile-spectrogram src/spectrogram.c src/spectrum.c src/window.c src/common.c)
add_executable(sndfile-mix-to-mono src/mix-to-mono.c src/common.c)
#add_executable(sndfile-jackplay src/jackplay.c)

# find libraries (PITA on Windows ...)
if(WIN32)
    find_library(SNDFILE_LIBRARY NAMES libsndfile-1 libsndfile HINTS ${PROJECT_SOURCE_DIR}/libsndfile/lib)
    #find_library(FFTW_LIBRARY NAMES fftw3-3 PATH ${CMAKE_CURRENT_SOURCE_DIR}/fftw64 ) #todo: why is find_library() looking for this in places other than where I asked it to look ?
    set(FFTW_LIBRARY ${PROJECT_SOURCE_DIR}/fftw64/libfftw3-3.lib)
    find_library(CAIRO_LIBRARY NAMES cairo HINTS ${PROJECT_SOURCE_DIR}/cairo/lib/x64)
    include_directories(libsndfile/include fftw64 cairo/include)
else()
    find_library(SNDFILE_LIBRARY NAMES libsndfile-1)
    find_library(FFTW_LIBRARY NAMES libfftw3-3)
    find_library(CAIRO_LIBRARY NAMES libcairo)
endif()

# common
message(STATUS "libsndfile library location: " ${SNDFILE_LIBRARY})
message(STATUS "fftw library location: " ${FFTW_LIBRARY}) 
message(STATUS "cairo library location: "  ${CAIRO_LIBRARY})

target_link_libraries(sndfile-generate-chirp ${SNDFILE_LIBRARY})
target_link_libraries(sndfile-waveform ${SNDFILE_LIBRARY} ${CAIRO_LIBRARY})
target_link_libraries(sndfile-mix-to-mono ${SNDFILE_LIBRARY})
target_link_libraries(sndfile-spectrogram ${SNDFILE_LIBRARY} ${FFTW_LIBRARY} ${CAIRO_LIBRARY})

if(WIN32)
# deploy dlls to target directory
add_custom_command(TARGET sndfile-spectrogram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/libsndfile/bin/libsndfile-1.dll"
        "$<TARGET_FILE_DIR:sndfile-spectrogram>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/cairo/lib/x64/cairo.dll"
        "$<TARGET_FILE_DIR:sndfile-spectrogram>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/fftw64/libfftw3-3.dll"
        "$<TARGET_FILE_DIR:sndfile-spectrogram>"
    )
endif()