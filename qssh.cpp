#include "qssh.h"

QSsh::QSsh()
{

}

QSsh::~QSsh()
{

}

void QSsh::InitInfo(const QString &ipAddress, const int &port, const QString &userName, const QString &passWd)
{
    m_strIpAddress = ipAddress;
    m_strUserName = userName;
    m_strPassWd = passWd;
    m_nPort = port;
}

bool QSsh::Login(const QString &ipAddress, const int &port, const QString &userName, const QString &passWd)
{
    if(ipAddress.isEmpty() || userName.isEmpty() || passWd.isEmpty())
        return false;

    return true;
}

bool QSsh::LoginOut()
{
    return false;
}

bool QSsh::uploadFile(const QString &localpath, const QString &remotepath)
{
    return false;
}

bool QSsh::download(const QString &sftppath, const QString &localpath)
{
    return false;
}

bool QSsh::ShellCommond(const QString &strcmd)
{
    return false;
}
