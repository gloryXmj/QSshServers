#pragma once
#ifndef SHELL_LIBSSH2_H
#define SHELL_LIBSSH2_H

#include <libssh2.h>
#include <iostream>
namespace qssh {
namespace Shell {
class Shell_Libssh2
{
public:
    Shell_Libssh2();
    int ShellCmd(std::string ipaddress, unsigned short port, std::string username, std::string password, const char *commandline);
private:
    static int waitsocket(unsigned int socket_fd, LIBSSH2_SESSION *session);
    char m_LastPrint[0x4000];
};
}
}


#endif // SHELL_LIBSSH2_H
