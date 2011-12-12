//////////////////////////////////////////////////////////////////////////
// FileName:	CardReaderClientDll.h
// Creator:		icejoywoo
// Date:		2011.12.03
// $Revision: 37 $
// Comment: 客户端操作读卡器的接口定义
//////////////////////////////////////////////////////////////////////////

#ifdef CARDREADERCLIENTDLL_EXPORTS
#define CARDREADERCLIENTDLL_API __declspec(dllexport)
#else
#define CARDREADERCLIENTDLL_API __declspec(dllimport)
#endif

#include <WINSOCK2.H> // win socket

#include "SmartComString.h"

// This class is exported from the CardReaderClientDll.dll
// class CARDREADERCLIENTDLL_API CCardReaderClientDll {
// public:
// 	CCardReaderClientDll(void);
// 	// TODO: add your methods here.
// };
// 
// extern CARDREADERCLIENTDLL_API int nCardReaderClientDll;
// 
// CARDREADERCLIENTDLL_API int fnCardReaderClientDll(void);

/**
 * @brief 读卡器(deprecated, 客户要求必须是函数式的API)
 */
// class CARDREADERCLIENTDLL_API CardReader {
// public:
// 	CardReader(int cardId, char* userId);
// 	virtual ~CardReader(void);
// 	/**
// 	 * @brief 获取读卡器
// 	 * @param	None
// 	 * @return  
// 	 *	0: 成功
// 	 */int GetReader(void);
// 
// 	/**
// 	 * @brief 释放读卡器
// 	 * @param	None
// 	 * @return  
// 	 *	0: 成功
// 	 */
// 	int ReleaseReader(void);
// private:
// 	/// 读卡器连接到服务器的socket
// 	SOCKET server; 
// 	/// 读卡器号
// 	int cardId;
// 	/// 用户标识符
// 	char* userId;
// };

// 修改记录:
// TODO: 将读卡器号由cardId改为readerId

/**
 * @brief 保存读卡器id和与服务器连接的socket
 */
typedef struct _Reader
{
	SOCKET s;
	int readerId;
} Reader;

/**
 * @brief 初始化客户端的服务器全局配置, Reader依赖这些配置建立与服务器的通信
 * @param
 *	serverIp	服务器ip
 *	serverPort	服务器端口号
 * @return 
 *	成功返回0
 */
CARDREADERCLIENTDLL_API int InitClient(char* serverIp, int serverPort);

/**
 * @brief 清理客户端, 在使用完读卡器的最后调用
 * @param None
 * @return 
 *	成功返回0
 */
CARDREADERCLIENTDLL_API int CleanUpClient();

/**
 * @brief 获取读卡器
 * @param
 *	reader			输出参数, 读卡器
 *	socketTimeout	socket连接的超时
 *	customTimeout	应用本身需要的延时
 * @return  
 *	0: 成功
 */
CARDREADERCLIENTDLL_API int GetReader(Reader* reader, long socketTimeout, long customTimeout);

/**
 * @brief 释放读卡器
 * @param
 *	reader			读卡器
 * @return  
 *	0: 成功
 */
CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader);

/**
 * @brief 读取终端设备id号和机号
 * @param 
 *	reader			读卡器, 使用reader来和服务器通信
 *	devID			输出参数, 存放7字节id号
 *	devIDBufLen		devID缓冲的长度
 *	readerId		输出参数, 1字节机号
 * @return 
 *	 0: 读取成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 读取失败
 */
CARDREADERCLIENTDLL_API int GetDevIDAndReaderId(Reader reader, char* devID, int devIDBufLen, int& readerId);

/**
 * @brief 通过终端设备ID号给终端设备设置机号
 * @param
 *	reader		读卡器, 使用reader来和服务器通信
 *	devID		存放7个字节的设备ID
 *	readerId	要设置的机号
 * @return
 *	 0: 设置成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 设置失败
 */
CARDREADERCLIENTDLL_API int SetReaderIdByDevID(Reader reader, const char* devID, int readerId);


/**
 * @brief 读取程序版本和终端类型
 * @param
 *	reader			读卡器
 *	appVer			程序版本
 *	appVerlen		存放appVersion的缓冲长度
 *	devType			终端类型
 *	devTypeLen		存放终端类型的缓冲长度
 * @return
 *	 0: 读取成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 读取失败
 */
CARDREADERCLIENTDLL_API int GetAppVerAndDevType(Reader reader, char* appVer, int appVerlen, char* devType, int devTypeLen);

/**
 * @brief 复位终端设备
 * @param
 *	readerId	机号
 * @return
 *	 0: 成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 */
CARDREADERCLIENTDLL_API int ResetDev(int readerId = 255);

/** 
 * @brief 获取读卡接口芯片ID号
 * @param
 *	chipID		接口芯片ID
 *	chipIDLen	存放接口芯片ID的缓存长度
 *	readerId		机号
 * @return 
 *	 0: 成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 读取失败
 */
CARDREADERCLIENTDLL_API int GetChipID(char* chipID, int chipIDLen,int readerId = 255);

/**
 * @brief 检测A卡（大卡）座与B卡（SIM卡）座是否有卡
 * @param
 *	readerId	机号
 *	cardA	出口参数, 1,A卡座有卡；0，A卡座无卡
 *	cardB	出口参数, 1,B卡座有卡；0，B卡座无卡
 * @return 
 *	 0: 检测成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 检测失败
 */
CARDREADERCLIENTDLL_API int IsCardReady(int& cardA,int& cardB,int readerId = 255);

/**
 * @brief 卡片复位应答
 * @param
 *	card		1:A卡，2：B卡,默认选择A卡
 *	readerId		机号，默认255
 *	retCode		出口参数, 复位命令的返回值
 *		retCode="F9"：卡座无卡
 *		retCode="FD"：不可识别卡
 *	返回值：
 *	0：通信成功
 *	-1：通信超时错误
 *	-2：通信器无效  
 *	-3: 机号范围错误
 */
CARDREADERCLIENTDLL_API int ResetCard(SmartCom::string& retCode,int card=1,int readerId=255);

/**
 * @brief 卡片操作-APDU
 * @param
 *	apdu		十六进制字符串表示的apdu命令
 *	card		1:A卡，2：B卡,默认选择A卡
 *	readerId		机号，默认255
 *	retCode		出口参数, 执行apdu指令的返回值
 *		retCode="F9"：卡座无卡
 *		retCode="FD"：不可识别卡
 *		retCode="F2"：无效7816命令包
 *		retCode="F0"：没有先给卡进行上电复位
 * @return
 *	 0: 通信成功
 *	-1: 通信超时错误
 *	-2: 通信器无效 
 *	-3: 机号范围错误
 */
CARDREADERCLIENTDLL_API int CardApdu(SmartCom::string& retCode,int card=1,int readerId=255);

/**
 * @brief 卡片下电
 * @param
 *	readerId	机号，默认255
 * @return
 *	 0: 下电成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 下电失败
 */
CARDREADERCLIENTDLL_API int ShutdownCard(int readerId=255);

/**
 * @brief 修改卡通信波特率
 * @param
 *	braudRate	要修改的波特率，只能选如下值：115200，57600，38400，28800，23040，19200，14400，12800，9600
 *	readerId		机号，默认255
 * @return
 *	 0: 修改成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 修改失败
 */
CARDREADERCLIENTDLL_API int ModifyCardBraudRate(int braudRate,int readerId=255);

/**
 * @brief 读卡通信波特率
 * @param
 *	readerId		机号，默认255
 *	braudRate	出口参数, 当前卡的通信波特率
 * @return
 *	 0: 读取成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 读取失败
 */
CARDREADERCLIENTDLL_API int GetCardBraudRate(int& braudRate,int readerId=255);

/**
 * @brief 修改卡片电源
 * @param
 *	power	电源：power=1: 5v，power=2: 3v，power=3: 1.8v
 *	card	1:A卡，2：B卡,默认选择A卡
 *	readerId	机号，默认255
 * @return
 *	 0: 修改成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 修改失败
 */
CARDREADERCLIENTDLL_API int ModifyCardPower(int power,int card=1,int readerId=255);

/**
 * @brief 发送执行批处理APDU命令
 * @param
 *	card	选择执行的卡，card=1为A卡，2为B卡。默认A卡
 *	cmdNum	要执行的指令条数
 *	readerId	机号，默认255
 * @return
 *	 0: 成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 发送失败
 */
CARDREADERCLIENTDLL_API int  ExcuteMulAPDU(int cmdNum,int card=1,int readerId=255);

/**
 * @brief 读批处理二进制脚本文件
 * @param
 *	bytes		要读取的字节数
 *	readerId		机号，默认255 
 *	offset		读取数据的文件偏移地址
 *	strData		出口参数, 读取的转换成十六进制字符串的数据
 * @return
 *	  0: 读取成功
 *	 -1: 通信超时错误
 *	 -2: 通信器无效
 *	 -3: 机号范围错误
 *	 -4: 读取失败
 */
CARDREADERCLIENTDLL_API int GetScriptData(int offset,unsigned char bytes,SmartCom::string& strData,int readerId=255);

/**
 * @brief 下载文件
 * @param
 *	flag		flag=1,下载命令体文件，flag=2，下载命令头文件
 *	fileName	文件名
 *	readerId		机号，默认255 
 * @return
 *	 0: 下载成功
 *	-1: 通信超时错误
 *	-2: 通信器无效 
 *	-3: 机号范围错误
 *	-4: 下载失败
 *	-5: 文件打开失败
 */
CARDREADERCLIENTDLL_API int DownloadFile(int flag,const char* fileName,int readerId=255);

/**
 * @brief 查询执行批处理APDU结果
 * @param
 *	readerId		机号，默认255 
 *	retCode		出口参数, 最后一条指令的返回值 
 *		retCode="F1": 未选定卡或无卡或卡复位失败(卡已失效)，APDU响应超时（或无效的APDU命令）等错误。
 * @return
 *	>=0: 的数：已经执行的命令条数
 *	 -1: 通信超时错误
 *	 -2: 通信器无效 
 *	 -3: 机号范围错误
 */
CARDREADERCLIENTDLL_API int CheckBatchResult(SmartCom::string& retCode,int readerId=255);

/**
 * @brief 对SST25VF016B存储器进行整片擦除
 * @param
 *	readerId	机号，默认255 
 * @return
 *	 0: 擦除成功
 *	-1: 通信超时错误
 *	-2: 通信器无效
 *	-3: 机号范围错误
 *	-4: 擦除失败
 */
CARDREADERCLIENTDLL_API int ClearMem(int readerId=255);