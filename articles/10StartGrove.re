= Groveとは

ArduinoやRaspberry Piといった開発ボードを使ったことがあるでしょうか？

これらのボードでは通常、「測定値を入力（インプット）」するボタン、温度計、加速度計といったセンサを使うときや、「処理結果を出力（アウトプット）」するLED、サーボモーター、液晶ディスプレイといったアクチュエータの部品を使うとき、ジャンパーワイヤやブレッドボードで「GPIOピン@<fn>{GPIO}」に接続したり、半田付けなどで接続したりします。

接続には回路の知識が必要だったり、はんだ技術が必要だったりと、電子工作初心者には少々敷居の高い作業になります。

//image[010_GROVE-Cable-Module-NefryBTR2-separated][GroveケーブルとGroveモジュール][scale=0.9]{
//}
Nefry BTでは、上記のような接続もできますが、Groveコネクタを搭載しているのでセンサやアクチュエータを直接刺すだけで手軽に試すことができます！

この章では、Groveを使ってNefry BTでどのようなことができるのか紹介していきます。

== Groveシステムとは

Groveは中国の深圳（シンセン）にあるSeeed Studio社が策定した規格です。

Grove規格対応のセンサやアクチュエータには4ピンを内包したGroveコネクタが取り付けられており、Groveモジュールと呼ばれます。
Nefry BTとGroveモジュールはGroveケーブルで接続できます。

コネクタには凸凹があって決められた向きにしか接続できないので、誤接続の心配がありません。
現在、100種類程のGroveモジュールが販売されており、IoT初心者が使ってみようと思う機能の部品はだいたい揃っています。

 * Seeed Studio: @<href>{https://www.seeedstudio.com}

== Groveモジュールの種類
ハードウェアとの通信方式の違いや、用途の違いでGroveモジュールを分類することができます。

==== デジタルモジュール
//image[011_button-touch-relay][デジタルモジュールの例][scale=0.6]{
//}

入出力する値として0（LOW）か1（HIGH）の2値を使うモジュールです。

 * ボタン
 * タッチセンサ
 * リレー

などがあります。

 * 入力: @<chap>{11GroveInputDigital}
 * 出力: @<chap>{12GroveOutputDigital}

それぞれの章を参考にしてください。

==== PWMモジュール
//image[012_LED-servo][PWMで制御するモジュールの例][scale=0.6]{
//}

PWM（Pulse Width Modulation）はデジタル信号が0になっている時間と1になっている時間の比率を変化させることでモジュールを制御する仕組みです。

 * LEDの明るさの制御
 * サーボモーターの回転角度の制御

などがあります。

@<chap>{13GroveOutputPWM}を参考にしてください。

==== アナログモジュール
//image[013_temp-light-sound][アナログモジュールの例][scale=0.6]{
//}

入出力する値を電圧の高さで表現するモジュールです。

 * 安価な温度計
 * 照度計
 * 音センサ

などがあります。

Nefry BTの場合は、入出力値は0V-3.3Vが0-4095の間の数値で表現されます。

@<chap>{14GroveAnalog}を参考にしてください。

==== I2Cモジュール
I2C（アイ・スクエア・シー）というプロトコルで通信するモジュールです。

 * モータを制御するモータドライバ
 * 高精度な温度湿度センサ
 * 加速度センサ

などがあります。

１つのGroveコネクターに複数のI2Cモジュールを接続できる特徴があります。

@<chap>{15GroveI2C}を参考にしてください。

==== 通信モジュール
他の機器とデータの送受信を行う機能を提供するモジュールです。

 * BLE（Bluetooth Low Energy）
 * GPS
 * NFC

などがあります。

本書では取り扱いません。

== 購入先
Groveモジュールは日本国内の電子部品販売店が扱っているので、実店舗や通販で簡単に購入できます。

代表的な販売店を次に示します。

 * スイッチサイエンス: @<href>{https://www.switch-science.com}
 * 秋月電子通商: @<href>{http://akizukidenshi.com}
 * 千石電商: @<href>{https://www.sengoku.co.jp}
 * マルツ: @<href>{https://www.marutsu.co.jp}

== 情報入手先
Groveモジュールの情報はSeeed Studio社のGroveシステムのWikiページ（@<href>{http://wiki.seeed.cc/Grove_System/}）から取得しましょう。

日本語の情報も検索すると出てくるものもあるので、そちらを参考にするのもよいでしょう！

====[column] Groveモジュールの動作電圧
Groveモジュールの動作電圧は5Vが基本です。Nefry BTのGroveコネクターが供給する電圧は3.3Vなので、すべてのGroveモジュールは動きません。しかし、多くのGroveモジュールが3.3Vに対応しています。

Groveモジュールを購入する際は、必ず販売店のサイトや公式サイトで動作電圧を確かめるようにしましょう。

====[/column]

====[column] Nefry BTのGroveコネクターとGPIOピンの対応関係
Groveシステムは４線のGroveケーブルを内包しています。4本の線の役割は次のとおりです。

//image[T010b-GROVE-Cable-Color][Groveケーブルの色と役割][scale=0.4]{
//}
@<comment>{コラム内の表だとエラーがでるのでここは図で表示する}

信号線は黄色と白の2本ありますが、通常は黄色1本のみが使われます。
I2Cのように信号線が2本必要な場合だけ、黄色と白の2本が使われます。

Nefry BT上の各Groveコネクターにある端子がどのGPIOに接続されているかを記載した図を次に示します。

//image[065_NefryBT-R1-R2-GROVE-GPIO-PIN][Nefry BT R２GroveコネクタのGPIOピン番号対応関係][scale=0.9]{
//}
背景が紺色になっている数字がGPIOピン番号です。

Nefry BT無印とR2で、接続されているGPIOのピン番号は同一ですが、A0、D5、A2といったピン名が異なっているのがわかります。



Nefry BT R2の右下のGroveコネクターの黄色ピンが「A0」ではなく「A1」になっているのがわかります（回路設計のミスです……）。

このためNefry BT R2でGroveコネクターのA0を使用するときは、プログラムでA1を指定しないといけません。

====[/column]

//footnote[GPIO][ボード上に搭載された一般的なピン。General-purpose-inoput/output。]
