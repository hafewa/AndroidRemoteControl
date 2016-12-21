cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib SHARED src/main/cpp/native-lib.cpp )
add_library(PersistentDataManager SHARED src/main/cpp/PersistentDataManager.cpp)
add_library(NetworkController SHARED src/main/cpp/NetworkController.cpp)
find_library(log-lib log )
target_link_libraries( native-lib ${log-lib} )
target_link_libraries( native-lib PersistentDataManager )
