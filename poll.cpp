#include <iostream>
#include <sys/poll.h>
#include <unistd.h>

int main() {
    // ファイルディスクリプタの準備
    int fd = STDIN_FILENO; // 標準入力のファイルディスクリプタ

    // pollfd構造体の準備
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    // poll関数でPOLLINイベントを待機
    int numEvents = poll(fds, 1, -1); // 無制限のタイムアウト

    if (numEvents == -1) {
        std::cerr << "Error in poll" << std::endl;
        return 1;
    }

    if (fds[0].revents & POLLIN) {
        // ファイルディスクリプタから読み取り可能なデータが到着した場合の処理
        char buffer[1024];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            std::cerr << "Error in read" << std::endl;
            return 1;
        }
        // 読み取ったデータの処理などを行う
        std::cout << "Read " << bytesRead << " bytes: " << buffer << std::endl;
    }

    return 0;
}
