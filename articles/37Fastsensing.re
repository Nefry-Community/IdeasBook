
= Fastsensingにデータを送ってみる


Fastsensing（https://fastsensing.com/ja/）は、専用のデバイスやマイコンボードからのセンサーデータを受信し、グラフ化や異常検知をしてくれるサービスです。



//image[fastsensing_top][Fastsensingのホームページ]{
//}



== スタブデバイスの追加


通常は専用のデバイスからセンサーデータをアップロードするのですが、ファストセンシング・ディベロッパー・プログラム（https://fastsensing.com/ja/developer/）をつかって、さまざまなマイコンボードからデータをアップロードすることができます。



//image[fastsensing_developer_program][ファストセンシング・ディベロッパー・プログラム]{
//}




ファストセンシング・ディベロッパー・プログラムのページ上の@<tt>{スタブデバイスの追加}のリンクから、Fastsensingのコンソールに遷移でき、仮想のデバイスを登録することができます。



//image[fastsensing_add_stub_device][スタブデバイスの追加]{
//}




ここから@<tt>{スタブデバイス}を追加すると、1つのデバイスに対して3つの独立したチャネルが割り当てられて、それぞれのチャネルに対してセンサーデータをアップロードすることができます。



//image[fastsensing_detail][スタブデバイスの詳細]{
//}




コンソール（https://console.fastsensing.com/devices）に登録した@<tt>{スタブデバイス}が表示されいるので、それを選択するとデバイスの詳細画面が表示されます。そこで、デバイスと各チャネルのトークンが表示されます。Nefry BTのFastsensingライブラリでは、これらのトークンをつかってセンサーデータをアップロードします。


== データを送ってみる


A0ピンのアナログ入力値を読み取りアップロードしてみましょう。


//emlist{
// FastSensingライブラリを使うのに必要
#include <NefryFastSensing.h>

// デバイスのトークンとチャネル1〜3のトークン
#define DEVICE_TOKEN "xxxxx"
#define CHANNEL1_TOKEN "xxxxx"
#define CHANNEL2_TOKEN "xxxxx"
#define CHANNEL3_TOKEN "xxxxx"

// Fastsensingと通信するために必要なインスタンス
NefryFastSensing fastSensing;

void setup() {
  // トークンを使って初期化
  fastSensing.begin(DEVICE_TOKEN, CHANNEL1_TOKEN, CHANNEL2_TOKEN, CHANNEL3_TOKEN);
  Nefry.println("FastSensing initialized");
}

void loop() {
  // A0ピンの値をセットします。一つ目の引数はチャネル（0〜2）を指定しています。
  fastSensing.setValue(0, analogRead(A0));

  // セットしたデータをFastsensingに送信します
  fastSensing.push();
  Nefry.println("Data pushed");

  delay(10000);
}
//}

== 送ったデータを見てみる


送ったデータはFastsensingのサイト上でグラフ化ができます。



//image[fastsensing_create_view][ビューの新規作成]{
//}




登録した@<tt>{スタブデバイス}のチャンネルの詳細画面から、@<tt>{ビュー}メニューで可視化の方法を選択できます。



//image[fastsensing_view][グラフ化したデータ]{
//}




例えば、このメニューで@<tt>{グラフ}を選ぶと、このようなグラフを表示することができます。

