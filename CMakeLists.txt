cmake_minimum_required(VERSION 3.16)

project(WorkFlowEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

include_directories(src)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWorkFlowEditor
    src/main.cpp
    src/block.h src/block.cpp
    src/workfloweditorarea.h src/workfloweditorarea.cpp

    src/abstractrelation.h src/abstractrelation.cpp

    src/directrelation.h src/directrelation.cpp
    src/curvedrelation.h src/curvedrelation.cpp

    src/relationhandle.h src/relationhandle.cpp

    src/commands/addblockcommand.h src/commands/addblockcommand.cpp

    src/abstracttool.h src/abstracttool.cpp
    src/selecttool.h src/selecttool.cpp
    src/relationtool.h src/relationtool.cpp
)

qt_add_resources(appWorkFlowEditor
    PREFIX /
    FILES
        res/icons/prompt.svg
        res/icons/openai.svg
        res/icons/ds.svg
        res/icons/code.svg
        res/icons/chat.svg
        res/icons/note.svg
)

qt_add_qml_module(appWorkFlowEditor
    URI WorkFlowEditor
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/SampleBlock.qml
        qml/SimpleRelation.qml
        qml/InputDataBlock.qml
        qml/OutputBlock.qml
        qml/SimpleRelationHandle.qml
        qml/BlockHeader.qml
        qml/BlockBackground.qml

        qml/blocks/AbstractBlock.qml
        qml/blocks/OpenAIEmbeddings.qml
        qml/blocks/ChatInputBlock.qml
        qml/blocks/AstraDBBlock.qml
        qml/blocks/ParseDataBlock.qml
        qml/blocks/PromptBlock.qml
        qml/blocks/ChatOutputBlock.qml
        qml/blocks/NoteBlock.qml

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
