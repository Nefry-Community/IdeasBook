
= ThingSpeakにデータを送ってみる


ThingSpeak（https://thingspeak.com/）は、マイコンなどからのセンサーデータを収取し、グラフ化やMATLABを使って分析を行えるだけでなく、Twitterなどの別のサービスへのアクションを行えるサービスです。



//image[thingspeak_top][ThingSpeakのホームページ]{
//}




ThingSpeakにセンサーデータをアップロードするには、まずチャネルを作成する必要があります。



//image[thingspeak_channel_detail][ThingSpeakのチャネル設定]{
//}




チャネルを作るとフィールドの設定ができ、1つのチャネルにつき最大8つのフィールドを持つことができ、それぞれのフィールドに別々のデータをアップロードすることができます。



//image[thingspeak_detail][ThingSpeakのAPIキー]{
//}




Nefry BTからThingSpeakにデータをアップロードする際は、チャネルのIDとライトAPIキーが必要となります。同じチャネルのフィールドであれば、同じライトキーを使うことになります。


//emlist{
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
//}