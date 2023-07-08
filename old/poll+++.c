struct pollfdとnfds_tはpoll関数の引数として関連しています。

struct pollfdは、poll関数に渡されるファイルディスクリプタと関連する
情報を保持する構造体です。この構造体は次のように定義されています：


struct pollfd 
{
    int fd;        // ファイルディスクリプタ
    short events;  // 待機するイベント
    short revents; // 実際に発生したイベント
};

; nfds_tは、poll関数に渡されるstruct pollfdの数を表す型です。
; nfds_tはC言語の型であり、構造体ではありません。
; 正確には、nfds_tは符号なし整数型（通常はunsigned int）です
; 通常、この値は配列内のstruct pollfdの要素数として指定されます。
; 具体的には、fdsはstruct pollfdの配列を指すポインタであり、
; nfdsは配列内のstruct pollfdの要素数を示す型です。poll関数は、fdsで指定されたファイルディスクリプタのイベントを待機し、その結果を各struct pollfdのreventsメンバに格納します。nfdsはfdsの要素数を指定するため、poll関数は配列内のすべての要素に対してイベントの待機と結果の格納を行います。