= Groveのデジタル入力（ボタンモジュール）
Groveボタンモジュールはデジタル入力モジュールです。

//image[070-GROVE-MODULE-BUTTON-Fukui][Groveボタンモジュール][scale=0.3]{
//}
ボタンが押されている時は1（HIGH）を返し、離されている時は0（LOW）を返します。

 * Groveボタンモジュール: @<href>{https://www.switch-science.com/catalog/801/}

== ボタンモジュールのプログラム
シリアルモニタに、ボタンを押していないときは0、ボタンを押している間は1が表示されるプログラムです。

Nefry BT上のGroveソケットのD2と書かれたところにボタンモジュールを接続してください。

//emlist{
//Groveケーブルを接続するGroveコネクタを１つ選んで#define文に記載してください。
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

@<code>{setup()} ルーチン内で @<code>{pinMode(PIN, INPUT)} を実行して、ピンの入出力方向を@<b>{入力}に設定します。

次に @<code>{loop()} ルーチン内で @<code>{digitalRead(PIN)} を使ってピンの値を取得します。
ボタンの状態に応じて0か1が返されます。

返された値を @<code>{Serial.println()} 関数でシリアルモニタに出力します。

=== 動作結果
//image[080_MONITOR-BUTTON][ボタンプログラムのシリアルモニタ出力例][scale=0.9]{
//}
シリアルモニタにはこのように入力結果が表示されます。ボタンを押すとリアルタイムに1が表示されると思います。

== Groveコネクタとの動作状況
上記のプログラムが、4つあるGroveコネクタで動作するかどうかを表にまとめました。

//table[ButtonProgramTestResult][ボタンプログラム動作状況（Nefry BT無印）]{
@<b>{コネクタ名} 	@<b>{動作状況}	@<b>{コメント}
------------
I2C(D0)	NO	Nefry BT無印のD0コネクタは液晶ディスプレイと@<br>{}GPIOピンを共用しているため動作しません。@<br>{}また、Groveコネクタにモジュールを繋いでいると@<br>{}Nefry BTが起動しません。
D2	OK
A0	OK
A2	OK
//}

//table[ButtonProgramTestResultR2][ボタンプログラム動作状況（Nefry BT R2）]{
@<b>{R2コネクタ名}	@<b>{動作状況}	@<b>{コメント}
---------
D0	OK
D2	OK
D5	OK
A0	OK	注：R2のプログラムでは、A0ではなくA1を指定します。
//}

== 他のデジタル入力モジュール
他のデジタル入力モジュールには、タッチセンサ、傾きセンサ、磁気スイッチ、水センサなどがあります。

いずれも上記のプログラムがそのまま使えます。

//image[090_GROVE-MODULE-TOUCH-Fuki][Groveタッチセンサモジュール][scale=0.3]{
//}

 * Groveタッチセンサ: @<href>{https://www.switch-science.com/catalog/811/}
 * Grove傾きセンサ: @<href>{https://www.switch-science.com/catalog/803/}
 * Grove磁気スイッチ: @<href>{https://www.switch-science.com/catalog/809/}
 * Grove水センサ: @<href>{https://www.switch-science.com/catalog/817/}
