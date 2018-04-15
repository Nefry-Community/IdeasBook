= PWMを使ってLEDの明るさを変える
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
