= I2C温度・湿度センサーモジュール
I2C接続の温度・湿度センサー（SHT31）を使ってみましょう。

//image[400-GROVE-MODULE-SHT31][Grove温度・湿度センサー(SHT31)][scale=0.4]

 * Grove温湿度センサー（SHT31） https://www.switch-science.com/catalog/2853/

I2C接続ではSCLとSDAという2本の信号線を使います。
Nefry BT無印とNefry BT R2のどちらもdefault設定ではGrove D0コネクターに
SCLとSDAが接続されいて、SCLは黄色線、SDAは白線です。

//image[290-NefryBT-R1-GROVE-GPIO-I2C-PIN][Nefy BT無印のI2C接続コネクター][scale=0.7]
//image[300-NefryBT-R2-GROVE-GPIO-I2C-PIN][Nefy BT R2のI2C接続コネクター][scale=0.7]

SCLとSDAが接続されるコネクターはプログラムで変更可能です。変更方法は後述します。

== I2C温度・湿度センサーモジュールのプログラム
Seeed Studio社が公開しているプログラムをそのまま使ってみます。
Seeed Studio社のGrove WikiのSHT31ページ（http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/）
//image[410-WEB-SeeedWiki-SHT31][Seeed Studio社のGrove Wikiページ][scale=0.5]
の下の方に次のような使い方の説明が記載されています。
//image[420-WEB-SeeedWiki-SHT31-Library][Libraryへのリンク][scale=0.5]
「library here」のhereをクリックするとSeeed Studio社のGitHubページが開きます。
//image[430-WEB-Seeed-GitHub-SHT31][Seed Studio社のGitHubページ][scale=0.9]
ページ右上の「Clone or download」というプルダウンメニューをクリックして、プログラム一式をダウンロードします。
ダウンロードしたプログラムのフォルダー構成は次のようになっています。
//image[440-WEB-Seeed-GitHub-SHT31-File-Tree][温度・湿度センサープログラムのフォルダー構成][scale=0.9]
「example」というフォルダーを、Nefry BTのプログラムを置いているご自身のフォルダにコピーします。
次に、「SHT31.cpp」と「SHT31.h」をそのフォルダにコピーします。コピー先のフォルダは次の図のようになります。
ファイルが３つコピーされていることを確認してください。
//image[450-My-SHT31-example-folder][コピーしたexampleフォルダー][scale=0.9]

「example.ino」ファイルを開くと、Arduino IDEの画面が開きます。タブが3つあり、フォルダー内のファイルが
タブとして表示されていることを確認してください。
//image[460-IDE-SHT31-Original][SHT31プログラムのArduino IDE画面][scale=0.9]

Nefry BT用にプログラムを変更を行います。変更は2箇所だけです。

 * 冒頭に @<code>{#include <Nefry.h>}を追加します。
 * @<code>{setup()}ルーチン内にある@<code>{Serial.begin(9600);}と@<code>{while(!Serial);}をコメントアウトします。
変更後のプログラムはこうなります。

//image[470-IDE-SHT31-Nefry][変更後のSHT31プログラム][scale=0.9]

//list[NefryBT_GROVE_SHT31][I2C温度・湿度計のプログラム]{
#include <Nefry.h>
#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"

SHT31 sht31 = SHT31();

void setup() {
//  Serial.begin(9600);
//  while(!Serial);
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

プログラムを実行すると、シリアルモニターに測定結果が表示されます。

//image[480-MONITOR-SHT31][SHT31プログラムのシリアルモニター表示例][scale=0.9]


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
