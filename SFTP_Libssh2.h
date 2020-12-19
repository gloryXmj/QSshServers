#pragma once

#include <string>
#include <atomic>

/*
功能：SFTP协议的文件传输功能
最后更新日期：2014-5-17
简介：借助Libssh2库很容易实现sftp,ssh2客户端，这里给出
	  如何实现Sftp客户端的代码
测试环境:Windows 8.1 64bit、Visual Studio 2013 Professional SP1
	   OpenSSL 1.0.1g、zlib-1.2.8、libssh2  1.4.3
	   Win32控制台项目
注意：动态链接需要把“libssh2.dll”文件复制到当前项目路径下
说明：原来的代码支持多线程，从应用程序抽出来的时候简化了，
	 你可以修改代码使它同时支持上传或下载多个文件。
建议:[1]第三方库直接下载源代码自己编译免得库由于编译器版本的
	 不同或设置的不同链接的时候一大堆麻烦。
	 [2]读懂代码根据项目需求作相应修改
补充阅读资料：
《使用libssh2库实现支持密码参数的ssh2客户端》
http://blog.chinaunix.net/uid-24382173-id-229823.html
*/
namespace kagula {
	namespace network {
		int SFTP_Init();
		void SFTP_Exit();

		class SFTP_BKCall
		{
		public:
			/* progress返回值范围[0.0,1.0] */
			virtual void OnProgress(float progress) = 0;
		};

		class SFTP_Libssh2
		{
		public:
            static SFTP_Libssh2* Inst();
			/*
			入口参数使用说明
			ip:	  就填一个IP地址就好了，例如“127.0.0.1”。
			port: 端口，SFTP服务器默认端口为22。
			username:
			password:
			sftppath: 远程路径“/”开头 ，例如“/a.jpg”
			localpath: 本地路径，例如“d:\\temp\\test.jpg”
			strLastError: 错误信息
			出口参数
			返回不等于零，代表失败！
			*/
			int upload(std::string ip, unsigned short port, std::string username,
				std::string password, std::string localpath, std::string remotepath);
			int download(std::string ip, unsigned short port, std::string username,
				std::string password, std::string sftppath, std::string localpath);

			//测试SFTP服务器是否可以链接
			bool IsAbilityConn(std::string ip, unsigned short port, std::string username,
				std::string password);

			//设置回掉函数
			void SetBKCall(SFTP_BKCall *bkCall) { m_bkCall = bkCall; }

			//存放最近的错误信息
			std::string   strLastError;

			//用于停止当前上传或下载线程
			void stop() { m_isBreak.store(true); }
		private:
			SFTP_Libssh2() :m_bkCall(NULL) { m_isBreak.store(false); };//防止直接初始化
			SFTP_Libssh2(const SFTP_Libssh2&);                 //防止拷贝复制
			SFTP_Libssh2& operator=(const SFTP_Libssh2&);      //防止分配(运算符函数的调用)

			SFTP_BKCall  *m_bkCall;
			std::atomic_bool m_isBreak; //带读写保护的bool值
		};
	}
}
