// poll関数は、POSIX標準で定義されている関数であり、I/Oマルチプレキシングを実現するために使用されます。以下はpoll関数の定義です：
#include <iostream>
#include <sys/poll.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
// struct pollfd
// {
//     int fd;       // 監視するファイルディスクリプタ
//     short events; // 監視するイベント
//     short revents; // 発生したイベント (戻り値で設定される)
// };

int poll(struct pollfd *fds,nfds_t nfds,int timeout)
{
	
}
// つまり、poll とはpollfd で指定された、pollfd つまりfd とeventを管理するためにfd の要素数
// およびfd の番号を管理する？

int main ()
{
	int fd1 =  open("1.txt", 1);
	int fd2 =  open("2.txt", 1);

	struct pollfd fds[2];
	// fds: struct pollfd型の配列へのポインタです。
	// 各要素は監視するファイルディスクリプタ
	// とその待機イベントを指定します。

	fds[0].fd = fd1;
	fds[0].events = POLLIN;
	
	// nfds: fds配列の要素数です。

	// timeout: 待機する時間をミリ秒単位で指定します。timeoutが0の場合、
	int timeout = 5000;
}

// poll関数は、指定されたファイルディスクリプタ（fd）に対して発生したイベントに応じて必要な処理を行うための
// 制御を戻します。具体的な処理はアプリケーションやプログラムの要件によって異なりますが、一般的な例としては以下のような処理が考えられます：
// ファイルディスクリプタが読み込み可能な状態（POLLINイベント）である場合、データの読み込みや受信処理を行います。たとえば、ソケットからのデータの受信やファイルの読み込みなどです。
// ファイルディスクリプタが書き込み可能な状態（POLLOUTイベント）である場合、データの書き込みや送信処理を行います。たとえば、ソケットへのデータの送信やファイルへの書き込みなどです。
// ファイルディスクリプタがエラー状態（POLLERRイベント）である場合、エラー処理を行います。たとえば、ソケットの接続が切断された場合やファイルのオープンに失敗した場合などです。
// その他のイベントに応じて、アプリケーション固有の処理を行います。たとえば、ファイルディスクリプタに対する特定のイベントが発生した場合に特定の処理を行うなどです。
// 上記は一般的な例ですが、実際の処理はプログラムの要件や設計によって異なります。poll関数は、イベントが発生したファイルディスクリプタに対して適切な処理を行うことで、非同期な入出力処理やイベント駆動型のプログラミングを実現するための手段として利用されます。

// 即座に戻ります。-1の場合、無期限に待機します。

// poll関数は呼び出し元をブロックし、指定されたファイルディスクリプタのいずれかが待機イベントを発生させるまで待機します。待機イベントが発生すると、fds配列の対応する要素のreventsフィールドが更新され、発生したイベントが示されます。
// poll関数は、複数のファイルディスクリプタを同時に監視するために使用され、非同期なI/O処理やマルチクライアントサーバーなどのシナリオで便利です。