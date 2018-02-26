cmake_minimum_required(VERSION 3.9)

project(Kris_Maya)

if(MSVC)
  set(DLLIMPORT "__declspec(dllimport)")
  set(DLLEXPORT "__declspec(dllexport)")
  set(DISABLE "__pragma(warning(push,0))")
  set(ENABLE "__pragma(warning(pop))")
endif()

set(PROJECT_SRCS
${PROJECT_SOURCE_DIR}/src/Multithread_Seperate.cpp
${PROJECT_SOURCE_DIR}/src/PluginMain.cpp

)

set(PROJECT_INCS
${PROJECT_SOURCE_DIR}/include/Kris/Kris_Maya/Multithread_Seperate.h
)

source_group("include" FILES ${PROJECT_INCS})
source_group("src"     FILES ${PROJECT_SRCS})

find_package( OpenCV REQUIRED )
find_package(Maya REQUIRED)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS} ${PROJECT_INCS})

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".mll")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_compile_definitions(${PROJECT_NAME} PUBLIC
                          WINDOWS_DISABLE_ALL_WARNING=${DISABLE}
                          WINDOWS_ENABLE_ALL_WARNING=${ENABLE})



# target_compile_definitions(${PROJECT_NAME} INTERFACE
#                           KRIS_MAYA_DLL=${DLLIMPORT})

# target_compile_definitions(${PROJECT_NAME} PRIVATE
#                           KRIS_MAYA_DLL=${DLLEXPORT})

target_include_directories(${PROJECT_NAME} PUBLIC
                          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
                          # ${MAYA_INCLUDE_DIR}
                          )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}
                                     # ${MAYA_LIBRARY}
                                     Maya::Maya 
                                     )


set_property(TARGET ${PROJECT_NAME} PROPERTY
            FOLDER ${CMAKE_PROJECT_NAME}/modules)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib COMPONENT install-app
        LIBRARY DESTINATION lib COMPONENT install-app
        RUNTIME DESTINATION bin COMPONENT install-app)

install(FILES ${PROJECT_SOURCE_DIR}/include/Hvr/Sample/Sample.h
        DESTINATION include/Hvr/Sample)

export(TARGETS ${PROJECT_NAME}
      APPEND FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake)

file(APPEND ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
    "find_dependency(OpenCV REQUIRED)\n")
