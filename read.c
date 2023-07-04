#include <unistd.h>
#include <fcntl.h> // 追加
int main() {
    int fd = open("filename.txt", O_RDONLY);
;
    char buffer[1024];
    ssize_t bytesRead;

    bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        // 読み込んだデータを処理する
    } else if (bytesRead == 0) {
        // ファイルの終端に達した場合の処理
    } else {
        // エラーが発生した場合の処理
    }

    return 0;
}
