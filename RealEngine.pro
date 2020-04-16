QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 -O0

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/Common/easyloggingpp/easylogging++.cc \
    source/Modules/MessageSystem/Message.cpp \
    source/Modules/Objects/Components/Transform.cpp \
    source/Modules/Objects/Model/Mesh.cpp \
    source/Modules/Objects/Model/Model.cpp \
    source/Modules/Objects/Model/ModelLoader.cpp \
    source/Modules/Objects/Object.cpp \
    source/Modules/Objects/ObjectManager.cpp \
    source/RealEngine.cpp \
    source/Ui/FileMenu.cpp \
    source/Modules/MessageSystem/MessageBus.cpp \
    source/Modules/MessageSystem/Messenger.cpp \
    source/Ui/ObjectListWidget.cpp \
    source/Ui/ObjectTransformWidget.cpp \
    source/main.cpp \
    source/Ui/MainWindow.cpp

HEADERS += \
    source/Common/easyloggingpp/easylogging++.h \
    source/Common/logging.h \
    source/Modules/MessageSystem/Message.h \
    source/Modules/MessageSystem/MessageType.h \
    source/Modules/Objects/Components/Transform.h \
    source/Modules/Objects/Model/Mesh.h \
    source/Modules/Objects/Model/Model.h \
    source/Modules/Objects/Model/ModelLoader.h \
    source/Modules/Objects/Object.h \
    source/Modules/Objects/ObjectManager.h \
    source/RealEngine.h \
    source/Ui/FileMenu.h \
    source/Ui/MainWindow.h \
    source/Modules/MessageSystem/MessageBus.h \
    source/Modules/MessageSystem/Messenger.h \
    source/Ui/ObjectListWidget.h \
    source/Ui/ObjectTransformWidget.h

FORMS += \
    source/Ui/MainWindow.ui \
    source/Ui/ObjectTransformWidget.ui

LIBS +=	\
    -lassimp

INCLUDEPATH +=	\
    source/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
