
= ティスプレイに好きな画像を表示させてみよう
この章では、任意の画像をNefry BTのディスプレイに表示させる方法を紹介します。

同時期に発売するNefryチュートリアル本「きょうからのNefry」で、ディスプレイの基本の使い方と文字を表示させる方法について説明していますのでご覧ください。

Nefry BTのディスプレイの表示は@<tt>{NefryDisplay.h}をincludeすることでプログラム可能になります。

== 本題に入る前に
@<tt>{NefryDisplay.h}ではディスプレイに関する便利な関数が色々準備されています。

//image[display1][ディスプレイライブラリの例][scale=0.8]{
//}
たとえば、このように@<tt>{NefryDisplay.print()}を使うと、簡単にディスプレイに好きな文字列を表示することができます。

//image[display5][図形を表示する][scale=0.8]{
//}
また、@<tt>{NefryDisplay.drawCircle()}や@<tt>{NefryDisplay.drawHorizontalLine()}、@<tt>{NefryDisplay.drawVerticalLine()}を使うと図形をディスプレイに表示することができます。

難しいディスプレイ制御の知識不要でこのような表示が簡単に関数で行えるので、ログの出力をディスプレイ上で行ったり、簡易的なデータを表示したりと役立つこと間違いなしです。

== 好きな画像を表示させる
プログラム上で描画する内容を動的に生成する方法もありますが、表示したい画像が手元にある場合は画像をXBMファイルに変換し、@<tt>{NefryDisplay.drawXbm()}で表示させる方法もあります。

この関数を使うと、任意の画像をディスプレイに表示させることができます。

=== XBMとは
XBM（＝X BitMap）はビットマップの一種です。データの中身はC言語のコードになっていて、char配列で画像を表現するという珍しい特徴を持っています。

//emlist{
#define pokiiio_width 128
#define pokiiio_height 64
static char pokiiio_bits[] = {0x7F, 0xFF, 0xFF, ... };
//}

XBMファイルをテキストエディタで開くと、このようなソースになっていることがあります。

@<tt>{pokiiio_width}と@<tt>{pokiiio_height}は画像のサイズを表し、@<tt>{pokiiio_bits}は画像そのもののデータを表しています。
画像の1ピクセル毎に、黒いピクセルは1、白いピクセルは0といったように2値で表現し、それを8ピクセル（＝8ビット）毎に16進数にまとめ、さらにそれを配列にすることで画像全体を表現するようになっています。

=== XMBファイルを作ってみる

//image[display7][XBMファイル作成手順][scale=0.8]{
//}
大まかな流れはこんな感じです。

作成するときは次のポイントを抑えます。

 * Nefry BTのディスプレイのサイズは128x64なので、そのサイズ（もしくはそれ以下）にリサイズする必要がある
 * @<code>{NefryDisplay.drawXbm()}では、黒いピクセルが白く表示されるので、XBMファイル生成の前段で色の反転を行っている
 * XBMへの変換はOnline-Utility.org（@<href>{https://www.online-utility.org/image/convert/to/XBM}）で変換できる

この3つさえ抑えていれば、簡単にXBMファイルを生成することができます。

今回は、私のTwitter（@pokiiio）のアイコンを変換してみました。

Nefry BTでのプログラムで必要になるのは、XBMファイルのchar配列のコードなので、XBMファイルをテキストエディタなどで開き、コピーしておきます。


//emlist{
#include <NefryDisplay.h>

char pokiiio[] = {（長いので省略）}; // XBMファイル内の配列をここで宣言する

void setup() {
  NefryDisplay.setAutoScrollFlg(true);
  NefryDisplay.autoScrollFunc(pokioPrint);
}

void loop() {

}

void pokioPrint() {
  NefryDisplay.drawXbm(0, 0, 128, 64, pokiiio);
}
//}


画像データの配列をプログラム内で宣言し、@<code>{NefryDisplay.drawXbm()}で指定することで画像を表示できます。

実際の配列の中身は、長さの都合で省略しています。

=== 実際に表示させてみる
Nefry BTの電源を入れて起動すると、このような感じでTwitterアイコンが表示されます。

//image[display6][Twitterアイコンを表示][scale=0.8]{
//}

ロゴやマークの表示やイラストの表示には最適です。みなさんも是非お試しください！
