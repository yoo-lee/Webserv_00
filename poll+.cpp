#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

int main() {
    int fd1 = open("1.txt" ,O_RDONLY);
	int fd2 = open("2.txt" , O_RDONLY);

    struct pollfd fds[2];
    int timeout = 5000; // タイムアウト時間（ミリ秒）

    fds[0].fd = fd1;
    fds[0].events = POLLIN; // 読み取り可能イベントを監視

    fds[1].fd = fd2;
    fds[1].events = POLLOUT; // 書き込み可能イベントを監視

    int readyDescriptors = poll(fds, 2, timeout);
    if (readyDescriptors > 0) 
	{
        // イベントが発生したファイルディスクリプタの処理
        for (int i = 0; i < 2; i++) {
            if (fds[i].revents & POLLIN) {
                // 読み取り可能イベントが発生した場合の処理
            std::cout << "File descriptor " << fds[i].fd << " is ready for reading." << std::endl;
            }
            if (fds[i].revents & POLLOUT) {
                // 書き込み可能イベントが発生した場合の処理
                std::cout << "File descriptor " << fds[i].fd << " is ready for writing." << std::endl;
            }
        }
    } else if (readyDescriptors == 0) {
        // タイムアウト発生時の処理
        std::cout << "Timeout occurred." << std::endl;
    } else {
        // エラー発生時の処理
        std::cerr << "Failed to poll file descriptors." << std::endl;
    }

    return 0;
}

// poll関数の戻り値は以下のような状況で変化します：

// 監視対象のいずれかのファイルディスクリプタにイベントが発生した場合：戻り値はイベントが発生したファイルディスクリプタの数（0 より大きい値）
// タイムアウト時間が経過し、イベントが発生しなかった場合：戻り値は 0
// poll関数の呼び出し中にエラーが発生した場合：戻り値は -1
