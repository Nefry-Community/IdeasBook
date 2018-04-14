# センサデータを「Ambient」に送り、グラフ化する

NefryにセンサとLCDをつけるとセンサデータを確認できます。しかし遠くにあるセンサのデータを確認したり、何ヶ月もの期間のデータを蓄積して比較したりするには、データをクラウドに送った方が便利です。IoTデータを扱うクラウドサービスはいくつかあります。この章では、IoTデータ可視化サービス「[Ambient](https://ambidata.io)」でNefryのデータを扱う例を紹介します。

## Ambientの概要

Ambientは簡単に使えるIoTデータ可視化サービスです。NefryなどのマイコンからセンサデータをAmbientに送ると、Ambientはそれを受信して、蓄積し、グラフ化します。細かな設定などをしなくても、送ったデータをリタルタイムにグラフ化してくれます。作ったセンサ端末の動作確認からデータの長期的な傾向の把握まで、幅広く便利に使えます。

![概要図](https://ambidata.io/structure.jpg)

## Ambientを使う準備

### ユーザー登録
Ambientを使うには、まず最初にユーザー登録します。Ambientの基本部分は無料で使えます。[Ambientのユーザー登録ページ](https://ambidata.io/usr/signup.html)でメールアドレスとパスワードを入力すると、入力したメールアドレスに確認メールが送られます。メール中のURLをクリックするとユーザー登録は完了です。しばらく待ってもメールが来ない場合は、迷惑メールフォルダを確認してください。そこにもなければ、お手数ですが、もう一度ユーザー登録をお願いします。

### チャネル生成
ユーザー登録してAmbientにログインすると、チャネル一覧ページが現れます。 マイコンからAmbientにデータを送る際は「チャネル」を指定して送ります。 最初はチャネルがないので、チャネル一覧ページには「チャネルを作る」ボタンがあるだけです。「チャネルを作る」ボタンを押すとチャネルが生成され、 作られたチャネルの情報が表示されます。データを送る時にはチャネルIDとライトキーを使います。

![チャネル一覧ページ](https://ambidata.io/createChannel.jpg)

## Nefryのプログラム

データをAmbientに送信するには、setup()関数の中でチャネルIDとライトキーを指定してAmbientの初期化をおこないます。指定したIDのチャネルにデータを送る準備です。ライトキーはパスワードのようなもので、正しいライトキーを指定した場合だけ、そのチャネルにデータを送ることができます。

```cpp
nefryAmbient.begin(channelId, "writeKey");
```

Ambientは一つのチャネルに最大8種類のデータを送ることができます。例えば温度データと湿度データを一つのチャネルに送れます。1番目のデータを温度、2番目のデータを湿度というように決めて送ります。決め方は自由です。具体的には次のように1番目のデータとして温度をセットし、2番目のデータとして湿度をセットします。

```cpp
nefryAmbient.set(1, temp);
nefryAmbient.set(2, humid);
nefryAmbient.send();
```

データがint型、float型であれば直接set()でセットできます。データの桁数などを制御したければご自分で文字列形式に変換し、パケットにセットします。データをパケットにセットしたら、send()で送信します。

プログラムは次のようになります。

```cpp
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
    Serial.begin(115200);
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
```

channelIdとwriteKeyにAmbientで先程作ったチャネルのIDとライトキーを設定します。プログラムをビルドしてNefryに書き込むと、温度、湿度が測定され、Ambientに送信され、グラフ化されます。Ambientのチャネルページを見ると、次のようにNefryから送った温度と湿度のデータを確認できます。

![チャネルページ](https://ambidata.io/channelPage.jpg)

### データ送信間隔

Ambientの最短のデータ受信間隔は5秒ですので、5秒以上の間を空けてデータを送ってください。また、1日に受信できる最大数は3,000件です。1回の送信に例えば3種類のデータを送ったとしても、件数は1件です。1日中連続してデータを送信するには約30秒以上の間を空けてください。実際には、測定したい物の特性に合わせて適度な間隔を選ぶのがいいです。例えば室内や外の気温や湿度であれば、普通それほど急激には変化しないので、5分から10分程度の間隔で十分でしょう。
