= GroveのI2C（温度・湿度センサーモジュール）

温度・湿度センサー（SHT31）はI2C接続のモジュールです。

//image[400-GROVE-MODULE-SHT31][Grove温度・湿度センサー(SHT31)][scale=0.4]{
//}

 * Grove温湿度センサー（SHT31） @<href>{https://www.switch-science.com/catalog/2853/}

I2C接続ではSCLとSDAという2本の信号線を使います。

Nefry BTでは、Grove D0コネクターにセンサーを繋いで使用します。

== I2C温度・湿度センサー制御ライブラリの入手とセットアップ
Seeed Studio社が公開しているライブラリをセットアップして、プログラム内で使用できるようにします。

//image[410-WEB-SeeedWiki-SHT31][Seeed Studio社のGrove Wikiページ][scale=0.5]{
//}

Seeed Studio社のGrove WikiのSHT31ページ（@<href>{http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/}）に使い方の説明が記載されています。
//image[420-WEB-SeeedWiki-SHT31-Library][Libraryへのリンク][scale=0.9]{
//}

「library here」のhereをクリックするとSeeed Studio社のGitHubページが開きます。

ここからライブラリを取得します。

//image[430-WEB-Seeed-GitHub-SHT31][Seed Studio社のGitHubページ][scale=0.9]{
//}

ページ右上の「Clone or download」というプルダウンメニューをクリックして、zipファイル（Grove_SHT31_Temp_Humi_Sensor-master.zip）をダウンロードします。

zipファイルにはSHT31を使うためのライブラリとサンプルプログラムが含まれています。

//image[500-menu-include-library][ライブラリの取り込み][scale=0.7]{
//}

//image[510-file-chooser][ファイル選択画面][scale=0.7]{
//}

zipファイルをArduino IDEにインストールします。

IDEのメニュー [スケッチ]>[ライブラリをインクルード]>[.ZIP形式のライブラリをインストール...] を選択し、ファイル選択画面で先ほどダウンロードしたzipファイルを指定します。

これでセットアップ完了です！！

== I2C温度・湿度センサーモジュールのプログラム

1秒ごとに温度湿度データをシリアルモニタに送るプログラムになります。

//emlist[NefryBT_GROVE_SHT31][I2C温度・湿度計のプログラム]{
#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"

SHT31 sht31 = SHT31();

void setup() {
  Serial.println("begin...");
  sht31.begin();
}

void loop() {
  float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();
  Serial.print("Temp = ");
  Serial.print(temp);
  Serial.println(" C"); //The unit for  Celsius because original arduino
  Serial.print("Hum = ");
  Serial.print(hum);
  Serial.println("%");
  Serial.println();
  delay(1000);
}
//}

上記のプログラムをNefryに書き込みましょう！

=== 実行結果
このプログラムを実行すると、シリアルモニターに測定結果が表示されます。

//image[480-MONITOR-SHT31][SHT31プログラムのシリアルモニター表示例][scale=0.9]{
//}

温度湿度モジュールと通信して温度と湿度の情報がちゃんと表示されているのが確認できると思います！

====[column] Nefry Libraryのバージョンを上げよう
Nefry BT R2はライブラリのバージョンがV1.2.0以前だとI2C制御部分のプログラムがうまく動作しません。

その修正が入ったライブラリのバージョンをv1.2.1以降にしておきます。

アップデートは次の手順で行います。

 1. Arduino IDEの「ツールメニュー ＞ ボード ＞ ボードマネージャ」を選ぶ
 2. 検索欄にnefryを記入する
 3. 検索結果をクリックするとバージョン選択のプルダウンメニューが現れる
 4. プルダウンメニューから1.2.1を選択する
 5. 更新ボタンをクリックする

//image[370-IDE-BoardManager-Nefry-v121][ボードマネージャーの更新][scale=0.9]{
//}

====[/column]
