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
