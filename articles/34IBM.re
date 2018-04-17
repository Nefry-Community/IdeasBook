= IBM Watson IoT Platformにつないでみる

この章では、NefryBTをIBM Watson IoT Platform （QuickStart） にデータ送信し可視化します。

== 今回の仕組み

//image[34IBM_01][今回の仕組み][scale=0.8]{
//}

このようにNefry BTの内蔵スイッチを押すとランダム値を IBM Watson IoT Platform （QuickStart） にデータ送信し、可視化をします。


== PubSubClientのダウンロード

IBM Watson IoT Platform ではMQTTで接続する必要があります。

MQTT通信をするために、今回はPubSubClientライブラリを採用します。

@<href>{https://github.com/knolleary/pubsubclient,PubSubClientライブラリ}

//image[34IBM_02][PubSubClientライブラリのGitHub][scale=0.8]{
//}

こちらをダウンロードしてきます。

//image[34IBM_03][ZIP形式のライブラリをインストール][scale=0.8]{
//}

@<tt>{スケッチ} >@<tt>{ライブラリをインクルード} > @<tt>{ZIP形式のライブラリをインストール} でPubSubClientライブラリをインストールします。

これでPubSubClientライブラリが使えるようになります。

== IBM Watson IoT Platform の準備（QuickStart）

IBM Watson IoT PlatformのQuickStartページでデータを待ちます。

@<href>{https://quickstart.internetofthings.ibmcloud.com/#/,IBM Watson IoT Platform}

//image[34IBM_04][QuickStartページ][scale=0.8]{
//}

IBM Watson IoT PlatformのQuickStartページにアクセスします。

//image[34IBM_05][デバイスIDを入力][scale=0.8]{
//}

IBM ご利用条件に同意します をチェックして、デバイスIDには今回使う @<tt>{NefryBT_123456789} を記入して待っておきます。

デバイスIDは後ほど設定するNefry BTのプログラムで設定するデバイスIDと一致させるので間違えないようにしましょう。

== プログラムを書き込みます


以下をNefry BTに書き込みます。


//emlist{
#include <Nefry.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

// 接続先のIBM Watson IoT Platform
#define ORG "quickstart"
// デバイスタイプはnefrybtで
#define DEVICE_TYPE "nefrybt"
// デバイスIDは自由な値で
#define DEVICE_ID "NefryBT_123456789"
// QuickStartでは使わないが
// 独自に作成したIBM Watson IoT Platformインタンスにつなぐ場合は使用する設定です
#define TOKEN "<yourDeviceToken>"

// 実際の接続するための設定群
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

// WiFiClient準備
WiFiClient wifiClient;

// MQTT接続のための準備
// QuickStartのため server , port だけ。あとはwifiClient紐付け。
PubSubClient client(server, 1883, wifiClient);

void setup() {
  // SW有効化
  Nefry.enableSW();
  // Serial指定
  Serial.begin(115200);
}

void loop() {
  // MQTT再接続処理
  if (!!!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!!!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }

  // スイッチを押すとランダム値を送る
  if (Nefry.readSW()) {
    // IBM Watson IoT Platformに合わせてデータ構造 data = ランダム値
    String payload = "{ \"d\" : {\"data\":" + String(random(0,100), DEC) + "} }";
    // データ送信
    Serial.print("Sending payload: ");
    Serial.println(payload);
    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
  }
}
//}

== 動かしてみる

Wi-Fiの接続を確認したうえで、内蔵スイッチを何度か押して、さきほど、表示していたIBM Watson IoT Platformの画面を確認してみましょう。

//image[34IBM_06][ボタンを押した時のグラフの様子][scale=0.8]{
//}

このようにデータが送信されています！

//image[34IBM_07][可視化されたグラフ][scale=0.8]{
//}

送信した時間やデータの内容など簡単に確認することができます。

== 広げていこう

IBM Watson IoT Platform （QuickStart） にデータ送信と可視化できました。

IBM Watson IoT Platformに接続できると、IBM Cloudのさまざまなサービスに接続することができるため、IoTをきっかけに出来ることが広がります。

たとえば、IBM Watson IoT Platformをきっかけにしてデータベースにデータを保存したのちに分析したり、Watson Text to Speechと連携してセンサーの数値に応じた音声を再生するなどさまざまなことができます。

IBM Watson IoT Platform （QuickStart）を試したあとは、IBM Cloudライト・アカウントに登録してみましょう。

無料の範囲内でもいろいろなサービスが試すことができます。
