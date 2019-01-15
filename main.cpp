#include <iostream>
#include <memory>
#include "DataProcessor.h"
#include <glog/logging.h>
#include "NetSniffer.cpp"
#include "TimeProcesser.h"
#include "MdSpi.h"
#include "mysqlconnectpool.h"
using namespace std;
DataInitInstance* dii;
// UserApi对象
CThostFtdcMdApi* mdUserApi;
int start_process=0;
void mkdataInit();
// 请求编号
int iRequestID;
void startSendMDThread(int sendtype);//发送类型 0：以客户端方式发送；1，以服务端方式发送
boost::thread_group thread_log_group;

//mysql
std::shared_ptr<MysqlConnectPool> g_db_pool = nullptr;
int main()
{
    //netTest();
    google::InitGoogleLogging("");
    google::SetLogDestination(google::GLOG_INFO, "./Logs");
    //google::SetStderrLogging(2);
    google::SetLogFilenameExtension("log_");
    dii = new DataInitInstance();

    //TradeProcessor* tpr = new TradeProcessor();
    //ua = new UserAccount();
    dii->codeCC = new CodeConverter("gb2312","utf-8");
    dii->beginDataInit();
    for( unordered_map<string, BaseAccount*>::iterator iter=dii->followNBAccountMap.begin();iter!=dii->followNBAccountMap.end();iter++ ){
           cout<<"key="<<iter->first<<endl;
           UserAccountInfo* ua=(UserAccountInfo*)iter->second;
           cout<<"pwd="<<ua->password<<endl;
    }
    //set account flag =follow
    dii->whichAccount="follow";
    dii->initTradeApi(dii->followNBAccountMap);
    while(!dii->isAllLoginOK()){
        cout<<"not all ok"<<endl;
        boost::this_thread::yield();
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
    //set account flag =naman
    dii->whichAccount="naman";
    dii->initTradeApi(dii->NBAccountMap);
    cout << ">>>>>>>>>>>>if ok,please press Enter!<<<<<<<<<<<<"<< endl;
    //getchar();
    //cout << "Hello World!" << endl;
    while(!dii->isAllLoginOK()){
        cout<<"not all ok"<<endl;
        boost::this_thread::yield();
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
    //req instrument only once.
    for( unordered_map<string, BaseAccount*>::iterator iter=dii->followNBAccountMap.begin();iter!=dii->followNBAccountMap.end();iter++ ){
           cout<<"drive investorid="<<iter->first<<" to query instruemnt info."<<endl;
           string ivestorID=iter->first;
           CTPInterface* interface=dii->getTradeApi(ivestorID);
           //cout<<ivestorID<<endl;
           CTraderSpi *userSpi=(CTraderSpi*)interface->pUserSpi;
           dii->loginInvestorID=ivestorID;
           userSpi->ReqQryInstrument();
           dii->isDoneSometh=false;
           while(!dii->isDoneSometh){
                boost::this_thread::sleep(boost::posix_time::seconds(1));
           }
           break;
    }
    cout<<"all ok"<<endl;
    /*
    if(dii->environment=="1"){
        mkdataInit();//product is omit
        dii->isDoneSometh=false;
        while(!dii->isDoneSometh){
             boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
        cout<<"md init ok"<<endl;
    }*/
    dii->startStrategy();
    startSendMDThread(1);
    /*this will receive order from exchange,not use.
    if(dii->environment=="2"){
        //drive seat to login exchange
        dii->initExgTraderApi();
        while(!dii->isExgOk){
            cout<<"not all ok"<<endl;
            boost::this_thread::yield();
            boost::this_thread::sleep(boost::posix_time::seconds(2));
        }
    }*/
    while(1){
        boost::this_thread::sleep(boost::posix_time::seconds(1000));    //microsecond,millisecn
    }
    return 0;
}
/************************************************************************/
/* 初始化参数列表                                                                     */
/************************************************************************/
void mkdataInit() {
    cout << "start to init mdApi" << endl;
    mdUserApi = CThostFtdcMdApi::CreateFtdcMdApi("log2");			// 创建UserApi
    CThostFtdcMdSpi* pUserSpi = new CMdSpi();
    mdUserApi->RegisterSpi(pUserSpi);						// 注册事件类
    cout<<"forntip="<<dii->MARKET_FRONT_ADDR<<endl;
    mdUserApi->RegisterFront(dii->MARKET_FRONT_ADDR);					// connect
    mdUserApi->Init();
    cout << "end init mdApi" << endl;
}
void startSendMDThread(int sendtype)
{
    //TraderDemo temp;
    //temp.m_queryServerIp = boost::lexical_cast<string>(TRADE_FRONT_ADDR);
    thread_log_group.create_thread(&ttt);
    //thread_log_group.create_thread(processStrategy);
    //thread_log_group.create_thread(metricProcesser);
}
