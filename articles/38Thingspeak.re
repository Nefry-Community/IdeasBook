= ThingSpeakにデータを送ってみる

この章では、NefryからThingSpeakライブラリをつかって、ThingSpeakにデータを送り、それを可視化する方法を紹介します。

//image[thingspeak_top][ThingSpeakのホームページ][scale=0.8]{
//}

ThingSpeak（@<href>{https://thingspeak.com/}）は、マイコンなどからのセンサーデータを収取し、グラフ化やMATLABを使って分析を行えるだけでなく、さらにTwitterや他のWebサービスなどの別のサービスへのアクションを行えるサービスです。

== アカウントをつくろう

//image[createAccount][アカウント作成][scale=0.8]{
//}

サイト上部の「Sign Up」をクリックし、アカウントを作成します。

必要な情報を入力し、アカウントを作成します。

アカウントの登録ができたらログインしましょう！

== チャネルを作成する

ThingSpeakにセンサーデータをアップロードするには、まずチャネルを作成する必要があります。

//image[createChannel][My Channels一覧][scale=0.8]{
//}

ログイン直後、このような画面が出ると思います。
出ない場合は、上の「Channel」から「My Channels」を選ぶと同じ画面が表示されるのでそちらから開きましょう。

「New Channel」をクリックし、チャネルを作成します。

//image[newChannel][チャネル登録][scale=0.8]{
//}

チャネル作成の画面に移動すると、名前を設定する欄があります。

そこに登録名を入力します。下にスクロールすると「Save Channel」とあるのでそれをクリックしてチャネルを登録します。

1つのチャネルにつき最大8つのフィールドがあり、それぞれのフィールドに別々のデータをアップロードすることができます。

//image[thingspeak_detail][ThingSpeakのAPIキー][scale=0.8]{
//}

チャネルができたら、ページ中央に並んだタブの中から「API Keys」をクリックして開きます。

このページでNefryからThingSpeakにセンサーデータを送るのに必要なAPI keyを取得することができます。

Write API Keyという欄に書かれた文字と、先ほど指定した登録名の下にあるチャネルIDを次の章ではNefryに設定していくので覚えておきましょう。

== プログラム

このプログラムはA0ピンにつながれたアナログ入力の値をThingSpeakに送るものになっています。

//emlist{
// ThingSpeakライブラリを使うのに必要
#include <NefryThingSpeak.h>

// ThingSpeakで作成したチャネルのID（数値）とライトキー
#define CHANNEL_ID 447668
#define WRITE_KEY "writeKeyを入力しよう"

void setup() {
  //ThingSpeakの初期設定を行います。WriteKeyも設定します
  NefryThingSpeak.begin(CHANNEL_ID);
  NefryThingSpeak.setWriteAPIKey(WRITE_KEY);
  Nefry.println("ThingSpeak initialized");
}

void loop() {
  // A0ピンのアナログ値を読み取って、ThingSpeakに送信
  // 第一引数はセットしたいフィールド（1〜8）です。
  NefryThingSpeak.writeField(1, analogRead(A0));
  Nefry.println("Data pushed");

  delay(20000);//20秒に一度送信します。
}
//}

ThingSpeakを制御するために@<code>{NefryThingSpeak.h}をincludeします。

まずはセンサーデータを送る前に準備をします。
@<code>{begin()}関数でチャネルの指定をし、@<code>{setWriteAPIKey()}関数でライトAPIキーを設定します。

これでThingSpeakにデータを送る下準備は完了です。

@<code>{writeField()}でデータを送りたいフィールドとデータを指定すると、ThingSpeakにデータが送られます。


== 送ったデータを見てみる


データの可視化は、チャネルの詳細ページから可能です。

//image[thingspeak_add_visualization][ThingSpeakのAPIキー][scale=0.8]{
//}

@<tt>{Add Visualizations}というメニューがあるので、それを押すだけ！

これだけでグラフが表示されます！

//image[thingspeak_visualization][ThingSpeakのAPIキー][scale=0.8]{
//}


簡易的ではありますが、フィールドに送られたデータを簡単に可視化できました。
