# Project name. Should be the same as the project directory name and
# will become the name of the binary target.
SET( PROJECT_NAME "IRC")

# Project source code list
SET( PROJECT_SOURCES
  main.cpp
)

# Project executable
ADD_EXECUTABLE(${PROJECT_NAME}
  ${PROJECT_SOURCES}
)

# Project dependencies
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  # Core library dependencies
  OpenEngine_Core
  OpenEngine_Logging
  OpenEngine_Display
  OpenEngine_Devices
  # Extensions
  Extensions_IRC
  Extensions_Sockets
)

