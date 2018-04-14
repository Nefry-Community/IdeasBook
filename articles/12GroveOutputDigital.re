= LEDモジュール
LEDモジュールはデジタル出力モジュールです。1（HIGH）を送ると点灯し、０（LOW）を送ると消灯します。

 * Grove LED 赤 https://www.switch-science.com/catalog/1254/
 * Grove LED 青 https://www.switch-science.com/catalog/1251/

//image[100_GROVE-MODULE-LED-separated-Tanaka][Grove LEDモジュールの構成品][scale=0.9]

Grove LEDモジュールは、

 * Groveの基板部分（LEDのソケット付き）
 * LED
 * Groveケーブル

のセットになっています。

LEDには＋、－の極性があります。通常は足の長い方がプラスですが、足の長さが同じ場合はLEDの形状で判断します。
円の一部分が欠けて直線になっている方がマイナスです。

//image[110_LED-Plus-Minus][LEDのプラス・マイナスを形状で見分ける][scale=0.4]

基板のLEDソケット部にも円が欠けている絵が描いてあるので、それに合わせてLEDを差し込みます。

//image[120_GROVE-MODULE-LED-Board-Fukui][基板上の極性表示][scale=0.4]
//image[130_GROVE-MODULE-LED-Board-LED-Fukui][LEDを差し込む][scale=0.4]

Grove基板にGroveケーブルを差し込み、Nefry BT側はD2にGroveケーブルを差し込みます。

//image[140_GROVE-MODULE-LED-Board-LED-Cable-Tanaka][Grove基板にGroveケーブルを差し込む][scale=0.4]
//image[150_GROVE-MODULE-LED-NefryBT-Cable_Tanaka][Nefry BTのD2にGroveケーブルを差し込む][scale=0.4]

==== LEDモジュールのプログラム
1秒ごとに点灯と消灯を繰り返すプログラムです。
プログラムの中身はとても単純です。
@<code>{setup()} ルーチン内で @<code>{pinMode(PIN, OUTPUT)} を実行してピンの入出力方向を@<b>{出力}に設定します。
次に、@<code>{loop()} ルーチン内で、最初に @<code>{digitalWrite(PIN,HIGH)} を使って1（HIGH）を出力したあと
@<code>{delay(1000)} で1秒間待ち、次に @<code>{digitalWirte(PIN,LOW)} で0（LOW）を出力したあと @<code>{delay(1000)}で
1秒間待ちます。

LEDが点灯しない場合や暗い場合は、Groveモジュールに付いている可変抵抗を回して調整してみてください。
5V動作を前提に設定されていることがあり、可変抵抗を調整することで3.3Vでも明かるく光るようになります。

//listnum[NefryBT_GROVE_LED][LEDモジュールのプログラム]{
#include <Nefry.h>
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
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
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
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

 * Groveリレー https://www.switch-science.com/catalog/807/
 * Groveブザー https://www.switch-science.com/catalog/804/

//image[170-GROVE-MODULE-RELAY_Fukui][Groveリレーモジュール][scale=0.4]
//image[180-GROVE-MODULE-BUZZER-Fukui][Groveブザーモジュール][scale=0.4]

==== PWMを使ってLEDの明るさを変える
PWMは、次の図のような周期的なパルス信号を生成します。1になっている時間と0になっている時間の比率（デューティー比）
を変えることで送信する電力を変化させます。LEDの点灯にPWMを使うと、1になっている時間が短いとLEDが暗くなり、
長いと明るくなります。

//image[190-PWM-LED-Waveform-key-Fukui][PWMでLEDの明るさを制御][scale=0.8]{
//}

PWMを使う場合、2つの値を指定します。

 * パルスの周期
 * デューティー比

Nefry BTではLEDCライブラリでPWMを制御します。LEDCではこの2つの値を指定するために3つの値を使います。

 * パルスの周期（Hzで指定）
 * 1周期に含まれる目盛の数（ビット数で指定。10bitなら1024目盛。最大は16bit。）
 * 1になっている時間の長さ（上記の目盛で指定。10bit目盛の場合は0〜1023の値。）

また、LEDCではどのチャンネルを使うかを指定します。チャンネルは0〜15の16個あります。

//image[200-PWM-LEDC-Parameter][LEDCで指定する値][scale=0.6]{
//}

==== LEDの明るさを変えるプログラム
//list[NefryBT_GROVE_PWM_LED][LEDの明るさを変えるプログラム]{
#include <Nefry.h>
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D2, A0, A2 (注：D0は使えません）
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します)
#define PIN D2

// LEDCのパラメータ設定
//   LEDC_CHANNEL        : チャンネル : 0
//   LEDC_RESOLUTION_BITS: 目盛数    : 10bit (0〜1023)
//   LEDC_FREQUENCY  : 周波数    : 50Hz (= 20ms周期)
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
    delay(50);
  }
  for (i = max; i > min; i -= delta) {
    ledcWrite(LEDC_CHANNEL, (uint32_t)i);
    delay(50);
  }
}
//}

@<code>{setup()} ルーチン内で @<code>{ledcSetup(...)} を実行して、チャンネル、周波数、目盛数を設定し、
@<code>{ledcAttachPin()}でGPIOピンとチャンネルを結びつけます。
次に、@<code>{loop()} ルーチン内で、@<code>{ledcWiter(LEDC_CHANNEL, i)}を使ってLEDの明るさを設定しています。
@<b>{i}を増減することでLEDの明るさを制御しています。


=== サーボモーターモジュール
サーボモーターモジュールはPWMで制御するモジュールです。サーボモーターはPWMで指定された値に応じて軸の角度が変わる特殊なモーターです。
通常180度程度の可動域があります。

//image[210-GROVE-MODULE-SERVO-Fukui][Groveサーボモーターモジュール][scale=0.4]

 * Groveサーボモーター https://www.switch-science.com/catalog/1858/

一般的には、周期は10〜20msでパルス幅は0.5ms〜2.5msぐらいのようですが、機種による差が大きく、また個体による差もあるようです。
筆者が持っているサーボモーターでは、次のようなパラメーターで動作するようです。

//image[220-PWM-LEDC-Servo-Parameter][サーボモーターのパラメータ例][scale=0.7]

==== サーボモーターのプログラム
Nefry BTに装備されているスイッチを押すたびに、0°、90°、180°の位置への移動を繰り返すプログラムです。

//list[NefryBT_GROVE_Servo][サーボモーターのプログラム]{
#include <Nefry.h>
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D2, A0, A2 (注：D0は使えません）
// Nefry BT R2の場合： D0, D2, D5, A1  (注：A0を使うときはA1を記載します)
#define PIN D2

// LEDCのパラメータ設定
//   LEDC_CHANNEL        : チャンネル : 0
//   LEDC_RESOLUTION_BITS: 目盛数    : 10bit (0〜1023)
//   LEDC_FREQUENCY  : 周波数    : 50Hz (= 20ms周期)
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
@<code>{setup()} ルーチン内で @<b>{ledcSetup(...)} を実行して、チャンネル、周波数、目盛数を設定し、
@<b>{ledcAttachPin()}でGPIOピンとチャンネルを結びつけます。@<b>{ledcWrite()}で0°のパルス幅を
サーボモーターに設定しています。

次に、@<b>{loop()} ルーチン内では、スイッチが押される度に90°、180°、0°のパルス幅を順に設定しています。
