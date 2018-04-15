= ボリュームモジュール
ボリュームモジュール（可変抵抗モジュール）はアナログ入力モジュールです。
Nefry BTでは3.3Vをモジュールに供給しているので、ノブを回すと0Vから3.3Vまで電圧が連続的に変化します。
ノブを時計回りにいっぱい回すと0Vで反時計回りにいっぱい回すと3.3Vが出力されます。

//image[230-GROVE-MODULE-VOLUME-Fukui][Groveボリュームモジュール][scale=0.4]

 * Groveボリューム https://www.switch-science.com/catalog/805/

==== ボリュームモジュールのプログラム
ボリュームモジュールから読み込んだ値をシリアルモニターに表示するプログラムです。
値の読み込みは@<code>{analogRead(PIN)}関数で行なっています。
モジュールを接続するGroveコネクターに合わせて、PINの@<code>{#define}宣言をしてください。

//list[Nefry_GROVE_RotaryAngleSensor][ボリュームのプログラム]{
#include <Nefry.h>
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
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


Nefry BT無印ではGroveコネクターA2だけ、Nefry BT R2ではGroveコネクターA0だけが使えるという結果になりましたが、
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

//table[ADCPinAssignR2][ADC ピン割り当て（Nefry BT R2）]{
@<b>{R2コネクター名}	@<b>{ADC}
-----------------
D0	-
D2	-
D5	ADC2
A0	ADC1
//}


ADC2には「WiFi機能を利用中は使えない」という制約があるので、通常使えるのはADC1だけになります。
Nefry BT無印ではGroveコネクターA2、Nefry BT R2ではA0（実際にはA1）だけでアナログ入力が行えます。

ADC2の制約について詳しい情報はこちらを参照してください。

http://esp-idf.readthedocs.io/en/latest/api-reference/peripherals/adc.html

=== アナログ温度センサーモジュール
アナログ温度センサーモジュールはアナログ入力モジュールです。

//image[260-GROVE-MODULE-TEMPERATURE-Fukui][Groveアナログ温度センサー][scale=0.4]

 * Groveアナログ温度センサー https://www.switch-science.com/catalog/806/

ボリュームモジュールと同じプログラムで測定値を取得できます。
しかし、これでは0〜4095の数値が得られるだけで温度が何度なのかわかりません。
取得した数値を温度に変換するプログラムが必要になります。
変換方法は、Groveモジュールの販売サイトや、Groveモジュールで使用している温度センサー部品のサイトにデータシート（仕様書）
が掲載されているのでそれを見れば詳細がわかりますが、かなり難解です。
Groveモジュールを使うだけなら、販売店サイトで公開されているプログラムを利用するのが手軽で早道です。

==== アナログ温度センサーモジュールのプログラム
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
//listnum[NefryBT_GROVE_AnalogTemperatureSensor][Nefry BT R2向けに変更したアナログ温度センサープログラム]{
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

//image[270-MONITOR-TEMPERATURE][アナログ温度センサープログラムのシリアルモニーター出力例][scale=0.9]

なんとなくそれらしい温度が表示されていますが、Arduinoにこの温度センサーを接続した時より1〜2度低いようです。
Arduinoのプログラムは5Vでの動作を前提としているので、3.3Vだと少し定数の変更が必要なのかもしれません。
このあたりがアナログセンサーを使うときの難しさです。数値の揺らぎがNefry BTの電子回路から来ているのか、
電圧の違いによるセンサーの挙動の違いなのか、プログラムに問題があるのかなど、どの原因かを切り分けるのは大変です。
I2Cのようなデジタルモジュールであれば、このような問題はかなり回避できます。
