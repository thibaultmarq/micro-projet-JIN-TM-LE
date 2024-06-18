file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)


add_library(src ${SOURCES}  "myMain.h" "GameManager.cpp" "Surface.cpp" "MovingSurface.h" "Surface.h" "Panel.cpp" "SurfaceType.h" "Player.cpp" "Player.h" "MovingSurface.cpp" "StaticSurface.cpp" "StaticSurface.h" "SaveFile.h" "Command.h" "Command.cpp")

target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC pugixml sfml-graphics sfml-audio box2d)