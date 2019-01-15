TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    DataProcessor.cpp \
    MdSpi.cpp \
    property.cpp \
    TraderSpi.cpp \
    TimeProcesser.cpp \
    CSHFETraderSpi.cpp

HEADERS += \
    DataProcessor.h \
    MdSpi.h \
    property.h \
    TraderSpi.h \
    TimeProcesser.h \
    CSHFETraderSpi.h \
    mysqlconnectpool.h \
    DBTable.h


LIBS += -L$$PWD/lib/ -lthostmduserapi -lmduserapi -ltraderapi  -lthostmduserapi  -lthosttraderapi

INCLUDEPATH += $$PWD/


LIBS += -L$$PWD/../glog_0_3_3/ -lglog
INCLUDEPATH += $$PWD/../glog_0_3_3


LIBS += -L$$PWD/../boost_1_61_0/stage/lib/ -lboost_system -lboost_date_time -lboost_system -lboost_thread -lpthread -lboost_chrono

INCLUDEPATH += $$PWD/../boost_1_61_0/


LIBS += -licui18n -licuuc -licudata  -ldl

OTHER_FILES += \
    ../build-FlowOrder-gcc5_4_0-Debug/config/global.properties


unix:!macx: LIBS += -L/usr/lib64/mysql/ -lmysqlclient

unix:!macx: LIBS += -L/usr/local/lib -lmysqlpp

INCLUDEPATH += /usr/local/include/mysql++ /usr/include/mysql

DEPENDPATH += /usr/local/include/mysql++
