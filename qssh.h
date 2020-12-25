#ifndef QSSH_H
#define QSSH_H


#include <libssh2.h>
#include <libssh2_sftp.h>

#ifdef HAVE_WINSOCK2_H
#include <winsock2.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

#include <sstream>
#include <iomanip>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "libssh2.lib")

#include <QObject>

class QSsh :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString strUserName READ UserName WRITE setUserName NOTIFY UserNameChanged);
    Q_PROPERTY(QString strPassWd READ PassWd WRITE setPassWd NOTIFY PassWdChanged);
    Q_PROPERTY(QString strIpAddress READ IpAddress WRITE setIpAddress NOTIFY IpAddressChanged);
    Q_PROPERTY(int nPort READ Port WRITE setPort NOTIFY portChanged);
public:

    explicit QSsh();
    ~QSsh();
    void InitInfo(const QString &ipAddress , const int &port,
                  const QString &userName  , const QString &passWd);
    //账户登录
    bool Login(const QString &ipAddress = QString::null , const int &port = 22,
               const QString &userName = QString::null  , const QString &passWd = QString::null);
    //账户登出
    bool LoginOut();

    bool uploadFile(const QString &localpath, const QString &remotepath);

    bool download(const QString &sftppath, const QString &localpath);

    bool ShellCommond(const QString &strcmd);

    QString UserName() const
    {
        return m_strUserName;
    }

    QString PassWd() const
    {
        return m_strPassWd;
    }

    QString IpAddress() const
    {
        return m_strIpAddress;
    }

    int Port() const
    {
        return m_nPort;
    }

public slots:
    void setUserName(QString strUserName)
    {
        if (m_strUserName == strUserName)
            return;

        m_strUserName = strUserName;
        emit UserNameChanged(m_strUserName);
    }

    void setPassWd(QString strPassWd)
    {
        if (m_strPassWd == strPassWd)
            return;

        m_strPassWd = strPassWd;
        emit PassWdChanged(m_strPassWd);
    }

    void setIpAddress(QString strIpAddress)
    {
        if (m_strIpAddress == strIpAddress)
            return;

        m_strIpAddress = strIpAddress;
        emit IpAddressChanged(m_strIpAddress);
    }

    void setport(int nport)
    {
        if (m_nPort == nport)
            return;

        m_nPort = nport;
        emit portChanged(m_nPort);
    }

signals:
    void UserNameChanged(QString strUserName);

    void PassWdChanged(QString strPassWd);

    void IpAddressChanged(QString strIpAddress);

    void portChanged(int nport);

private:
    //文件传输
    int SFtp_init();
    void SFtp_Exit();

private:
    QString m_strUserName = QString::null;
    QString m_strPassWd = QString::null;
    QString m_strIpAddress = QString::null;
    int m_nPort = 22;
};

#endif // QSSH_H
