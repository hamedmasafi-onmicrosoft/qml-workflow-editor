cmake_minimum_required(VERSION 3.16)

project(WorkFlowEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWorkFlowEditor
    main.cpp
    block.h block.cpp
    workfloweditorarea.h workfloweditorarea.cpp

    abstractrelation.h abstractrelation.cpp

    directrelation.h directrelation.cpp
    curvedrelation.h curvedrelation.cpp

    relationhandle.h relationhandle.cpp

    commands/addblockcommand.h commands/addblockcommand.cpp

    abstracttool.h abstracttool.cpp
    selecttool.h selecttool.cpp
    relationtool.h relationtool.cpp
)

qt_add_qml_module(appWorkFlowEditor
    URI WorkFlowEditor
    VERSION 1.0
    QML_FILES
        Main.qml
        SampleBlock.qml
        SimpleRelation.qml
        InputDataBlock.qml
        OutputBlock.qml
        SimpleRelationHandle.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWorkFlowEditor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWorkFlowEditor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWorkFlowEditor
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appWorkFlowEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
