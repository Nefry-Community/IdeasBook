= Groveのアナログ入力（ボリュームと温度センサー）

== ボリュームモジュール

ボリュームモジュール（可変抵抗モジュール）はアナログ入力モジュールです。

//image[230-GROVE-MODULE-VOLUME-Fukui][Groveボリュームモジュール][scale=0.4]{
//}

 * Groveボリューム @<href>{https://www.switch-science.com/catalog/805/}

 Nefry BTでは3.3Vをモジュールに供給しているので、ノブを回すと0Vから3.3Vまで電圧が連続的に変化します。

 ノブを時計回りにいっぱい回すと0Vで反時計回りにいっぱい回すと3.3Vが出力されます。

=== ボリュームモジュールのプログラム

ボリュームモジュールから読み込んだ値をシリアルモニターに表示するプログラムです。

Nefry BT無印に接続する場合はA2、Nefry BT R2に接続する場合はA1（基板上はA0と記載）に接続します。

Nefry BT無印の場合はコードの@<code>{#define PIN A1}を@<code>{#define PIN A2}に書き換えてください。

//emlist[Nefry_GROVE_RotaryAngleSensor][ボリュームのプログラム]{
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： A2
// Nefry BT R2の場合： A1  (注：A0を使うときはA1を記載します。)
#define PIN A1

void setup() {
}

void loop() {
  Serial.println(analogRead(PIN));
  delay(500);
}
//}

=== プログラム説明

プログラムの説明をしていきます。

今まで説明してきたコードで一番シンプルになります。

値の読み込みは@<code>{analogRead(PIN)}関数で行なっています。

返された値を @<code>{Serial.println()} 関数でシリアルモニターに出力します。

その上記の繰り返しを0.5秒ごとに行います。

=== 動作結果（ボリュームモジュール）

プログラムを動作させノブを左右に回すとこのように0〜4095の数字が表示されます。

右にいっぱい回すと0、左にいっぱい回すと4095が表示されます。

//image[240-MONITOR-VOLUME][ボリュームプログラムのシリアルモニター出力例][scale=0.9]{
//}

シリアルモニターに出力している数値をグラフで表すことも可能です。

Arduino IDEに装備されている@<b>{「シリアルプロッタ」}を使います。

シリアルプロッタは次の手順で起動します。

 1. シリアルモニタウィンドウが開いている場合は閉じる。
 2. 「ツール」メニューの「シリアルプロッタ」を選択する。

シリアルプロッタを開くと、次のようなグラフが描画されます。

//image[250-PLOTTER-VOLUME][シリアルプロッター表示例][scale=0.9]

==== ボリュームモジュールのGrove端子ごとの動作状況
ボリュームモジュールの動作状況を次の表にまとめました。

//table[VolumeProgramTestResult][ボリュームプログラム動作状況（Nefry BT無印）]{
@<b>{無印コネクター名}	@<b>{動作状況}	@<b>{コメント}
-----------------------------
I2C(D0)	NO	常に0が表示される。
D2	NO	常に0が表示される。
A0	NO	常に4095が表示される。
A2	OK
//}

//table[VolumeProgramTestResultR2][ボリュームプログラム動作状況（Nefry BT R2）]{
@<b>{R2コネクター名}	@<b>{動作状況}	@<b>{コメント}
----------------------------
D0	NO	常に0が表示される。
D2	NO	常に0が表示される。
D5	NO	常に4095が表示される。
A0	OK	注：R2用のプログラムでは、A0ではなくA1を使います
//}

====[column] アナログ入力できるピンが少ない理由

Nefry BT無印ではGroveコネクターA2だけ、Nefry BT R2ではGroveコネクターA0だけが使えるという結果になりましたが、
これには理由があります。

0〜3.3Vの電圧を0〜4095の数値に変換する作業はADC（Analog Digital Converter）が行います。
Nefry BTのCPUであるESP-WROOM-32には２系統のADCがありADC1、ADC2と呼ばれています。
ADCが使えるGPIOピンは決まっています。どのピンにADC1とADC2が割り当てられているかを次表にまとめます。

//image[T060b-NefryBT-R1-ADC][ADC ピン割り当て（Nefry BT無印）][scale=0.4]

//image[T070b-NefryBT-R2-ADC][ADC ピン割り当て（Nefry BT R2）][scale=0.4]

ADC2には「WiFi機能を利用中は使えない」という制約があるので、通常使えるのはADC1だけになります。
Nefry BT無印ではGroveコネクターA2、Nefry BT R2ではA0（実際にはA1）だけでアナログ入力が行えます。

ADC2の制約について詳しい情報はこちらを参照してください。

@<href>{http://esp-idf.readthedocs.io/en/latest/api-reference/peripherals/adc.html}

====[/column]


== アナログ温度センサーモジュール
アナログ温度センサーモジュールはアナログ入力モジュールです。

//image[260-GROVE-MODULE-TEMPERATURE-Fukui][Groveアナログ温度センサー][scale=0.2]

 * Groveアナログ温度センサー @<href>{https://www.switch-science.com/catalog/806/}

ボリュームモジュールと同じプログラムで測定値を取得できます。

しかし、これでは0〜4095の数値が得られるだけで温度が何度なのかわかりません。
取得した数値を温度に変換するプログラムが必要になります。

ここではSeeed Studio社の商品紹介ページ（@<href>{hhttp://wiki.seeed.cc/Grove-Temperature_Sensor_V1.2/}）にあるプログラムを元にNefryで動くように修正しました。

=== アナログ温度センサーモジュールのプログラム

//emlist[NefryBT_GROVE_AnalogTemperatureSensor][Nefry BT R2向けに変更したアナログ温度センサープログラム]{
#include <Nefry.h>
#include <math.h>
const int B = 4275;           // B value of the thermistor
const int R0 = 100000;        // R0 = 100k
const int pinTempSensor = A1; // Grove - Temperature Sensor connect to A1

void setup()
{
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

=== 動作結果（アナログ温度センサーモジュール）

このプログラムを動作させるとシリアルモニタに次のような結果が出力されます。

//image[270-MONITOR-TEMPERATURE][アナログ温度センサープログラムのシリアルモニーター出力例][scale=0.9]{
//}

なんとなくそれらしい温度が表示されていますが、Arduinoにこの温度センサーを接続した時より1〜2度低いです。

Arduinoのプログラムは5Vでの動作を前提としているので、3.3Vだと少し定数の変更だと思われます。

このあたりがアナログセンサーを使うときの難しさです。数値の揺らぎの原因がなにかを切り分けるのは大変です。

I2Cのようなデジタルモジュールであれば、このような問題はかなり回避できます。
