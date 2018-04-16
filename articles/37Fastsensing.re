= Fastsensingにデータを送ってみる

Fastsensing（@<href>{https://fastsensing.com/ja/}）は、専用のデバイスやマイコンボードからのセンサーデータを受信し、グラフ化や異常検知をしてくれるサービスです。

この章では、NefryからFastSensingライブラリをつかって、Fastsensingにデータを送り、それを可視化する方法を紹介します。

//image[fastsensing_top][Fastsensingのホームページ]{
//}

== アカウントをつくろう

ホームページ上部の@<tt>{アカウント作成}から、アカウントを作ります。

//image[fastsensing_create_account][アカウント作成]{
//}

アカウント作成後に、コンソール画面の@<tt>{デバイス}タブなかに@<tt>{デバイスの登録}というボタンがありますが、こちらはファストセンシング対応デバイスの登録専用になっています。

通常は専用のデバイスからセンサーデータをアップロードするのですが、今回のNefry BTからのデータのアップロードを行うため、ここのメニューは使いません。

//image[fastsensing_add_device][今回は「ファストセンシング対応デバイスの登録」は行わない]{
//}

ファストセンシング対応デバイスの登録代わりに、ファストセンシング・ディベロッパー・プログラム（@<href>{https://fastsensing.com/ja/developer/}）をつかって仮想のデバイスを登録して、さまざまなマイコンボードからデータをアップロードすることができるようになります。

//image[fastsensing_developer_program][ファストセンシング・ディベロッパー・プログラム]{
//}

ファストセンシング・ディベロッパー・プログラムのページ上の@<tt>{スタブデバイスの追加}のリンクから、Fastsensingのコンソールに遷移でき、仮想のデバイスを登録することができます。

//image[fastsensing_add_stub_device][スタブデバイスの追加]{
//}

ここから@<tt>{スタブデバイス}を追加すると、1つのデバイスに対して3つの独立したチャネルが割り当てられて、それぞれのチャネルに対してセンサーデータをアップロードすることができます。

//image[fastsensing_detail][スタブデバイスの詳細]{
//}

コンソール（@<href>{https://console.fastsensing.com/devices}）に登録した@<tt>{スタブデバイス}が表示されているので、それを選択するとデバイスの詳細画面が表示されます。

そこで、デバイスと各チャネルのトークンが表示されます。

Nefry BTのFastsensingライブラリでは、これらのトークンをつかってセンサーデータをアップロードします。


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


@<tt>{NefryFastSensing.h}をincludeした上で、@<tt>{NefryFastSensing}クラスのインスタンスを宣言します。

@<tt>{begin()}関数で、デバイストークンとチャネルトークンを使って初期化をすれば準備完了です。

@<tt>{setValue()}関数で、送り先のチャネルと、チャネルに送るデータをセットして、@<tt>{push()}でFastsensingに送信します。


== 送ったデータを見てみる


送ったデータはFastsensingのサイト上でグラフ化ができます。



//image[fastsensing_create_view][ビューの新規作成]{
//}




登録した@<tt>{スタブデバイス}のチャンネルの詳細画面から、@<tt>{ビュー}メニューで可視化の方法を選択できます。



//image[fastsensing_view][グラフ化したデータ]{
//}




例えば、このメニューで@<tt>{グラフ}を選ぶと、このようなグラフを表示することができます。

グラフの他にも、@<tt>{リアルタイムグラフ}、@<tt>{イメージマップ}、@<tt>{パネル}、@<tt>{表}があります。色々な方法で可視化にチャレンジしてみて下さい！
