QT       += core gui
QT       += sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(src/entity/entity.pri) # 模型数据库关联
include(src/common/common.pri) #通用类库
include(src/erpdelegate/erpdelegate.pri) #自定义代理
include(src/rbacmanager/rbacmanager.pri) # 权限管理
include(src/sysmanager/sysmanager.pri) # 系统管理
include(src/suppliermanager/suppliermanager.pri) # 供应商管理
include(src/employeemanager/employeemanager.pri) # 人力资源管理

INCLUDEPATH += $$PWD/src/entity
INCLUDEPATH += $$PWD/src/common
INCLUDEPATH += $$PWD/src/erpdelegate
INCLUDEPATH += $$PWD/src/rbacmanager
INCLUDEPATH += $$PWD/src/sysmanager
INCLUDEPATH += $$PWD/src/suppliermanager
INCLUDEPATH += $$PWD/src/employeemanager

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main/erplogin.cpp \
    main.cpp \
    src/main/erpsys.cpp

HEADERS += \
    src/main/erplogin.h \
    src/main/erpsys.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS += \
    src/main/erplogin.ui


