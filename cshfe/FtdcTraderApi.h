/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file FtdcTraderApi.h
///@brief 定义了客户端接口
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCTRADERAPI_H)
#define _FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiStruct.h"
//#include <src/ergti/types/MyFtdcUserApiDataType.h>

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#if defined(LIB_TRADER_API_EXPORT) && defined(ISLIB) && defined(UNIX)
#define TRADER_API_EXPORT  __attribute__ ((visibility("default")))
#else
#define TRADER_API_EXPORT
#endif 
#endif

class CShfeFtdcTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};

 	///度量报文回调通知。当API收到一个度量报文后，调用本方法，在本方法中可以调用AddLocalMeasureID。
	virtual int OnMeasureNotify(){return 0;};

	///错误应答
	virtual void OnRspError(CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户登录应答
	virtual void OnRspUserLogin(CShfeFtdcRspUserLoginField *pRspUserLogin, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户退出应答
	virtual void OnRspUserLogout(CShfeFtdcRspUserLogoutField *pRspUserLogout, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入应答
	virtual void OnRspOrderInsert(CShfeFtdcInputOrderField *pInputOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作应答
	virtual void OnRspOrderAction(CShfeFtdcOrderActionField *pOrderAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价录入应答
	virtual void OnRspQuoteInsert(CShfeFtdcInputQuoteField *pInputQuote, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价操作应答
	virtual void OnRspQuoteAction(CShfeFtdcQuoteActionField *pQuoteAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CShfeFtdcUserPasswordUpdateField *pUserPasswordUpdate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告录入应答
	virtual void OnRspExecOrderInsert(CShfeFtdcInputExecOrderField *pInputExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告操作应答
	virtual void OnRspExecOrderAction(CShfeFtdcExecOrderActionField *pExecOrderAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///管理报单录入应答
	virtual void OnRspAdminOrderInsert(CShfeFtdcInputAdminOrderField *pInputAdminOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///非标组合报单录入应答
	virtual void OnRspCombOrderInsert(CShfeFtdcInputCombOrderField *pInputCombOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///放弃执行宣告录入应答
	virtual void OnRspAbandonExecOrderInsert(CShfeFtdcInputAbandonExecOrderField *pInputAbandonExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///放弃执行宣告操作应答
	virtual void OnRspAbandonExecOrderAction(CShfeFtdcAbandonExecOrderActionField *pAbandonExecOrderAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价录入应答
	virtual void OnRspQuoteDemand(CShfeFtdcQuoteDemandInfoField *pQuoteDemandInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅主题应答
	virtual void OnRspSubscribeTopic(CShfeFtdcDisseminationField *pDissemination, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///会员资金查询应答
	virtual void OnRspQryPartAccount(CShfeFtdcRspPartAccountField *pRspPartAccount, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单查询应答
	virtual void OnRspQryOrder(CShfeFtdcOrderField *pOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价查询应答
	virtual void OnRspQryQuote(CShfeFtdcQuoteField *pQuote, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交单查询应答
	virtual void OnRspQryTrade(CShfeFtdcTradeField *pTrade, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///会员客户查询应答
	virtual void OnRspQryClient(CShfeFtdcRspClientField *pRspClient, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///会员持仓查询应答
	virtual void OnRspQryPartPosition(CShfeFtdcRspPartPositionField *pRspPartPosition, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///客户持仓查询应答
	virtual void OnRspQryClientPosition(CShfeFtdcRspClientPositionField *pRspClientPosition, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约查询应答
	virtual void OnRspQryInstrument(CShfeFtdcRspInstrumentField *pRspInstrument, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约交易状态查询应答
	virtual void OnRspQryInstrumentStatus(CShfeFtdcInstrumentStatusField *pInstrumentStatus, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///保值额度应答
	virtual void OnRspQryHedgeVolume(CShfeFtdcHedgeVolumeField *pHedgeVolume, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///信用限额查询应答
	virtual void OnRspQryCreditLimit(CShfeFtdcCreditLimitField *pCreditLimit, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///非标组合报单查询应答
	virtual void OnRspQryCombOrder(CShfeFtdcCombOrderField *pCombOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告查询应答
	virtual void OnRspQryExecOrder(CShfeFtdcExecOrderField *pExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///放弃执行宣告查询应答
	virtual void OnRspQryAbandonExecOrder(CShfeFtdcAbandonExecOrderField *pAbandonExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///普通行情查询应答
	virtual void OnRspQryMarketData(CShfeFtdcMarketDataField *pMarketData, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易所公告查询请求应答
	virtual void OnRspQryBulletin(CShfeFtdcBulletinField *pBulletin, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///主题查询应答
	virtual void OnRspQryTopic(CShfeFtdcDisseminationField *pDissemination, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约价位查询应答
	virtual void OnRspQryMBLMarketData(CShfeFtdcMBLMarketDataField *pMBLMarketData, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///信息查询应答
	virtual void OnRspQryInformation(CShfeFtdcInformationField *pInformation, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交回报
	virtual void OnRtnTrade(CShfeFtdcTradeField *pTrade) {};

	///报单回报
	virtual void OnRtnOrder(CShfeFtdcOrderField *pOrder) {};

	///执行宣告回报
	virtual void OnRtnExecOrder(CShfeFtdcExecOrderField *pExecOrder) {};

	///报价回报
	virtual void OnRtnQuote(CShfeFtdcQuoteField *pQuote) {};

	///非标组合报单回报
	virtual void OnRtnCombOrder(CShfeFtdcCombOrderField *pCombOrder) {};

	///放弃执行宣告回报
	virtual void OnRtnAbandonExecOrder(CShfeFtdcAbandonExecOrderField *pAbandonExecOrder) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CShfeFtdcInstrumentStatusField *pInstrumentStatus) {};

	///增加合约通知
	virtual void OnRtnInsInstrument(CShfeFtdcInstrumentField *pInstrument) {};

	///删除合约通知
	virtual void OnRtnDelInstrument(CShfeFtdcInstrumentField *pInstrument) {};

	///增加合约单腿通知
	virtual void OnRtnInsCombinationLeg(CShfeFtdcCombinationLegField *pCombinationLeg) {};

	///删除合约单腿通知
	virtual void OnRtnDelCombinationLeg(CShfeFtdcCombinationLegField *pCombinationLeg) {};

	///别名定义通知
	virtual void OnRtnAliasDefine(CShfeFtdcAliasDefineField *pAliasDefine) {};

	///数据流回退通知
	virtual void OnRtnFlowMessageCancel(CShfeFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///公告通知
	virtual void OnRtnBulletin(CShfeFtdcBulletinField *pBulletin) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CShfeFtdcInputOrderField *pInputOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CShfeFtdcOrderActionField *pOrderAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(CShfeFtdcInputQuoteField *pInputQuote, CShfeFtdcRspInfoField *pRspInfo) {};

	///报价操作错误回报
	virtual void OnErrRtnQuoteAction(CShfeFtdcQuoteActionField *pQuoteAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///执行宣告录入错误回报
	virtual void OnErrRtnExecOrderInsert(CShfeFtdcInputExecOrderField *pInputExecOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///执行宣告操作错误回报
	virtual void OnErrRtnExecOrderAction(CShfeFtdcExecOrderActionField *pExecOrderAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///非标组合报单录入错误回报
	virtual void OnErrRtnCombOrderInsert(CShfeFtdcInputCombOrderField *pInputCombOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///放弃执行宣告录入错误回报
	virtual void OnErrRtnAbandonExecOrderInsert(CShfeFtdcInputAbandonExecOrderField *pInputAbandonExecOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///放弃执行宣告操作错误回报
	virtual void OnErrRtnAbandonExecOrderAction(CShfeFtdcAbandonExecOrderActionField *pAbandonExecOrderAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///询价请求分发
	virtual void OnRtnQuoteDemandNotify(CShfeFtdcQuoteDemandNotifyField *pQuoteDemandNotify) {};

	///汇率查询应答
	virtual void OnRspQryExchangeRate(CShfeFtdcRspExchangeRateField *pRspExchangeRate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class TRADER_API_EXPORT CShfeFtdcTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CShfeFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	///获取系统版本号
	///@param nMajorVersion 主版本号
	///@param nMinorVersion 子版本号
	///@return 系统标识字符串
	static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterFront优先于RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CShfeFtdcTraderSpi *pSpi) = 0;
	
	///加载证书
	///@param pszCertFileName 用户证书文件名
	///@param pszKeyFileName 用户私钥文件名
	///@param pszCaFileName 可信任CA证书文件名
	///@param pszKeyFilePassword 用户私钥文件密码
	///@return 0 操作成功
	///@return -1 可信任CA证书载入失败
	///@return -2 用户证书载入失败
	///@return -3 用户私钥载入失败	
	///@return -4 用户证书校验失败
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;

	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(TE_RESUME_TYPE nResumeType) = 0;

	///订阅交易员流。
	///@param nResumeType 交易员流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后交易员流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到交易员流的数据。
	virtual void SubscribeUserTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///设置心跳超时时间。
	///@param timeout 心跳超时时间(秒)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///打开请求日志文件
	///@param pszReqLogFileName 请求日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///打开应答日志文件
	///@param pszRspLogFileName 应答日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;

	///用户输入度量点标识
	virtual int AddMeasureItem(const char *pszMeasureItem) = 0;

	///用户登录请求
	virtual int ReqUserLogin(CShfeFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///用户退出请求
	virtual int ReqUserLogout(CShfeFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CShfeFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CShfeFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///报价录入请求
	virtual int ReqQuoteInsert(CShfeFtdcInputQuoteField *pInputQuote, int nRequestID) = 0;

	///报价操作请求
	virtual int ReqQuoteAction(CShfeFtdcQuoteActionField *pQuoteAction, int nRequestID) = 0;

	///用户密码修改请求
	virtual int ReqUserPasswordUpdate(CShfeFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///执行宣告录入请求
	virtual int ReqExecOrderInsert(CShfeFtdcInputExecOrderField *pInputExecOrder, int nRequestID) = 0;

	///执行宣告操作请求
	virtual int ReqExecOrderAction(CShfeFtdcExecOrderActionField *pExecOrderAction, int nRequestID) = 0;

	///管理报单录入请求
	virtual int ReqAdminOrderInsert(CShfeFtdcInputAdminOrderField *pInputAdminOrder, int nRequestID) = 0;

	///非标组合报单录入请求
	virtual int ReqCombOrderInsert(CShfeFtdcInputCombOrderField *pInputCombOrder, int nRequestID) = 0;

	///放弃执行宣告录入请求
	virtual int ReqAbandonExecOrderInsert(CShfeFtdcInputAbandonExecOrderField *pInputAbandonExecOrder, int nRequestID) = 0;

	///放弃执行宣告操作请求
	virtual int ReqAbandonExecOrderAction(CShfeFtdcAbandonExecOrderActionField *pAbandonExecOrderAction, int nRequestID) = 0;

	///询价录入请求
	virtual int ReqQuoteDemand(CShfeFtdcInputQuoteDemandField *pInputQuoteDemand, int nRequestID) = 0;

	///订阅主题请求
	virtual int ReqSubscribeTopic(CShfeFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///会员资金查询请求
	virtual int ReqQryPartAccount(CShfeFtdcQryPartAccountField *pQryPartAccount, int nRequestID) = 0;

	///报单查询请求
	virtual int ReqQryOrder(CShfeFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///报价查询请求
	virtual int ReqQryQuote(CShfeFtdcQryQuoteField *pQryQuote, int nRequestID) = 0;

	///成交单查询请求
	virtual int ReqQryTrade(CShfeFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///会员客户查询请求
	virtual int ReqQryClient(CShfeFtdcQryClientField *pQryClient, int nRequestID) = 0;

	///会员持仓查询请求
	virtual int ReqQryPartPosition(CShfeFtdcQryPartPositionField *pQryPartPosition, int nRequestID) = 0;

	///客户持仓查询请求
	virtual int ReqQryClientPosition(CShfeFtdcQryClientPositionField *pQryClientPosition, int nRequestID) = 0;

	///合约查询请求
	virtual int ReqQryInstrument(CShfeFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///合约交易状态查询请求
	virtual int ReqQryInstrumentStatus(CShfeFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///保值额度查询
	virtual int ReqQryHedgeVolume(CShfeFtdcQryHedgeVolumeField *pQryHedgeVolume, int nRequestID) = 0;

	///信用限额查询请求
	virtual int ReqQryCreditLimit(CShfeFtdcQryCreditLimitField *pQryCreditLimit, int nRequestID) = 0;

	///非标组合报单查询请求
	virtual int ReqQryCombOrder(CShfeFtdcQryCombOrderField *pQryCombOrder, int nRequestID) = 0;

	///执行宣告查询请求
	virtual int ReqQryExecOrder(CShfeFtdcQryExecOrderField *pQryExecOrder, int nRequestID) = 0;

	///放弃执行宣告查询请求
	virtual int ReqQryAbandonExecOrder(CShfeFtdcQryAbandonExecOrderField *pQryAbandonExecOrder, int nRequestID) = 0;

	///普通行情查询请求
	virtual int ReqQryMarketData(CShfeFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///交易所公告查询请求
	virtual int ReqQryBulletin(CShfeFtdcQryBulletinField *pQryBulletin, int nRequestID) = 0;

	///主题查询请求
	virtual int ReqQryTopic(CShfeFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///合约价位查询
	virtual int ReqQryMBLMarketData(CShfeFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID) = 0;

	///信息查询
	virtual int ReqQryInformation(CShfeFtdcQryInformationField *pQryInformation, int nRequestID) = 0;

	///汇率查询请求
	virtual int ReqQryExchangeRate(CShfeFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID) = 0;
protected:
	~CShfeFtdcTraderApi(){};
};

#endif
