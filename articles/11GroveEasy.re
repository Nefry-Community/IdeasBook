
== Groveポートを使ってみよう


このページではNefry BTにGPIOを使ってGrove LEDを点滅する仕組みを説明します。



GPIOとはデジタル信号を出し入れする仕組みのことです。GPIOをつかうことで、Nefry BTからさまざまなセンサーに合わせたデジタル信号の読み取り（入力）ができたり、Nefry BTからデジタル信号を送り（出力）モーターを動かしたりLEDを光らせることができます。


== Nefry BTのGPIOの位置


Nefry BTではGPIOを使える以下のGPIOピンとGroveポートが搭載されています。



//image[11GroveEasy_01][GPIOピンとGroveポート]{
//}




今回はGroveポートにGrove LEDを差し込んでGPIOを体験してみましょう。


== Grove LED 赤 を購入しましょう


たとえば、スイッチサイエンスのオンラインショップ ( https://www.switch-science.com/catalog/1254/ ) で購入できます。



//image[11GroveEasy_02][Grove LED 赤の内容物]{
//}




このように、

 * Groveの基板部分
 * LED　赤
 * Groveケーブル



が入っています。



//image[11GroveEasy_03][付属のLEDのとりつけ]{
//}




付属のLEDは配線の長短がなく分かりにくいですが、LED内のアソード・カソードの位置を見ながら差し込んでみましょう。


== Grove LEDをNefry BTをつなぐ


続いて、Grove LEDをNefry BTをつなぎます。



//image[11GroveEasy_04][Groveケーブル（写真左）]{
//}




Groveケーブルを確認します。



//image[11GroveEasy_05][GroveポートのD2に差し込んだ図]{
//}




GroveポートのD2にGroveケーブル差し込みます。



//image[11GroveEasy_06][Grove LED側]{
//}




Grove LEDにもGroveケーブル差し込みます。


== プログラムの書き込み


初期状態で書かれている現状のコードを削除して、次のコードに差し替えましょう。



//image[11GroveEasy_07][次のコードに差し替えたウインドウ]{
//}




このコードは https://github.com/Nefry-Community/IdeaBookExample/tree/master/examples にある、 11GroveEasy のサンプルからコピーペーストすることが可能です。


//emlist[][c]{
#include <Nefry.h>

void setup() {
  // SW有効化
  Nefry.enableSW();
  // 差し込んだD2ポートを出力(OUTPUT)にする指示
  pinMode(D2, OUTPUT);
}

void loop() {
  // SWを押した時を判定する Nefry.readSW
  if (Nefry.readSW()) {
    // Grove LEDが点灯
    digitalWrite(D2, HIGH);
    // 押されたら1秒待つ
    Nefry.ndelay(1000);
    // Grove LEDが消灯
    digitalWrite(D2, LOW);
  }
}
//}

== コードの説明

//emlist[][c]{
void setup() {
  // SW有効化
  Nefry.enableSW();
  // 差し込んだD2ポートを出力(OUTPUT)にする指示
  pinMode(D2, OUTPUT);
}
//}


起動時に行いたい動作 setup 関数ではSW有効化と差し込んだD2ポートを出力(OUTPUT)にする指示をしています。


//emlist[][c]{
void loop() {
  // SWを押した時を判定する Nefry.readSW
  if (Nefry.readSW()) {
    // Grove LEDが点灯
    digitalWrite(D2, HIGH);
    // 押されたら1秒待つ
    Nefry.ndelay(1000);
    // Grove LEDが消灯
    digitalWrite(D2, LOW);
  }
}
//}


以降は、起動後に繰り返す loop 関数の動きをです。SWを押した時 @<tt>{Nefry.readSW} で判定し、押したときだけ、 @<tt>{digitalWrite(D2, HIGH);} でGrove LEDを差し込んだ D2 にデジタル信号が出力され点灯し、@<tt>{Nefry.ndelay(1000);} で1秒待ってから、 @<tt>{digitalWrite(D2, LOW);} で消灯します。


== 確認


実際に書き込んで確認してみましょう。



//image[11GroveEasy_08][プログラムのとおりGrove LEDが点灯・消灯]{
//}




無事にプログラム書き込みが終わると、Nefry BTの内蔵スイッチを押すとプログラムのとおりGrove LEDが点灯・消灯します。

