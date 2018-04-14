# ThingSpeakにデータを送ってみる
ThingSpeak（https://thingspeak.com/）は、マイコンなどからのセンサーデータを収取し、グラフ化やMATLABを使って分析を行えるだけでなく、Twitterなどの別のサービスへのアクションを行えるサービスです。この章では、NefryからThingSpeakライブラリをつかって、ThingSpeakにデータを送り、それを可視化する方法を紹介します。



![ThingSpeakのホームページ](thingspeak_top)


## チャネルを作成する


ThingSpeakにセンサーデータをアップロードするには、まずチャネルを作成する必要があります。


![ThingSpeakのチャネル設定](thingspeak_channel_detail)


チャネルを作るとフィールドの設定ができ、1つのチャネルにつき最大8つのフィールドを持つことができ、それぞれのフィールドに別々のデータをアップロードすることができます。


![ThingSpeakのAPIキー](thingspeak_detail)



## データを送ってみる


Nefry BTからThingSpeakにデータをアップロードする際は、チャネルのIDとライトAPIキーが必要となります。同じチャネルのフィールドであれば、同じライトキーを使うことになります。


```
// ThingSpeakライブラリを使うのに必要
#include <NefryThingSpeak.h>

// ThingSpeakで作成したチャネルのID（数値）とライトキー
#define CHANNEL_ID 447668
#define WRITE_KEY "1AQGOCTGWAJGVFQN"

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

  delay(20000);
}
```


`NefryThingSpeak.h`をincludeして、`begin()`関数でチャネルの指定をし、`setWriteAPIKey()`関数でライトAPIキーを設定すれば、ThingSpeakにデータを送ることができます。`writeField()`でデータを送りたいフィールドとデータを指定して送信します。


## 送ったデータを見てみる


データの可視化は、チャネルの詳細ページから可能です。


![ThingSpeakのAPIキー](thingspeak_add_visualization)


`Add Visualizations`というメニューがあるので、それを押すだけ。


![ThingSpeakのAPIキー](thingspeak_visualization)


簡易的ではありますが、フィールドに送られたデータを簡単に可視化する事ができました。
