cmake_minimum_required(VERSION 3.14)
project(pixel_wars)

set(CMAKE_CXX_STANDARD 17)

add_executable(pixel_wars main.cpp Drawer.h Game_World.h Entities.h Entity_Handler.h server.h client.h vector2.h Drawer.cpp Game_World.cpp link.h link.cpp test_runner.h unit_tests.h Entities.cpp unit_tests.cpp Entity_Handler.cpp Main_Menu.h including_headers.h)
#find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)\
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(pixel_wars sfml-graphics sfml-window sfml-system sfml-audio Threads::Threads)
