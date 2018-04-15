= センサーデータを「Ambient」に送り、グラフ化する

この章では、Nefryにセンサーを繋いで取得したセンサーデータを簡単に可視化できるサービス「Ambient（@<href>{https://ambidata.io}）」を紹介していきます！

== Ambientの概要

Ambientは簡単に使えるIoTデータ可視化サービスです。

//image[structure][概要図][scale=0.8]{
//}

NefryなどのマイコンからセンサーデータをAmbientに送ると、Ambientはそれを受信して、蓄積し、グラフ化します。
細かな設定などをしなくても、送ったデータをリタルタイムにグラフ化してくれるのがとても便利です！

Ambientがあれば、作ったセンサー端末の動作確認からデータの長期的な傾向の把握まで、幅広い用途に使えます。

== Ambientを使う準備

=== ユーザー登録

Ambientを使うためにユーザー登録します。Ambientの基本部分は無料で使えます。

「Ambientのユーザー登録ページ（@<href>{https://ambidata.io/usr/signup.html}）」でメールアドレスとパスワードを入力すると、入力したメールアドレスに確認メールが送られます。

メール中のURLをクリックするとユーザー登録は完了です。
しばらく待ってもメールが来ない場合は、迷惑メールフォルダを確認してください。

そこにもなければ、お手数ですがもう一度ユーザー登録をお願いします。

=== チャネル生成

//image[createChannel][チャネル一覧ページ][scale=0.8]{
//}

ユーザー登録してAmbientにログインすると、チャネル一覧ページが表示されます。

NefryからAmbientにデータを送る際は「チャネル」を指定して送ります。

最初はチャネルがないので、チャネル一覧ページには「チャネルを作る」ボタンがあるだけです。
「チャネルを作る」ボタンを押すとチャネルが生成され、 作られたチャネルの情報が表示されます。

データを送る時にはチャネルIDとライトキーを使います。

== プログラム

Ambientでは一つのチャネルに最大8種類のデータを送ることができます。

今回のプログラムでは1番目のデータを温度、2番目のデータを湿度というように決めて送ります。

channelIdとwriteKeyにAmbientで先ほど作ったチャネルのIDとライトキーを入れ込みます。

プログラムをビルドしてNefryに書き込むと、温度、湿度が測定され、Ambientに送信＆グラフ化されます。
書き込み後Ambientのチャネルページを見ると、Nefryから送った温度と湿度のデータを確認できるはずです。

//emlist{
/*
 * Nefryと「Grove temperature and humidity sensor pro」を使い
 * 温度、湿度データをAmbientに送信し、グラフ化する
 */
#include "DHT.h"
#include <NefryAmbient.h>  // Ambientを扱うためのヘッダファイル

#define DHTPIN A1
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

NefryAmbient nefryAmbient; // Ambientのオブジェクト

void setup()
{
    Serial.println("DHT22 -> Ambient");

    dht.begin();
    nefryAmbient.begin(channelId, "writeKey"); // チャネルIDとライトキーで初期化する
}

void loop()
{
    float temp = dht.readTemperature(); // センサーから温度を読む
    float humid = dht.readHumidity();   // センサーから湿度を読む

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(temp) || isnan(humid)) {
        delay(100);
        return;
    }
    Serial.printf("temp: %.1f, humid: %.1f\r\n", temp, humid);
    nefryAmbient.set(1, temp);  // 温度データを1番目のデータとしてセットする
    nefryAmbient.set(2, humid); // 湿度データを2番目のデータとしてセットする
    nefryAmbient.send();        // データをAmbientに送る

    delay(30000);
}
//}

=== プログラム説明

データをAmbientに送信するには、@<code>{nefryAmbient.begin(channelId, "writeKey");}関数でチャネルIDとライトキーを指定してAmbientライブラリの初期化をおこないます。

ライトキーはパスワードのようなもので、チャネルIDとライトキーを正しく指定した場合だけ、そのチャネルにデータを送ることができます。

//emlist{
nefryAmbient.set(1, temp);
nefryAmbient.set(2, humid);
nefryAmbient.send();
//}

データがint型、float型であれば直接@<code>{set()}でセットできます。
データの桁数などを制御したければご自分で文字列形式に変換し、パケットにセットします。

データをパケットにセットしたら、@<code>{send()}で送信します。


====[column] データ送信間隔について
Ambientの最短のデータ受信間隔は5秒ですので、5秒以上の間を空けてデータを送ってください。

また、1日に受信できる最大数は3,000件です。

1日中連続してデータを送信するには約30秒以上の間を空けてください。

実際には、測定したい物の特性に合わせて適度な間隔を選びましょう。
室内や外の気温や湿度であれば、普通それほど急激には変化しないので、5分から10分程度の間隔で十分です。
====[/column]

=== 動作結果

//image[channelPage][チャネルページ][scale=0.8]{
//}

このようなグラフを見ることができるはずです。

Ambientには、グラフの公開機能や画像の添付などここで紹介しきれない機能がいろいろとあるので、Ambientの公式サイトをぜひご覧ください。
