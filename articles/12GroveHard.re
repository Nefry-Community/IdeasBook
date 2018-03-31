= GROVEモジュールをつかってみる

本章では、Nefry BTのGROVEコネクター（白い四角のコネクター）に接続するGROVEモジュールの種類と使い方を解説します。

== GROVEシステム
IoT入門者にとって、電子部品の選択とか配線方法などハードウェアに関わる部分はわからないことがたくさんあって苦労する部分です。
その苦労を大幅に減らしてくれるのがGROVEシステムです。

=== GROVEシステムの概要
IoTシステムを作ってみようと思ったとき、ボタン、温度計、加速度計といった「測定値を入力」するためのセンサーや、
LED、サーボモーター、液晶ディスプレイといった「処理結果を出力」するためのアクチュエーターをIoTボードに接続します。
ArduinoやRaspberry PiといったIoTボードでは、通常、ジャンパーケーブルやブレッドボードを使ってそれらの部品を接続します。
部品に足（PIN）を付けるために半田付けが必要な場合もあります。
電子工作初心者には敷居の高い作業になります。
Nefry BTにはGROVEコネクターが装備されているので、GROVEケーブルを使ってセンサーやアクチュエーターを手軽に接続できます。

//image[010_GROVE-Cable-Module-NefryBTR2-separated][GROVEケーブルとGROVEモジュール][scale=0.9]

GROVEは中国の深圳（シンセン）にあるSeeed Studio社が策定した規格です。
センサーやアクチュエーターには4ピンのGROVEコネクターが取り付けられており、GROVEモジュールと呼ばれます。
IoTボードとGROVEモジュールは4線のGROVEケーブルで接続します。
コネクターには凸凹があって決められた向きにしか接続できないので、誤接続の心配がありません。
現在、Seeed Studio社から100種類程のGROVEモジュールが販売されており、IoT初心者が使ってみようと思う部品はだいたい揃っています。

 * Seeed Studio https://www.seeedstudio.com

=== 購入先
GROVEモジュールは日本国内の電子部品販売店が扱っているので実店舗や通販で簡単に購入できます。
代表的な販売店を次に示します。

 *スイッチサイエンス https://www.switch-science.com
 *秋月電子通商 http://akizukidenshi.com
 *千石電商 https://www.sengoku.co.jp
 *マルツ https://www.marutsu.co.jp

=== 情報入手先
GROVEモジュールの情報はインターネットで比較的簡単に手に入ります。
日本国内の販売店のサイトにモジュールの仕様やサンプルプログラムが掲載されている場合が多いので、まず、そちらをチェックすることをお勧めします。

多くの人がGROVEモジュールを使った作例をインターネットに公開しているので、特定のモジュールの使い方を知りたいときはとても参考になります。
Nefry BTを使った記事はまだ少ないですがArduinoを使った記事がたくさんあます。
Arduinoのプログラムは少しの変更でNefry BTで動作するのでとても役に立ちます。

情報が新しく正確なのはSeeed Studio社のGROVEシステムのサイト（http://wiki.seeed.cc/Grove_System/）です。
英語サイトですが平易な言葉で記述されているで意味を理解することはそれほど難しくありません。
日本のサイトでわからないことがあった時、こちらのサイトを眺めてみると答えが見つかることが多いです。

=== GROVEモジュールの動作電圧
GROVEモジュールの動作電圧は5Vが基本です。Arduinoの標準的な電圧が5Vなのでそれに合わせてあると思われます。
Nefry BTのGROVEコネクターが供給する電圧は3.3VなのでGROVEモジュールが動作するかどうか不安になりますが、
実際には多くのGROVEモジュールが3.3Vで動作するので問題ありません。
GROVEモジュールを購入する際に、販売店のサイトや本家のサイトで動作電圧を確かめるようすれば失敗を避けられます。

== GROVEモジュールの種類
GROVEモジュールとIoTボード間の通信方式の違いや、用途の違いでGROVEモジュールを分類できます。

=== デジタルモジュール
入出力する値として０（LOW）か１（HIGH）の２値を使うモジュールです。
ボタン、タッチセンサー、リレーがその代表例です。

=== アナログモジュール
入出力する値を電圧の高さで表現するモジュールです。温度計、照度計、音センサーなどがその代表例です。
Nefry BTの場合は供給電圧が3.3Vなので、入出力値は0〜3.3Vで表現されます。

アナログモジュールはプログラムが単純になるという利点がありますが、入出力値に誤差が出やすいという問題があります。
たとえば、アナログモジュールの温度計では１〜２度の誤差が出ることがよくあります。
誤差は、アナログモジュール側に原因がある場合と、Nefry BT側のアナログデジタル変換回路に原因がある場合の両方があります。
精度の高い値を入出力したい場合は、次に説明するI2CやPWMを用います。

=== I2Cモジュール
I2C（アイ・スクエア・シー）はデジタル信号で通信するプロトコルの一種です。byte列を送受信できるので、精度の高い測定値、複数の測定値、
複雑なコマンドなどを送受信できます。たとえば１つのモジュールで温度、湿度、気圧を測定できるモジュールがあります。

I2Cは2本の信号線と電源とグランドの計4本のケーブルを使います。GROVEケーブルは信号線2本と電源とグランドの４線なので
I2Cモジュールの接続にそのまま使えます。I2Cはデイジーチェーン接続ができる設計になっているので、IoTボードの１つのGROVEコネクターに複数の
I2Cモジュールを接続できます。

=== PWMモジュール
PWM（Pulse Width Modulation）はデジタル信号が０になっている時間と１になっている時間の比率を変化させることで
電力を制御する仕組みです。
PWMを使う代表例は、LEDの明るさの制御やサーボモーターの回転角度の制御です。

=== 通信モジュール
他の機器とデータの送受信を行う機能を提供するモジュールです。
BLE（Bluetooth Low Energy）、赤外線通信、NFCなどがあります。


== 色々なGROVEモジュールをつかってみる
この節では、よく使われるGROVEモジュールをNefry BTに接続して動作させてみる例を説明します。
ここで紹介するプログラムは、ファームウェアv1.2.0で動作確認を行なっています。

=== Nefry BTのGROVEコネクターとGPIOピンの対応関係
Nefry BTにGROVEモジュールをつなげて使用するには、どのGROVEコネクターにつながっているかを
プログラム内で指定する必要があります。そのときに使うGPIOピン名は、Nefry BTの基板に印刷されている
GROVEコネクター名を使います。ただし1つだけ例外があります。Nefry BT R2のA0コネクターを使うときは代わりにA1を指定します。
これは基板に印刷されているコネクター名と実際に配線されているピン名が異なっているためです。

//image[030_NefryBT-R1-GROVE-PIN][Nefry BT無印のGROVEコネクター名][scale=0.5]
//image[040_NefryBT-R2-GROVE-PIN][Nefry BT R2のGROVEコネクター名][scale=0.5]


基本的な使い方は前述のとおりですが、4つある端子の役割をもう少し詳しく見ていきましょう。
GROVEシステムは４線のGROVEケーブルを使います。4本の線の役割は次のとおりです。
//table[GREVE-CABLE][GROVEケーブルの色と役割]{
@<b>{色}	@<b>{役割}
------------
黄色	信号線１
白	信号線２
赤	電源
黒	グランド
//}

#@# //indepimage[T010-GROVE-Cable-Color]
//image[T010b-GROVE-Cable-Color][GROVEケーブルの色と役割][scale=0.4]

信号線は黄色と白の2本ありますが、通常は黄色1本のみが使われます。
I2Cのように信号線が2本必要な場合だけ、黄色と白の2本が使われます。

Nefry BT上の各GROVEコネクターにある端子がどのGPIOに接続されているかを記載した図を次に示します。
背景が紺色になっている数字がピン番号です。Nefry BT無印とR2で、接続されているGPIOのピン番号は同一ですが、
A0、D5、A2といったピン名が異なっているのがわかります。

//image[050_NefryBT-R1-GROVE-GPIO-PIN][Nefry BT無印GROVEコネクタのGPIO番号対応関係][scale=0.7]
//image[060_NefryBT-R2-GROVE-GPIO-PIN][Nefry BT R２GROVEコネクタのGPIO番号対応関係][scale=0.7]


Nefry BT R2の右下のGROVEコネクターの黄色ピンが「A0」ではなく「A1」になっているのがわかります。
このためプログラムでGROVEコネクターを指定するときA1を使わなければなりません。

少しややこしいですね。このようなGPIOのピン名を使わずに、GPIOのピン番号を使えば混乱が避けられます。
また、この方式にすればNefry BT無印とR2のどちらでも動作するプログラムになるという利点があります。
たとえばピン番号「32」を指定すると、Nefry BT無印でもR2でも図の右下のGROVEコネクターを指定したことになります。


=== ボタンモジュール
ボタンモジュールはデジタル入力モジュールです。ボタンが押されている時は１（HIGH）を返し、離されている時は０（LOW）を返します。
//image[070-GROVE-MODULE-BUTTON-Fukui][GROVEボタンモジュール][scale=0.3]

 * GROVEボタンモジュール https://www.switch-science.com/catalog/801/

==== ボタンモジュールのプログラム
シリアルモニターに、通常は0が表示され、ボタンを押している間だけ1が表示されるプログラムです。
モジュールを接続するGROVEコネクターに合わせて、PINの#define文のピン名を変更してください。

プログラムの中身はとても単純です。
@<b>{setup()} ルーチン内で @<b>{pinMode(PIN, INPUT)} を実行してピンの入出力方向を@<b>{入力}に設定します。
次に @<b>{loop()} ルーチン内で @<b>{digitalRead(PIN)} を使ってピンの値を取得します。
ボタンの状態に応じて0か1が返されます。
返された値を @<b>{Serial.print()} 関数でシリアルモニターに出力します。

//list[NefryBT_GROVE_Button][ボタンモジュールのプログラム]{
#include <Nefry.h>
//GROVEケーブルを接続するGROVEコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D0, D2, A0, A2
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します。)
#define PIN D2

void setup() {
  pinMode(PIN, INPUT);
  Serial.print("PIN = ");
  Serial.println(PIN);
}

void loop() {
  Serial.println(digitalRead(PIN));
  delay(300);
}
//}

シリアルモニターには次のように入力結果が表示されます。

//image[080_MONITOR-BUTTON][ボタンプログラムのシリアルモニター出力例][scale=0.9]

==== GROVEコネクターごとの動作状況
上記のプログラムが、4つあるGROVEコネクターで動作するかどうかを表にまとめました。

//table[ButtonProgramTestResult][ボタンプログラム動作状況（Nefry BT無印）]{
@<b>{コネクター名} 	@<b>{動作状況}	@<b>{コメント}
------------
I2C(D0)	NO	Nefry BT無印のD0コネクターは液晶ディスプレイと@<br>{}GPIOピンを共用しているため動作しません。@<br>{}また、GROVEコネクターにモジュールを繋いでいると@<br>{}Nefry BTが起動しません。
D2	OK
A0	OK
A2	OK
//}

#@# //indepimage[T020-NefryBt-R1-BUTTON]
//image[T020b-NefryBT-R1-BUTTON][ボタンプログラム動作状況（Nefry BT無印）][scale=0.9]

//table[ButtonProgramTestResultR2][ボタンプログラム動作状況（Nefry BT R2）]{
@<b>{R2コネクター名}	@<b>{動作状況}	@<b>{コメント}
---------
D0	OK
D2	OK
D5	OK
A0	OK	注：R2用のプログラムでは、A0ではなくA1を使います。
//}

#@# //indepimage[T030-NefryBT-R2-BUTTON]
//image[T030c-NefryBT-R2-BUTTON][ボタンプログラム動作状況（Nefry BT R2）][scale=0.9]

==== 他のデジタル入力モジュール
他のデジタル入力モジュールには、タッチセンサー、傾きセンサー、磁気スイッチ、水センサーなどがあります。
いずれもボタンモジュールのプログラムがそのまま使えます。

 * GROVEタッチセンサー https://www.switch-science.com/catalog/811/
 * GROVE傾きセンサー https://www.switch-science.com/catalog/803/
 * GROVE磁気スイッチ https://www.switch-science.com/catalog/809/
 * GROVE水センサー https://www.switch-science.com/catalog/817/

//image[090_GROVE-MODULE-TOUCH-Fuki][GROVEタッチセンサーモジュール][scale=0.3]

=== LEDモジュール
LEDモジュールはデジタル出力モジュールです。1（HIGH）を送ると点灯し、０（LOW）を送ると消灯します。

 * GROVE LEDモジュール赤 https://www.switch-science.com/catalog/1254/
 * GROVE LEDモジュール青 https://www.switch-science.com/catalog/1251/

//image[100_GROVE-MODULE-LED-separated-Tanaka][GROVE LEDモジュールの構成品][scale=0.9]

GROVE LEDモジュールは、

 * GROVEの基板部分（LEDのソケット付き）
 * LED
 * GROVEケーブル

のセットになっています。

LEDには＋、－の極性があります。通常は足の長い方がプラスですが、足の長さが同じ場合はLEDの形状で判断します。
円の一部分が欠けて直線になっている方がマイナスです。

//image[110_LED-Plus-Minus][LEDのプラス・マイナスを形状で見分ける][scale=0.4]

基板のLEDソケット部にも円が欠けている絵が描いてあるので、それに合わせてLEDを差し込みます。

//image[120_GROVE-MODULE-LED-Board-Fukui][基板上の極性表示][scale=0.4]
//image[130_GROVE-MODULE-LED-Board-LED-Fukui][LEDを差し込む][scale=0.4]

GROVE基板にGROVEケーブルを差し込み、Nefry BT側はD2にGROVEケーブルを差し込みます。

//image[140_GROVE-MODULE-LED-Board-LED-Cable-Tanaka][GROVE基板にGROVEケーブルを差し込む][scale=0.4]
//image[150_GROVE-MODULE-LED-NefryBT-Cable_Tanaka][Nefry BTのD2にGROVEケーブルを差し込む][scale=0.4]

==== LEDモジュールのプログラム
1秒ごとに点灯と消灯を繰り返すプログラムです。

プログラムの中身はとても単純です。
@<b>{setup()} ルーチン内で @<b>{pinMode(PIN, OUTPUT)} を実行してピンの入出力方向を@<b>{出力}に設定します。
次に、@<b>{loop()} ルーチン内で、最初に @<b>{digitalWrite(PIN,HIGH)} を使って1（HIGH）を出力したあと
@<b>{delay(1000)} で1秒間待ち、次に @<b>{digitalWirte(PIN,LOW)} で0（LOW）を出力したあと @<b>{delay(1000)}で
1秒間待ちます。

LEDが点灯しない場合や暗い場合は、GROVEモジュールに付いている可変抵抗を回して調整してみてください。
5V動作を前提に設定されていることがあり、可変抵抗を調整することで3.3Vでも明かるく光るようになります。

//listnum[NefryBT_GROVE_LED][LEDモジュールのプログラム]{
#include <Nefry.h>
//GROVEケーブルを接続するGROVEコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D2, A0, A2 (注：D0は使えません）
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します。)
#define PIN D2

void setup() {
  pinMode(PIN, OUTPUT);
  Serial.print("PIN = ");
  Serial.println(PIN);
}

void loop() {
  digitalWrite(PIN, HIGH);
  Serial.println(HIGH);
  delay(1000);

  digitalWrite(PIN, LOW);
  Serial.println(LOW);
  delay(1000);
}
//}

==== LEDプログラムの機能追加：内臓スイッチとの連携
Nefry BTに装備されているスイッチと連動させるプログラムにしてみましょう。
スイッチを押すと１秒間LEDが点灯するプログラムにします。
@<b>{setup()} ルーチン内で @<b>{Nefry.enableSW()} を実行してスイッチを利用できるようにします。
次に、@<b>{loop()} ルーチン内で、@<b>{Nefry.readSW()} を使ってスイッチの状態を読み取り、
押されていればLEDを点灯して1秒間待ちLEDを消灯します。

//list[NefryBT_GROVE_LED_Switch][LEDと内臓スイッチとの連携プログラム]{
#include <Nefry.h>
//GROVEケーブルを接続するGROVEコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D2, A0, A2 (注：D0は使えません）
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します)
#define PIN D2

void setup() {
  pinMode(PIN, OUTPUT);
  Serial.print("PIN = ");
  Serial.println(PIN);
  Nefry.enableSW();
}

void loop() {
  if (Nefry.readSW()) {
    digitalWrite(PIN, HIGH);
    Serial.println(HIGH);
    delay(1000);
    digitalWrite(PIN, LOW);
    Serial.println(LOW);
  }
}
//}

//image[160_GROVE-MODULE-LED-running-Tanaka][ボタンを押してLEDを光らせている様子][scale=0.7]

==== 他のデジタル出力モジュール
リレーやブザーなどもデジタル出力モジュールとして利用できます。
リレーは、1（HIGH）だと回路を接続し、0（LOW）だと切断します。
ブザーは、1（HIGH）だと音が鳴り、0（LOW）だと音が止まります。

 * GROVEリレーモジュール https://www.switch-science.com/catalog/807/
 * GROVEブザーモジュール https://www.switch-science.com/catalog/804/

//image[170-GROVE-MODULE-RELAY_Fukui][GROVEリレーモジュール][scale=0.4]
//image[180-GROVE-MODULE-BUZZER-Fukui][GROVEブザーモジュール][scale=0.4]

==== PWMを使ってLEDの明るさを変える
PWMは、次の図のような周期的なパルス信号を生成します。1になっている時間と0になっている時間の比率（デューティー比）
を変えることで送信する電力を変化させます。LEDの点灯にPWMを使うと、1になっている時間が短いとLEDが暗くなり、
長いと明るくなります。

//image[190-PWM-LED-Waveform-key-Fukui][PWMでLEDの明るさを制御][scale=0.8]

PWMを使う場合、2つの値を指定します。

 * パルスの周期
 * デューティー比

Nefry BTではLEDCライブラリでPWMを制御します。LEDCではこの2つの値を指定するために3つの値を使います。

 * パルスの周期（Hzで指定）
 * 1周期に含まれる目盛の数（ビット数で指定。10bitなら1024目盛。最大は16bit。）
 * 1になっている時間の長さ（上記の目盛で指定。10bit目盛の場合は0〜1023の値。）

また、LEDCではどのチャンネルを使うかを指定します。チャンネルは0〜15の16個あります。

//image[200-PWM-LEDC-Parameter][LEDCで指定する値][scale=0.6]

==== LEDの明るさを変えるプログラム
//list[NefryBT_GROVE_PWM_LED][LEDの明るさを変えるプログラム]{
#include <Nefry.h>
//GROVEケーブルを接続するGROVEコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D2, A0, A2 (注：D0は使えません）
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します)
#define PIN D2

// LEDCのパラメータ設定
//   LEDC_CHANNEL        : チャンネル : 0
//   LEDC_RESOLUTION_BITS: 目盛数    : 10bit (0〜1023)
//   LEDCBASE_FREQUENCY  : 周波数    : 50Hz (= 20ms周期)
#define LEDC_CHANNEL 0
#define LEDC_RESOLUTION_BITS 10
#define LEDC_FREQUENCY 50

const int32_t min = 0;
const int32_t max = 1023;
const int32_t delta = 32;
int32_t i;

void setup() {
  Serial.print("PIN = ");
  Serial.println(PIN);
  ledcSetup(LEDC_CHANNEL, LEDC_FREQUENCY, LEDC_RESOLUTION_BITS);
  ledcAttachPin(PIN, LEDC_CHANNEL);
}

void loop() {
  for (i = min; i < max; i += delta) {
    ledcWrite(LEDC_CHANNEL, (uint32_t)i);
    Nefry.ndelay(50);
  }
  for (i = max; i > min; i -= delta) {
    ledcWrite(LEDC_CHANNEL, (uint32_t)i);
    Nefry.ndelay(50);
  }
}
//}

@<b>{setup()} ルーチン内で @<b>{ledcSetup(...)} を実行して、チャンネル、周波数、目盛数を設定し、
@<b>{ledcAttachPin()}でGPIOピンとチャンネルを結びつけます。
次に、@<b>{loop()} ルーチン内で、@<b>{ledcWiter(LEDC_CHANNEL, i)}を使ってLEDの明るさを設定しています。
@<b>{i}を増減することでLEDの明るさを制御しています。

このプログラムでは@<b>{delay()}の代わりに@<b>{Nefry.delay()}を使っています。
これはWiFi接続管理やWebサーバー機能などのNefry独自の機能を実行するタイミングを提供するためです。
Nefry独自機能は@<b>{loop()}関数の繰り返し実行の合間に行われます。
@<b>{loop()}関数の中で行われる処理に時間がかかると、独自機能がその間行われなくなります。
@<b>{Nefry.ndelay()}関数を使うと、delayの待ち時間の間に独自機能が実行されます。

=== サーボモーターモジュール
サーボモーターモジュールはPWMで制御するモジュールです。サーボモーターはPWMで指定された値に応じて軸の角度が変わる特殊なモーターです。
通常180度程度の可動域があります。

//image[210-GROVE-MODULE-SERVO-Fukui][GROVEサーボモーターモジュール][scale=0.4]

 * GROVEサーボモーターモジュール https://www.switch-science.com/catalog/1858/

一般的には、周期は10〜20msでパルス幅は0.5ms〜2.5msぐらいのようですが、機種による差が大きく、また個体による差もあるようです。
筆者が持っているサーボモーターでは、次のようなパラメーターで動作するようです。

//image[220-PWM-LEDC-Servo-Parameter][サーボモーターのパラメータ例][scale=0.7]

==== サーボモーターのプログラム
Nefry BTに装備されているスイッチを押すたびに、0°、90°、180°の位置への移動を繰り返すプログラムです。

//list[NefryBT_GROVE_Servo][サーボモーターのプログラム]{
#include <Nefry.h>
//GROVEケーブルを接続するGROVEコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D2, A0, A2 (注：D0は使えません）
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します)
#define PIN D2

// LEDCのパラメータ設定
//   LEDC_CHANNEL        : チャンネル : 0
//   LEDC_RESOLUTION_BITS: 目盛数    : 10bit (0〜1023)
//   LEDCBASE_FREQUENCY  : 周波数    : 50Hz (= 20ms周期)
#define LEDC_CHANNEL 0
#define LEDC_RESOLUTION_BITS 10
#define LEDC_FREQUENCY 50

//  30/1024*20ms = 0.59ms
//  77/1024*20ms = 1.50ms
// 122/1024*20ms = 2.38ms
uint32_t pulse[3] = {30, 77, 122};
int n = 0;

void setup() {
  ledcSetup(LEDC_CHANNEL, LEDC_FREQUENCY, LEDC_RESOLUTION_BITS);
  ledcAttachPin(PIN, LEDC_CHANNEL);
  Serial.println(pulse[n]);
  ledcWrite(0, pulse[n]);
  Nefry.enableSW();
}

void loop() {
  if (Nefry.readSW()) {
    n = (n+1) % 3;
    Serial.println(pulse[n]);
    ledcWrite(0, pulse[n]);
  }
}
//}

配列宣言 @<b>{pulse[3]}で、0°、90°、180°のパルス幅を覚える配列を定義しています。
@<b>{setup()} ルーチン内で @<b>{ledcSetup(...)} を実行して、チャンネル、周波数、目盛数を設定し、
@<b>{ledcAttachPin()}でGPIOピンとチャンネルを結びつけます。@<b>{ledcWrite()}で0°のパルス幅を
サーボモーターに設定しています。

次に、@<b>{loop()} ルーチン内では、スイッチが押される度に90°、180°、0°のパルス幅を順に設定しています。

=== ボリュームモジュール
ボリュームモジュール（可変抵抗モジュール）はアナログ入力モジュールです。
Nefry BTでは3.3Vをモジュールに供給しているので、ノブを回すと0Vから3.3Vまで電圧が連続的に変化します。
ノブを時計回りにいっぱい回すと0Vで反時計回りにいっぱい回すと3.3Vが出力されます。

//image[230-GROVE-MODULE-VOLUME-Fukui][GROVEボリュームモジュール][scale=0.4]

 * GROVEボリュームモジュール https://www.switch-science.com/catalog/805/

==== ボリュームモジュールのプログラム
ボリュームモジュールから読み込んだ値をシリアルモニターに表示するプログラムです。
値の読み込みは@<b>{analogRead(PIN)}関数で行なっています。
モジュールを接続するGROVEコネクターに合わせて、PINの@<b>{#define}宣言をしてください。

//list[Nefry_GROVE_RotaryAngleSensor][ボリュームのプログラム]{
#include <Nefry.h>
//GROVEケーブルを接続するGROVEコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D0, D2, A0, A2
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します。)
#define PIN A1

void setup() {
  pinMode(PIN, INPUT);
}

void loop() {
  Serial.println(analogRead(PIN));
  delay(300);
}
//}

プログラムを動作させノブを左右に回すとこのように0〜4095の数字が表示されます。
右にいっぱい回すと0、左にいっぱい回すと4095が表示されます。
//image[240-MONITOR-VOLUME][ボリュームプログラムのシリアルモニター出力例][scale=0.9]

シリアルモニターに出力している数値をグラフで表すことも可能です。
Arduino IDEに装備されている「シリアルプロッタ」を使います。
シリアルプロッタは次の手順で起動します。

 * シリアルモニタウィンドウが開いている場合は閉じる。
 * 「ツール」メニューの「シリアルプロッタ」を選択する。

シリアルプロッタを開くと、次のようなグラフが描画されます。

//image[250-PLOTTER-VOLUME][シリアルプロッター表示例][scale=0.9]

==== ボリュームモジュールのGROVE端子ごとの動作状況
ボリュームモジュールの動作状況を次の表にまとめました。

//table[VolumeProgramTestResult][ボリュームプログラム動作状況（Nefry BT無印）]{
@<b>{無印コネクター名}	@<b>{動作状況}	@<b>{コメント}
-----------------------------
I2C(D0)	NO	常に0が表示される。
D2	NO	常に0が表示される。
A0	NO	常に4095が表示される。
A2	OK
//}

#@# //indepimage[T040-NefryBT-R1-VOLUME]
//image[T040b-NefryBT-R1-VOLUME][ボリュームプログラム動作状況（Nefry BT無印）][scale=0.7]

//table[VolumeProgramTestResultR2][ボリュームプログラム動作状況（Nefry BT R2）]{
@<b>{R2コネクター名}	@<b>{動作状況}	@<b>{コメント}
----------------------------
D0	NO	常に0が表示される。
D2	NO	常に0が表示される。
D5	NO	常に4095が表示される。
A0	OK	注：R2用のプログラムでは、A0ではなくA1を使います
//}

#@# //indepimage[T050-NefryBT-R2-VOLUME]
//image[T050b-NefryBT-R2-VOLUME][ボリュームプログラム動作状況（Nefry BT R2）][scale=0.9]

Nefry BT無印ではGROVEコネクターA2だけ、Nefry BT R2ではGROVEコネクターA0だけが使えるという結果になりましたが、
これには理由があります。

0〜3.3Vの電圧を0〜4095の数値に変換する作業はADC（Analog Digital Converter）が行います。
Nefry BTのCPUであるESP-WROOM-32には２系統のADCがありADC1、ADC2と呼ばれています。
ADCが使えるGPIOピンは決まっています。どのピンにADC1とADC2が割り当てられているかを次表にまとめます。


//table[ADCPinAssignR1][ADC ピン割り当て（Nefry BT無印）]{
@<b>{無印コネクター名}	@<b>{ADC}
-------------------
I2C(D0)	-
D2	-
A0	ADC2
A2	ADC1
//}

#@# //indepimage[T060-NefryBT-R1-ADC]
//image[T060b-NefryBT-R1-ADC][ADC ピン割り当て（Nefry BT無印）][scale=0.4]

//table[ADCPinAssignR2][ADC ピン割り当て（Nefry BT R2）]{
@<b>{R2コネクター名}	@<b>{ADC}
-----------------
D0	-
D2	-
D5	ADC2
A0	ADC1
//}

#@# //indepimage[T070-NefryBT-R2-ADC]
//image[T070c-NefryBT-R2-ADC][ADC ピン割り当て（Nefry BT R2）][scale=0.6]


ADC2には「WiFi機能を利用中は使えない」という制約があるので、通常使えるのはADC1だけになります。
Nefry BT無印ではGROVEコネクターA2、Nefry BT R2ではA0（実際にはA1）だけでアナログ入力が行えます。

ADC2の制約について詳しい情報はこちらを参照してください。

http://esp-idf.readthedocs.io/en/latest/api-reference/peripherals/adc.html

=== アナログ温度計
アナログ温度計はアナログ入力モジュールです。

//image[260-GROVE-MODULE-TEMPERATURE-Fukui][GROVEアナログ温度計][scale=0.4]

 * GROVEアナログ温度計モジュール https://www.switch-science.com/catalog/806/

ボリュームモジュールと同じプログラムで測定値を取得できます。
しかし、これでは0〜4095の数値が得られるだけで温度が何度なのかわかりません。
取得した数値を温度に変換するプログラムが必要になります。
変換方法は、GROVEモジュールの販売サイトや、GROVEモジュールで使用している温度センサー部品のサイトにデータシート（仕様書）
が掲載されているのでそれを見れば詳細がわかりますが、かなり難解です。
GROVEモジュールを使うだけなら、販売店サイトで公開されているプログラムを利用するのが手軽で早道です。

==== アナログ温度計のプログラム
ここではSeeed Studio社の商品紹介ページ（http://wiki.seeed.cc/Grove-Temperature_Sensor_V1.2/）
にあるプログラムを使ってみます。

//list[NefryBT_GROVE_AnalogTemperatureSensor_Seeed][Seeed Studio社の商品紹介ページにあるプログラム]{
#include <math.h>
const int B = 4275;           // B value of the thermistor
const int R0 = 100000;        // R0 = 100k
const int pinTempSensor = A5; // Grove - Temperature Sensor connect to A5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int a = analogRead(pinTempSensor);

  float R = 1023.0/a-1.0;
  R = R0*R;

  // convert to temperature via datasheet
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;

  Serial.print("temperature = ");
  Serial.println(temperature);

  delay(100);
}
//}

Nefry BT R2用にプログラムを変更します。

 * 先頭に @<b>{#include <Nefry.h>} を追加します。
 * @<b>{pinTempSensor}の@<b>{A5}を@<b>{A1}に変更します。（Nefry BT無印の場合はA2にしてください。）
 * @<b>{Serial.begin(9600)}は不要なので削除します。
 * @<b>{pinMode()}関数がなくても動作しますが、念のため@<b>{pinMode(pinTermpSensor, INPUT)}を追加します。
 * 変数@<b>{a}は@<b>{analogRead(pinTempSensor)}で取得した値です。Arduinoの@<b>{analogRead()}は0〜1023の値を取得できますが、NefrryBTの@<b>{analogRead()}では0〜4095を取得するので、@<b>{1023.0}となっている部分を@<b>{4095.0}に変更します。

この変更を加えたプログラムは次のようになります。
//listnum[NefryBT_GROVE_AnalogTemperatureSensor][Nefry BT R2向けに変更したアナログ温度計プログラム]{
#include <Nefry.h>
#include <math.h>
const int B = 4275;           // B value of the thermistor
const int R0 = 100000;        // R0 = 100k
const int pinTempSensor = A1; // Grove - Temperature Sensor connect to A1

void setup()
{
  pinMode(pinTempSensor, INPUT);
}

void loop()
{
  int a = analogRead(pinTempSensor);

  float R = 4095.0/a-1.0;
  R = R0*R;

  // convert to temperature via datasheet
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;

  Serial.print("temperature = ");
  Serial.println(temperature);

  delay(100);
}
//}

このプログラムを動作させるとシリアルモニタに次のような結果が出力されます。

//image[270-MONITOR-TEMPERATURE][温度計プログラムのシリアルモニーター出力例][scale=0.9]

なんとなくそれらしい温度が表示されていますが、Arduinoにこの温度計を接続した時より1〜2度低いようです。
Arduinoのプログラムは5Vでの動作を前提としているので、3.3Vだと少し定数の変更が必要なのかもしれません。
このあたりがアナログセンサーを使うときの難しさです。数値の揺らぎがNefry BTの電子回路から来ているのか、
電圧の違いによるセンサーの挙動の違いなのか、プログラムに問題があるのかなど、どの原因かを切り分けるのは大変です。
I2Cのようなデジタルモジュールであれば、このような問題はかなり回避できます。

=== I2C温度・湿度・気圧計
I2C接続の温度・湿度・気圧センサー（BME280）を使ってみましょう。

//image[280-GROVE-MODULE-BME280-Seeed][GROVE温度・湿度・気圧センサー(BME280)][scale=0.3]

 * GROVE温度・湿度・気圧センサーモジュール https://www.switch-science.com/catalog/3374/

I2C接続ではSCLとSDAという2本の信号線を使います。
Nefry BT無印とNefry BT R2のどちらもdefault設定ではGROVE D0コネクターに
SCLとSDAが接続されいて、SCLは黄色線、SDAは白線です。

//image[290-NefryBT-R1-GROVE-GPIO-I2C-PIN][Nefy BT無印のI2C接続コネクター][scale=0.7]
//image[300-NefryBT-R2-GROVE-GPIO-I2C-PIN][Nefy BT R2のI2C接続コネクター][scale=0.7]

SCLとSDAが接続されるコネクターはプログラムで変更可能です。変更方法は後述します。

==== I2C温度・湿度・気圧計のプログラム
Seeed Studio社が公開しているプログラムをそのまま使ってみます。
スイッチサイエンス社の商品ページに「ライブラリ（GitHub）」というリンクがあます。
//image[310-WEB-SwitchScience-BME280-REFERENCE][スイッチサイエンス社の商品ページ][scale=0.5]
このリンクをクリックするとSeeed Studio社のGitHubページが開きます。
//image[320-WEB-Seeed-GitHub-BME280][Seed Studio社のGitHubページ][scale=0.9]
ページ右上の「Clone or download」というプルダウンメニューをクリックして、プログラム一式をダウンロードします。
ダウンロードしたプログラムのフォルダー構成は次のようになっています。
//image[330-WEB-Seeed-GitHub-BME280-File-Tree][温度・湿度・気圧計プログラムのフォルダー構成][scale=0.9]

「bme280_example」というフォルダーを、Nefry BTのプログラムを置いているご自身のフォルダにコピーします。
次に、「Seeed_BME280.cpp」と「Seeed_BME280.h」をそのフォルダにコピーします。コピー先のフォルダはこうなります。
ファイルが３つコピーされていることを確認してください。
//image[340-My-bme280_example-folder][コピーしたBME280_exampleフォルダー][scale=0.9]

「bme280_example.ino」ファイルを開くと、Arduino IDEの画面が開きます。タブが3つあり、フォルダー内のファイルが
タブとして表示されていることを確認してください。
//image[350-IDE-BME280-Original][BME280プログラムのArduino IDE画面][scale=0.7]

Nefry BT用にプログラムを変更を行います。変更は2箇所だけです。

 * 冒頭のコメントの直後に @<b>{#include <Nefry.h>}を追加します。
 * @<b>{setup()}ルーチン内にある@<b>{Serial.begin(9600);}をコメントアウトします。
変更後のプログラムはこうなります。

//image[360-IDE-BME280-Nefry][変更後のBME280プログラム][scale=0.7]

//list[NefryBT_GROVE_BME280][I2C温度・湿度・気圧計のプログラム]{
#include <Nefry.h>

#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;

void setup()
{
  //Serial.begin(9600);
  if(!bme280.init()){
    Serial.println("Device error!");
  }
}

void loop()
{
  float pressure;

  //get and print temperatures
  Serial.print("Temp: ");
  Serial.print(bme280.getTemperature());
  Serial.println("C");//The unit for  Celsius because original arduino
                      //don't support speical symbols

  //get and print atmospheric pressure data
  Serial.print("Pressure: ");
  Serial.print(pressure = bme280.getPressure());
  Serial.println("Pa");

  //get and print altitude data
  Serial.print("Altitude: ");
  Serial.print(bme280.calcAltitude(pressure));
  Serial.println("m");

  //get and print humidity data
  Serial.print("Humidity: ");
  Serial.print(bme280.getHumidity());
  Serial.println("%");

  delay(2000);
}
//}

次にArduino IDEのNefry BTボードマネージャーをv1.2.1以降にしておきます。
Nefry BT R2はV1.2.0以前だとI2C制御部分のプログラムがうまく動作しません。
ボードマネージャーのアップデートは次の手順で行います。

 * Arduino IDEの「ツールメニュー ＞ ボード ＞ ボードマネージャ」を選ぶ
 * 検索欄にnefryを記入する
 * 検索結果をクリックするとバージョン選択のプルダウンメニューが現れる
 * プルダウンメニューから1.2.1を選択する
 * 更新ボタンをクリックする

//image[370-IDE-BoardManager-Nefry-v121][ボードマネージャーの更新][scale=0.9]

プログラムを実行すると、シリアルモニターに測定結果が表示されます。

//image[380-MONITOR-BME280][BME280プログラムのシリアルモニター表示例][scale=0.9]

Altitudeの値がちょっと変ですが、温度、湿度、気圧はだいたい正しいようです。

==== 他のGROVEコネクターを使う方法
他のGROVEコネクターを使うには、I2Cの通信に使う2本の通信線SCLとSDAのGPIOピン番号を変更する必要があります。
以下では、GROVEコネクターD2に変更する例を説明します。

 * Arduino IDEで「Seeed_BME280.cpp」タブを選択する。
 * 5行目にある@<b>{Wire.begin();}を、@<b>{Wire.begin(D3, D2);}に変更します。@<b>{begin()}の引数の並び順は、@<b>{begin(SDA, SCL)}です。


//image[390-IDE-BME280-Wire-begin][GROVEコネクターD2を使うためのプログラム変更][scale=0.7]


== （校正用メモ）

執筆者の皆さんと相談して統一する必要がある項目

=== 用語の統一が必要なもの

 * GROVE or Grove （Seeedの公式サイトではGROVEと表記されている）
 * GROVEコネクター or Groveポート or GROVEソケット
 * GROVEモジュール or GROVEパーツ
 * 入力モジュール or センサーモジュール
 * 出力モジュール or アクチュエーターモジュール
 * NefryBT or Nefry BT （BTの前のスペースの有無）
 * Nefry BT無印 or Nefry BT R1

=== プログラムの書き方の統一

 * delay() or Nefry.ndelay()　（delay()を全てNefry.ndelay()に変更した方が良いのか？）

=== tableを使うかどうか

table（表）は、

 * pdf版　○（正しく表示される）
 * web版　X（表示が崩れる）
 * atom内のpreview　　X（表示が崩れる）

という状況。このバージョンの原稿では、校正がやり易いようにtableの画像を併記している。

電子版をweb形式で公開する場合、tableはやめてtableの画像を貼ることになる？
