file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}  "myMain.h")
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC pugixml sfml-graphics box2d)