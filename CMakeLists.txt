# To add this cmake file, follow:
# ...
# add_subdirectory("path/to/this/cmakefile")
# ...
# add_executable(${PROJECT_NAME} ... ${CPP_UTILS_SOURCE_FILES})
# ...

file(GLOB CPP_UTILS_SOURCES "*.cpp")
file(GLOB CPP_UTILS_HEADERS "headers/*.h")
file(GLOB CPP_UTILS_ENUMS "enums/*.h")
file(GLOB CPP_UTILS_INTERFACES "interfaces/*.h")
set (CPP_UTILS_SOURCE_FILES ${CPP_UTILS_SOURCES} ${CPP_UTILS_HEADERS} ${CPP_UTILS_ENUMS} ${CPP_UTILS_INTERFACES} PARENT_SCOPE)