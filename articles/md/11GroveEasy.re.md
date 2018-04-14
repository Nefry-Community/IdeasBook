## Groveポートを使ってみよう

このページではNefry BTにGPIOを使ってGrove LEDを点滅する仕組みを説明します。

GPIOとはデジタル信号を出し入れする仕組みのことです。GPIOをつかうことで、Nefry BTからさまざまなセンサーに合わせたデジタル信号の読み取り（入力）ができたり、Nefry BTからデジタル信号を送り（出力）モーターを動かしたりLEDを光らせることができます。

## Nefry BTのGPIOの位置

Nefry BTではGPIOを使える以下のGPIOピンとGroveポートが搭載されています。

![GPIOピンとGroveポート](11GroveEasy_01.jpg)

今回はGroveポートにGrove LEDを差し込んでGPIOを体験してみましょう。

## Grove LED 赤 を購入しましょう

たとえば、スイッチサイエンスのオンラインショップ ( https://www.switch-science.com/catalog/1254/ ) で購入できます。

![Grove LED 赤の内容物](11GroveEasy_02.jpg)

このように、

* Groveの基板部分
* LED　赤
* Groveケーブル

が入っています。

![付属のLEDのとりつけ](11GroveEasy_03.jpg)

付属のLEDは配線の長短がなく分かりにくいですが、LED内のアソード・カソードの位置を見ながら差し込んでみましょう。

## Grove LEDをNefry BTをつなぐ

続いて、Grove LEDをNefry BTをつなぎます。

![Groveケーブル（写真左）](11GroveEasy_04.jpg)

Groveケーブルを確認します。

![GroveポートのD2に差し込んだ図](11GroveEasy_05.jpg)

GroveポートのD2にGroveケーブル差し込みます。

![Grove LED側](11GroveEasy_06.jpg)

Grove LEDにもGroveケーブル差し込みます。

## プログラムの書き込み

初期状態で書かれている現状のコードを削除して、次のコードに差し替えましょう。

![次のコードに差し替えたウインドウ](11GroveEasy_07.png)

このコードは https://github.com/Nefry-Community/IdeaBookExample/tree/master/examples にある、 11GroveEasy のサンプルからコピーペーストすることが可能です。

```c
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
```

## コードの説明

```c
void setup() {
  // SW有効化
  Nefry.enableSW();
  // 差し込んだD2ポートを出力(OUTPUT)にする指示
  pinMode(D2, OUTPUT);
}
```

起動時に行いたい動作 setup 関数ではSW有効化と差し込んだD2ポートを出力(OUTPUT)にする指示をしています。

```c
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
```

以降は、起動後に繰り返す loop 関数の動きをです。SWを押した時 ```Nefry.readSW``` で判定し、押したときだけ、 ```digitalWrite(D2, HIGH);``` でGrove LEDを差し込んだ D2 にデジタル信号が出力され点灯し、```Nefry.ndelay(1000);``` で1秒待ってから、 ```digitalWrite(D2, LOW);``` で消灯します。

## 確認

実際に書き込んで確認してみましょう。

![プログラムのとおりGrove LEDが点灯・消灯](11GroveEasy_08.jpg)

無事にプログラム書き込みが終わると、Nefry BTの内蔵スイッチを押すとプログラムのとおりGrove LEDが点灯・消灯します。
