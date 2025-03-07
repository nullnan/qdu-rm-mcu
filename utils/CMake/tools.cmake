MACRO(INCLUDE_ALL_DIR curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)

    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child} AND EXISTS ${curdir}/${child}/info.cmake)
            set(SUB_DIR ${curdir}/${child})
            include(${curdir}/${child}/info.cmake)
        ENDIF()
    ENDFOREACH()
ENDMACRO()

MACRO(SUB_ADD_SRC src)
    FOREACH(item ${${src}})
        LIST(APPEND ${PROJECT_NAME}_SOURCES ${item})
    ENDFOREACH()
ENDMACRO()

MACRO(SUB_ADD_INC inc)
    FOREACH(item ${${inc}})
        LIST(APPEND ${PROJECT_NAME}_INCLUDES ${item})
    ENDFOREACH()
ENDMACRO()

MACRO(CHECK_SUB_ENABLE enable)
    string(REGEX REPLACE ".*/\(.*\)" "\\1" ${enable} ${SUB_DIR})
    set(${enable} ${${CONFIG_PREFIX}${${enable}}})
ENDMACRO()
