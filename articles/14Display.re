
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

