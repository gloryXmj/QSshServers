#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "SFTP_Libssh2.h"

#include "shell_libssh2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ///下面的代码只要在进程初始化的时候执行
    qssh::network::SFTP_Init();

    ///测试SFTP链接
    qssh::network::SFTP_Libssh2* client = qssh::network::SFTP_Libssh2::Inst();
    std::string ip = "192.168.0.109";
    uint16_t port = 22;
    std::string usr = "xmj";
    std::string pwd = "xmj0503";
    if (false == client->IsAbilityConn(ip, port, usr, pwd))
    {
        std::cout << client->strLastError << std::endl;
        return ;
    }

    ///测试文件上传,d:\\temp\\a.html
    if (0 != client->upload(ip, 22, usr, pwd, "C:\\Users\\xmj\\Desktop\\2048.zip", "/home/xmj/2048.zip"))
    {
        std::cout << "Error:" << client->strLastError << std::endl;
    } else
    {
        std::cout << client->strLastError << std::endl;
    }

    ///测试文件下载
    if (0 != client->download(ip, 22, usr, pwd, "/home/xmj/Workspace/Shell/Exp.sh","C:\\Users\\xmj\\Desktop\\Exp.sh" ))
    {
        std::cout << "Error:" << client->strLastError << std::endl;
    }
    else
    {
        std::cout << client->strLastError << std::endl;
    }

    ///进程准备结束，释放资源的时候，运行下面的代码
    qssh::network::SFTP_Exit();

    qssh::Shell::Shell_Libssh2 ssh_shell;
    std::cout << ssh_shell.ShellCmd(ip,port,usr,pwd,"ls /home/xmj") << std::endl;
    std::cout << ssh_shell.ShellCmd(ip,port,usr,pwd,"ls -al /home/xmj") << std::endl;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

