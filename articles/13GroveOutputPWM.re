= GroveをPWMで制御（サーボモータ）

この章は、モジュールの紹介ではなくPWMでどのような制御ができるのか紹介していきます。

== PWM（Pulse-with-modulation）とは
PWMの動作の仕組みと、Nefry BTのプログラムでのパラメーター指定方法を説明します。

=== PWMの仕組み
PWMは、次の図のような周期的なパルス信号を生成します。

//image[190-PWM-LED-Waveform-key-Fukui][PWMでLEDの明るさを制御][scale=0.8]{
//}
1になっている時間と0になっている時間の比率（デューティー比）を変えることで送信する電力を変化させます。

LEDの点灯にPWMを使うと、人の目では1になっている時間が短いとLEDが暗くなり、長いと明るくなったように見えます。

PWMを使う場合、2つの値を指定します。

 * パルスの周期
 * デューティー比

=== Nefry BTでPWMを制御する方法
Nefry BTではLEDCライブラリを使い、PWMを制御します。

//image[200-PWM-LEDC-Parameter][LEDCで指定する値][scale=0.6]{
//}
LEDCライブラリではPWMの2値を指定するために、3つの値を使います。

 * パルスの周期（Hzで指定）
 * 1周期に含まれる目盛の数（ビット数で指定。10bitなら1024目盛。最大は16bit。）
 * 1になっている時間の長さ（上記の目盛で指定。10bit目盛の場合は0〜1023の値。）

また、LEDCライブラリではどのチャンネルを使うかを指定します。チャンネルは0〜15の16個あります。

=== GroveコネクタごとのPWMの動作状況
Nefry BT 無印では、D2, A0, A2でPWMが動作します。
Nefry BT R2ではD0, D2, D5, A1の全てのGroveコネクタでPWMが動作します。

== LEDの明るさを制御
=== LEDモジュール
@<chap>{12GroveOutputDigital}で説明したLEDモジュールを使います。
Nefry BT上のGroveソケットのD2と書かれたところに、LEDモジュールを接続してください。
他のGroveソケットを使う場合は、プログラム内のPINの定義を変更してください。

=== LEDの明るさ制御のプログラム
LEDが徐々に明るくなり、最大まで明るくなったら徐々に暗くなるように制御するプログラムです。

//emlist{
//Groveケーブルを接続するGroveコネクタを１つ選んで#define文に記載してください。
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

const int min = 0;
const int max = 1023;
const int delta = 32;
int i;

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

=== プログラム説明（LEDの明るさ制御）
プログラムの説明をしていきます。

@<code>{setup()} ルーチン内で @<code>{ledcSetup(...)} を実行して、チャンネル、周波数、目盛数を設定します。

@<code>{ledcAttachPin()}でGPIOピンと上で設定したチャンネルを結びつけます。

次に、@<code>{loop()} ルーチン内で@<code>{ledcWiter(LEDC_CHANNEL, i)}を使ってLEDの明るさを設定しています。
@<b>{i}を増減することでLEDの明るさを制御しています。

== サーボモータの回転角度を制御
=== サーボモータモジュール
サーボモータモジュールはPWMで制御するモジュールです。

//image[210-GROVE-MODULE-SERVO-Fukui][Groveサーボモーターモジュール][scale=0.4]{
//}
サーボモータはPWMで指定された値に応じて軸の角度が変わる特殊なモータです。
通常180度程度の可動域があります。

 * Groveサーボモータ: @<href>{https://www.switch-science.com/catalog/1858/}

一般的には、周期は10〜20msでパルス幅は0.5ms〜2.5msぐらいのようですが、機種による差が大きく、また個体による差もあるようです。

//image[220-PWM-LEDC-Servo-Parameter][サーボモータのパラメータ例][scale=0.7]
筆者が持っているサーボモータでは、上のようなパラメータで動作するようです。

=== サーボモータ制御プログラム
Nefry BTに装備されているスイッチを押すたびに、0°、90°、180°の位置への移動を繰り返すプログラムです。

Nefry BT上のGroveソケットのD2と書かれたところに、サーボモータモジュールを接続してください。

//emlist{
//Groveケーブルを接続するGroveコネクタを１つ選んで#define文に記載してください。
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
int pulse[3] = {30, 77, 122};
int n = 0;

void setup() {
  ledcSetup(LEDC_CHANNEL, LEDC_FREQUENCY, LEDC_RESOLUTION_BITS);
  ledcAttachPin(PIN, LEDC_CHANNEL);
  Serial.println(pulse[0]);
  ledcWrite(LEDC_CHANNEL, pulse[0]);
  Nefry.enableSW();
}

void loop() {
  if (Nefry.readSW()) {
    n = (n+1) % 3;
    Serial.println(pulse[n]);
    ledcWrite(LEDC_CHANNEL, pulse[n]);
  }
}
//}

=== プログラム説明（サーボモータ制御）
配列宣言 @<code>{pulse[3]}で、0°、90°、180°のパルス幅を覚える配列を定義しています。

@<code>{setup()} ルーチン内で @<code>{ledcSetup(...)} を実行して、チャンネル、周波数、目盛数を設定します。

@<code>{ledcAttachPin()}でGPIOピンと上で設定したチャンネルを結びつけます。
次に@<code>{ledcWiter(LEDC_CHANNEL, i)}で0度にサーボモータを初期化します。

@<code>{loop()} ルーチン内では、スイッチが押される度に@<code>{ledcWiter(LEDC_CHANNEL, i)}で90°、180°、0°のパルス幅を順に設定しています。
