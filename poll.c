#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>

struct pollfd 
{
    int fd;       // 監視するファイルディスクリプタ
    short events; // 監視するイベント
    short revents; // 発生したイベント (戻り値で設定される)
};

struct pollfd
{
	int fd;
	short events;
	short revents;
};

int main ()
{
	struct pollfd fds[2];
	int timeout = 1000;

	fds[0].fd = fd1;
}

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
    if (readyDescriptors > 0) {
        // イベントが発生したファイルデ
	}
}