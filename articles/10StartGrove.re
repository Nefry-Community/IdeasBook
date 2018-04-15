= Groveとは

ArduinoやRaspberry Piといったハードウェアでは、ボタン、温度計、加速度計といった「測定値を入力」するセンサーやLED、サーボモーター、液晶ディスプレイといった「処理結果を出力」するアクチュエーターの部品をジャンパーワイヤやブレッドボード、半田付けなどで接続します。

これは、電子工作初心者には少々敷居の高い作業になります。

//image[010_GROVE-Cable-Module-NefryBTR2-separated][GroveケーブルとGroveモジュール][scale=0.9]{
//}

Nefry BTでは、上記のジャンバーワイヤで接続もできますが、特徴としてGroveコネクターがあるのでセンサーやアクチュエーターを手軽に接続して試すことができます！

この章では、Groveというモジュールを使ってNefryでどのようなことができるのか紹介していきます。

== Groveシステムとは

Groveは中国の深圳（シンセン）にあるSeeed Studio社が策定した規格です。

センサーやアクチュエーターには4ピンのGroveコネクターが取り付けられており、Groveモジュールと呼ばれます。
NefryとGroveモジュールは4線のGroveケーブルで接続します。

コネクターには凸凹があって決められた向きにしか接続できないので、誤接続の心配がありません。
現在、Seeed Studio社から100種類程のGroveモジュールが販売されており、IoT初心者が使ってみようと思う部品はだいたい揃っています。

 * Seeed Studio @<href>{https://www.seeedstudio.com}

== 購入先

Groveモジュールは日本国内の電子部品販売店が扱っているので実店舗や通販で簡単に購入できます。

代表的な販売店を次に示します。

 *スイッチサイエンス @<href>{https://www.switch-science.com}
 *秋月電子通商 @<href>{http://akizukidenshi.com}
 *千石電商 @<href>{https://www.sengoku.co.jp}
 *マルツ @<href>{https://www.marutsu.co.jp}

== 情報入手先

Groveモジュールの情報はインターネットで比較的簡単に手に入ります。
日本国内の販売店のサイトにモジュールの仕様やサンプルプログラムが掲載されている場合が多いので、まず、そちらをチェックすることをお勧めします。

多くの人がGroveモジュールを使った作例をインターネットに公開しているので、特定のモジュールの使い方を知りたいときはとても参考になります。

Nefry BTを使った記事はまだ少ないですがArduinoを使った記事がたくさんあます。
Arduinoのプログラムは少しの変更でNefry BTで動作するのでとても役に立ちます。

情報が新しく正確なのはSeeed Studio社のGroveシステムのサイト（@<href>{http://wiki.seeed.cc/Grove_System/}）です。
日本のサイトでわからないことがあった時、こちらのサイトを確認すると答えが見つかることが多いです。

====[column] Groveモジュールの動作電圧

Groveモジュールの動作電圧は5Vが基本です。

しかし、Nefry BTのGroveコネクターが供給する電圧は3.3Vなので、すべてのGroveモジュールは動かないですが、多くのGroveモジュールが3.3Vに対応しています。

必ずGroveモジュールを購入する際に、販売店のサイトや本家のサイトで動作電圧を確かめるようにしましょう。

====[/column]

====[column] Nefry BTのGroveコネクターとGPIOピンの対応関係

Nefry BTにGroveモジュールをつなげて使用するには、どのGroveコネクターにつながっているかを
プログラム内で指定する必要があります。そのときに使うGPIOピン名は、Nefry BTの基板に印刷されている
Groveコネクター名を使います。ただし1つだけ例外があります。Nefry BT R2のA0コネクターを使うときは代わりにA1を指定します。
これは基板に印刷されているコネクター名と実際に配線されているピン名が異なっているためです。

//image[030_NefryBT-R1-GROVE-PIN][Nefry BT無印のGroveコネクター名][scale=0.5]{
//}

//image[040_NefryBT-R2-GROVE-PIN][Nefry BT R2のGroveコネクター名][scale=0.5]{
//}


基本的な使い方は前述のとおりですが、4つある端子の役割をもう少し詳しく見ていきましょう。
Groveシステムは４線のGroveケーブルを使います。4本の線の役割は次のとおりです。

//table[GREVE-CABLE][Groveケーブルの色と役割]{
@<b>{色}	@<b>{役割}
------------
黄色	信号線１
白	信号線２
赤	電源
黒	グランド
//}


信号線は黄色と白の2本ありますが、通常は黄色1本のみが使われます。
I2Cのように信号線が2本必要な場合だけ、黄色と白の2本が使われます。

Nefry BT上の各Groveコネクターにある端子がどのGPIOに接続されているかを記載した図を次に示します。
背景が紺色になっている数字がGPIOピン番号です。Nefry BT無印とR2で、接続されているGPIOのピン番号は同一ですが、
A0、D5、A2といったピン名が異なっているのがわかります。

//image[050_NefryBT-R1-GROVE-GPIO-PIN][Nefry BT無印GroveコネクタのGPIOピン番号対応関係][scale=0.7]{
//}

//image[060_NefryBT-R2-GROVE-GPIO-PIN][Nefry BT R２GroveコネクタのGPIOピン番号対応関係][scale=0.7]{
//}


Nefry BT R2の右下のGroveコネクターの黄色ピンが「A0」ではなく「A1」になっているのがわかります。
このためプログラムでGroveコネクターを指定するときA1を使わなければなりません。

====[/column]


== Groveモジュールの種類
Groveモジュールとハードウェア間の通信方式の違いや、用途の違いでGroveモジュールを分類できます。

=== デジタルモジュール
入出力する値として０（LOW）か１（HIGH）の２値を使うモジュールです。
ボタン、タッチセンサー、リレーがその代表例です。

 * 入力:@<chap>{11GroveInputDigital}
 * 出力:@<chap>{12GroveOutputDigital}

 それぞれの章を参考にしてください。

=== PWMモジュール
PWM（Pulse Width Modulation）はデジタル信号が０になっている時間と１になっている時間の比率を変化させることでモジュールを制御する仕組みです。

LEDの明るさの制御やサーボモーターの回転角度の制御がその代表例です。

@<chap>{13GroveOutputPWM}を参考にしてください。

=== アナログモジュール
入出力する値を電圧の高さで表現するモジュールです。

温度計、照度計、音センサーなどがその代表例です。

Nefry BTの場合は入出力値は0V-3.3Vを0-4096の間の数値で表現されます。

アナログモジュールはI2Cなど通信が必要なプログラムよりシンプルに作ることができる利点がありますが、入出力値に誤差が出やすいという問題があります。

アナログモジュールの温度計では１〜２度の誤差が出ることがよくあります。
精度の高い値を入出力したい場合は、後に説明するI2Cを用います。

@<chap>{14GroveAnalog}を参考にしてください。

=== I2Cモジュール
I2C（アイ・スクエア・シー）はデジタル信号で通信するプロトコルです。

精度の高い測定値、複数の測定値、複雑なコマンドなどを送受信できます。

１つのモジュールで温度、湿度、気圧を測定できるモジュールがあります。

１つのGroveコネクターに複数のI2Cモジュールを接続できる特徴があります。

@<chap>{15GroveI2C}を参考にしてください。

=== 通信モジュール
他の機器とデータの送受信を行う機能を提供するモジュールです。
BLE（Bluetooth Low Energy）、赤外線通信、NFCなどがあります。

この本では取り扱いません。
