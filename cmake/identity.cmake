set(PROJECT_NAME Reaction)
set(PROJECT_VERSION 1.36)

set(SERVER_NAME Reactionded)
set(CLIENT_NAME Reaction)

set(BASEGAME Boomstick)

set(CGAME_MODULE cgame)
set(GAME_MODULE qagame)
set(UI_MODULE ui)

set(WINDOWS_ICON_PATH ${CMAKE_SOURCE_DIR}/misc/quake3.ico)

set(MACOS_ICON_PATH ${CMAKE_SOURCE_DIR}/misc/quake3.icns)
set(MACOS_BUNDLE_ID com.rq3.${CLIENT_NAME})

set(COPYRIGHT "Reaction Copyright © 2001-2026 Boomstick Studios and contributors. Quake III Arena Copyright © 1999-2000 id Software, Inc.")

set(CONTACT_EMAIL "bugs@rq3.com")

# Reaction registers no URL protocol handler (PROTOCOL_HANDLER stays commented out in q_shared.h), so
# PROTOCOL_HANDLER_SCHEME is not set.

# Reaction is a standalone game; the cache default lets -DBUILD_STANDALONE=OFF still override it.
set(BUILD_STANDALONE ON CACHE BOOL "Build binaries for standalone games")
