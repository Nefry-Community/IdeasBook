= Groveのデジタル入力（ボタンモジュール）
ボタンモジュールはデジタル入力モジュールです。

ボタンが押されている時は１（HIGH）を返し、離されている時は０（LOW）を返します。
//image[070-GROVE-MODULE-BUTTON-Fukui][Groveボタンモジュール][scale=0.3]{
//}

 * Groveボタン @<href>{https://www.switch-science.com/catalog/801/}

== ボタンモジュールのプログラム
シリアルモニターに、通常は0が表示され、ボタンを押している間だけ1が表示されるプログラムです。

GroveソケットのD2と書かれたところにGroveモジュールを接続してください。

//emlist{
//Groveケーブルを接続するGroveコネクターを１つ選んで#define文に記載してください。
// Nefry BT無印の場合： D0, D2, A0, A2　(注：D0を使うことはできません。)
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

=== プログラム説明

プログラムの説明をしていきます。

@<code>{setup()} ルーチン内で @<code>{pinMode(PIN, INPUT)} を実行してピンの入出力方向を@<b>{入力}に設定します。

次に @<code>{loop()} ルーチン内で @<code>{digitalRead(PIN)} を使ってピンの値を取得します。
ボタンの状態に応じて0か1が返されます。

返された値を @<code>{Serial.println()} 関数でシリアルモニターに出力します。

=== 動作結果

シリアルモニターには次のように入力結果が表示されます。

//image[080_MONITOR-BUTTON][ボタンプログラムのシリアルモニター出力例][scale=0.9]{
//}

== Groveコネクターごとの動作状況
上記のプログラムが、4つあるGroveコネクターで動作するかどうかを表にまとめました。

//table[ButtonProgramTestResult][ボタンプログラム動作状況（Nefry BT無印）]{
@<b>{コネクター名} 	@<b>{動作状況}	@<b>{コメント}
------------
I2C(D0)	NO	Nefry BT無印のD0コネクターは液晶ディスプレイと@<br>{}GPIOピンを共用しているため動作しません。@<br>{}また、Groveコネクターにモジュールを繋いでいると@<br>{}Nefry BTが起動しません。
D2	OK
A0	OK
A2	OK
//}

//table[ButtonProgramTestResultR2][ボタンプログラム動作状況（Nefry BT R2）]{
@<b>{R2コネクター名}	@<b>{動作状況}	@<b>{コメント}
---------
D0	OK
D2	OK
D5	OK
A0	OK	注：R2用のプログラムでは、A0ではなくA1を使います。
//}

== 他のデジタル入力モジュール
他のデジタル入力モジュールには、タッチセンサー、傾きセンサー、磁気スイッチ、水センサーなどがあります。

いずれも上記のプログラムがそのまま使えます。

 * Groveタッチセンサー @<href>{https://www.switch-science.com/catalog/811/}
 * Grove傾きセンサー @<href>{https://www.switch-science.com/catalog/803/}
 * Grove磁気スイッチ @<href>{https://www.switch-science.com/catalog/809/}
 * Grove水センサー @<href>{https://www.switch-science.com/catalog/817/}

//image[090_GROVE-MODULE-TOUCH-Fuki][Groveタッチセンサーモジュール][scale=0.3]{
//}
