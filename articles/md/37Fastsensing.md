# Fastsensingにデータを送ってみる
Fastsensing（https://fastsensing.com/ja/）は、専用のデバイスやマイコンボードからのセンサーデータを受信し、グラフ化や異常検知をしてくれるサービスです。この章では、NefryからFastSensingライブラリをつかって、Fastsensingにデータを送り、それを可視化する方法を紹介します。


![Fastsensingのホームページ](fastsensing_top)


## スタブデバイスの追加


通常は専用のデバイスからセンサーデータをアップロードするのですが、ファストセンシング・ディベロッパー・プログラム（https://fastsensing.com/ja/developer/）をつかって、さまざまなマイコンボードからデータをアップロードすることができます。


![ファストセンシング・ディベロッパー・プログラム](fastsensing_developer_program)


ファストセンシング・ディベロッパー・プログラムのページ上の`スタブデバイスの追加`のリンクから、Fastsensingのコンソールに遷移でき、仮想のデバイスを登録することができます。


![スタブデバイスの追加](fastsensing_add_stub_device)


ここから`スタブデバイス`を追加すると、1つのデバイスに対して3つの独立したチャネルが割り当てられて、それぞれのチャネルに対してセンサーデータをアップロードすることができます。


![スタブデバイスの詳細](fastsensing_detail)


コンソール（https://console.fastsensing.com/devices）に登録した`スタブデバイス`が表示されいるので、それを選択するとデバイスの詳細画面が表示されます。そこで、デバイスと各チャネルのトークンが表示されます。Nefry BTのFastsensingライブラリでは、これらのトークンをつかってセンサーデータをアップロードします。


## データを送ってみる


A0ピンのアナログ入力値を読み取りアップロードしてみましょう。


```
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
```


`NefryFastSensing.h`をincludeした上で、`NefryFastSensing`クラスのインスタンスを宣言します。`begin()`関数で、デバイストークンとチャネルトークンを使って初期化をすれば準備完了です。`setValue()`関数で、送り先のチャネルと、チャネルに送るデータをセットして、`push()`でFastsensingに送信します。


## 送ったデータを見てみる


送ったデータはFastsensingのサイト上でグラフ化ができます。


![ビューの新規作成](fastsensing_create_view)


登録した`スタブデバイス`のチャンネルの詳細画面から、`ビュー`メニューで可視化の方法を選択できます。


![グラフ化したデータ](fastsensing_view)



例えば、このメニューで`グラフ`を選ぶと、このようなグラフを表示することができます。
