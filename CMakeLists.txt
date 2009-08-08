project(plasma-defcon)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

set(defcon_SRCS defcon.cpp)

kde4_add_ui_files(defcon_SRCS ui/config.ui)
kde4_add_plugin(plasma_applet_defcon ${defcon_SRCS})
target_link_libraries(plasma_applet_defcon 
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})

install(TARGETS plasma_applet_defcon
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-defcon.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

install(FILES defcon.svg
        DESTINATION ${DATA_INSTALL_DIR}/desktoptheme/default/widgets/)
