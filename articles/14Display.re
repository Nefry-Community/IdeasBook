
= ティスプレイを触ってみる


Nefry BTのディスプレイの表示も@<tt>{NefryDisplay.h}をincludeすることでプログラム可能になります。


== 簡単な使い方


たとえば、このように@<tt>{NefryDisplay#print()}を使うと、簡単にディスプレイに好きな文字列を表示することができます。


//emlist{
#include <NefryDisplay.h>

void setup() {
  NefryDisplay.print("POKIO");
  NefryDisplay.print("KEIKYU");
}

void loop() {

}
//}


//image[display1][ディスプレイライブラリの例]{
//}




もし、ディスプレイの横幅より長い文字列を入力しても、自動でスクロール表示してくれます。


//emlist{
#include <NefryDisplay.h>

void setup() {
  NefryDisplay.print("POKIOPOKIOPOKIOPOKIO");
  NefryDisplay.print("KEIKYUKEIKYUKEIKYUKEIKYU");
}

void loop() {

}
//}


//image[display2][長い文字列を表示したとき]{
//}




ただし、ディスプレイに表示できるのは3行までで、4行以上表示しようとすると、最後に表示しようとした3行分が表示されます。


//emlist{
#include <NefryDisplay.h>

void setup() {
  NefryDisplay.print("P");
  NefryDisplay.print("O");
  NefryDisplay.print("K");
  NefryDisplay.print("I");
  NefryDisplay.print("O");
}

void loop() {

}
//}


//image[display3][4行以上の文字列を表示したとき]{
//}




たとえば、「P」「O」「K」「I」「O」と表示しようとしたときは、最後の3行である @<strong>{「K」「I」「O」} だけが表示される事になります。



このように、@<tt>{NefryDisplay#print()}は非常に便利な関数です。実行中のプログラムのログを表示したり、表示した文字列が3行以下の場合におすすめです。


== 高度な使い方


もう少し、凝った表示をしたいときは、@<tt>{NefryDisplay#autoScrollFunc()}で表示したい要素を記述した関数を渡す方法があります。



たとえば、好きな位置に文字列を表示させたいときは、@<tt>{NefryDisplay#drawString()}を使います。


//emlist{
#include <NefryDisplay.h>

void setup() {
  NefryDisplay.setAutoScrollFlg(true);
  NefryDisplay.autoScrollFunc(pokioPrint);
}

void loop() {

}

void pokioPrint() {
  NefryDisplay.drawString(0, 0, "POKIO");
  NefryDisplay.drawString(20, 15, "POKIO");
  NefryDisplay.drawString(40, 30, "POKIO");
  NefryDisplay.drawString(60, 45, "POKIO");
}
//}


//image[display4][好きな位置に文字を表示する]{
//}




このように、「POKIO」という文字を好きな位置に配置できました。また、@<tt>{NefryDisplay#autoScrollFunc()}を使う場合は@<tt>{Nefry PrintDialog}という固定で表示される文字列もないので、ディスプレイ全体をフルに使うことができます。



もちろん、文字列以外にも図形を表示できます。


//emlist{
#include <NefryDisplay.h>

void setup() {
  NefryDisplay.setAutoScrollFlg(true);
  NefryDisplay.autoScrollFunc(pokioPrint);
}

void loop() {

}

void pokioPrint() {
  NefryDisplay.drawCircle(10, 10, 10);
  NefryDisplay.fillCircle(40, 40, 20);
  NefryDisplay.drawRect(40, 10, 20, 20);
  NefryDisplay.fillRect(70, 30, 30, 30);
  NefryDisplay.drawHorizontalLine(100, 10, 15);
  NefryDisplay.drawHorizontalLine(100, 15, 15);
  NefryDisplay.drawVerticalLine(105, 5, 15);
  NefryDisplay.drawVerticalLine(110, 5, 15);
}
//}


//image[display5][図形を表示する]{
//}




このように、少し凝った表示も簡単に実装することができます。


== 好きな画像を表示させる


プログラム上で描画する内容を動的に生成する方法もありますが、表示したい画像が手元にある場合、画像をXBMファイルに変換し、@<tt>{NefryDisplay#drawXbm()}で表示させる方法もあります。この関数を使うと、任意の画像をディスプレイに表示させる事ができます。


=== XBMとは


XBM（＝X BitMap）はビットマップの一種で、データの中身はC言語のコードになっていて、char配列で画像を表現するという珍しい特徴を持っています。


//emlist{
#define pokiiio_width 128
#define pokiiio_height 64
static char pokiiio_bits[] = {0x7F, 0xFF, 0xFF, ... };
//}


XBMファイルをテキストエディタで開くと、このようなソースになっていることがあります。@<tt>{pokiiio_width}と@<tt>{pokiiio_height}は画像のサイズを表し、@<tt>{pokiiio_bits}は画像そのもののデータを表しています。画像の1ピクセル毎に、黒いピクセルは1、白いピクセルは0といったように2値で表現し、それを8ピクセル（＝8ビット）毎に16進数にまとめ、さらにそれを配列にすることで画像全体を表現するようになっています。


=== XMBファイルを作ってみる


大まかな流れはこんな感じです。



//image[display7][XBMファイル作成手順]{
//}




ポイントは3点で、

 * Nefry BTのディスプレイのサイズは128x64なので、そのサイズ（もしくはそれ以下）にリサイズする必要がある
 * @<tt>{NefryDisplay#drawXbm()}では、黒いピクセルが白く表示されるので、XBMファイル生成の前段で色の反転を行っている
 * XBMへの変換はOnline-Utility.org（https://www.online-utility.org/image/convert/to/XBM）で変換できる



これさえ抑えていれば、簡単にXBMファイルを生成することができます。



今回は、私のTwitter（@pokiiio）のアイコンを変換してみました。Nefry BTでのプログラムで必要になるのは、XBMファイルのchar配列のコードなので、XBMファイルをテキストエディタなどで開き、コピーしておきます。


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


画像データの配列のプログラム内で宣言し、@<tt>{NefryDisplay#drawXbm()}でそれを指定することで画像を表示できます。実際の配列の中身は、長さの都合で省略しています。


=== 実際に表示させてみる


Nefry BTの電源を入れて、起動するとこのような感じでTwitterアイコンが表示されます。



//image[display6][Twitterアイコンを表示]{
//}




ロゴやマークの表示や、イラストを表示するには最適です。みなさんも是非お試しください！

