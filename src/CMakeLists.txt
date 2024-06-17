file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)


add_library(src ${SOURCES}  "myMain.h" "GameManager.cpp" "Surface.cpp" "Surface.h" "Panel.cpp" "SurfaceType.h" "Player.cpp" "Player.h")
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC pugixml sfml-graphics sfml-audio box2d)