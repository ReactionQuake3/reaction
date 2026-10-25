# Import variables from misc/lib-versions.sh
file(STRINGS ${CMAKE_SOURCE_DIR}/misc/lib-versions.sh LIB_VERSIONS_CONTENT
    REGEX "^[A-Z_]+=[^ ]+")
foreach(LINE ${LIB_VERSIONS_CONTENT})
    if(LINE MATCHES "^([A-Z_]+)=(.+)$")
        set(${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
    endif()
endforeach()

include(libraries/curl)
include(libraries/freetype)
include(libraries/jpeg)
include(libraries/ogg)
include(libraries/opus)
include(libraries/openal)
include(libraries/sdl)
include(libraries/vorbis)
include(libraries/zlib)
