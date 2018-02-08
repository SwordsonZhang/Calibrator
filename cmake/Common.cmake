
# Detect OS

if(MSVC OR MSYS OR MINGW)
  set(OS_WIN TRUE)
elseif(APPLE)
  set(OS_MAC TRUE)
elseif(UNIX)
  set(OS_LINUX TRUE)
else()
  message(STATUS "Maybe not work on this os.")
endif()

if(OS_LINUX)
  execute_process(COMMAND uname -r COMMAND tr -d '\n' OUTPUT_VARIABLE UNAME_R_TEGRA)
  if(${UNAME_R_TEGRA} MATCHES ".*(tegra|jetsonbot).*")
    set(OS_TEGRA TRUE)
    message(STATUS "OS_TEGRA: ${OS_TEGRA}")
  endif()
endif()

# Functions

macro(find_value NAME OUTVAL)
  if(OS_LINUX)
    set(SDK_CONFIG "${CMAKE_CURRENT_LIST_DIR}/../../sdk.cfg")
    if(EXISTS "${SDK_CONFIG}")
      execute_process(
        COMMAND cat ${SDK_CONFIG}
        COMMAND grep "^${NAME}="
        COMMAND sed "s/^${NAME}=\\s*\\(.*\\)/\\1/"
        OUTPUT_VARIABLE __value
        OUTPUT_STRIP_TRAILING_WHITESPACE)
      set("${OUTVAL}" "${__value}")
    endif()
  endif()
endmacro()
