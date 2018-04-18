= Nefry クラウド × IFTTT 連携でお手軽IoTはじめよう！

@<strong>{Nefryクラウド}を使えばネットワークからNefryを動かすことができます。

今回はNefryクラウドとIFTTTを使ってお手軽IoTをしてみようと思います！

== 完成図

Nefryクラウドを使った一例として、@<strong>{TwitterからNefryに通知を送る}プログラムを作ってみます。

//image[36NefryCloud_05][image.png (141.9 kB)][scale=0.8]{
//}

IFTTTでTwitterで自分がツイートしたら、Nefryクラウドを経由してNefryにメッセージをおくるものを作っていきます。


== Nefryクラウドのアカウントつくろう

@<b>{注意：セキュリティが強固ではないので秘匿性の高いデータは扱わないでください。}

まず、次のURLを入力してNefryクラウドにアクセスしてみましょう。

@<href>{http://cloud.nefry.studio:1880/nefrysetting/}

//image[36NefryCloud_02][アカウントを作成します][scale=0.8]{
//}

アクセスできると、このような画面が現れます。

任意のUsernameと確実に届くメールアドレスを入力して、Sendを押します。

//image[36NefryCloud_03][成功画面][scale=0.8]{
//}

問題がなければ、次のような画面が現れます。エラーがあれば、再度入力してください。

//image[36NefryCloud_04][このようなメールが届きます][scale=0.8]{
//}

成功すると、入力したメールアドレスにこのような@<strong>{APIKey}が届きます。

これは、Nefryに書き込むプログラムに使うので覚えておきましょう。

※メールが届かない場合は、入力したメールアドレスが間違っているか、もしくは迷惑メールのフォルダに入っているのかもしれません。

== Nefryクラウドのライブラリをインストール

NefryでNefryクラウドを使うためにライブラリをインストールします。

次のURLからライブラリをダウンロードできます。

@<href>{https://drive.google.com/file/d/15wHNn3ceyG7f0QEh2PPrnWGt0kIyStfW/view}

ダウンロードしたzipファイルをArduino IDEのライブラリに追加していきます。

//image[36NefryCloud_06][ZIP形式のライブラリをインストールをクリックします][scale=0.8]{
//}

Arduino IDE上で「スケッチ」→「ライブラリをインクルード」→「ZIP形式のライブラリをインストール」と順にクリックします。

//image[36NefryCloud_07][ダウンロードしたZipファイルを指定します][scale=0.8]{
//}

別ウィンドウが表示されるので、そこでダウンロードしたzipファイルをクリックします。

//image[36NefryCloud_08][インストールの確認をしましょう][scale=0.8]{
//}

すると、インストールが開始されます。

しばらくするとNefryクラウドのライブラリが追加されているはずです。

それが確認できれば準備は完了です！

== TwitterからNefryに通知を送る-Nefryのプログラム-

ライブラリのインストールが終わったところで、Nefryに入れるプログラムを説明します。

今回はNefryクラウドからうけとったメッセージが、「Nefry」だったら「Hello World」と返すプログラムを作成しました。

次のソースコードの@<code>{nefryCloud.begin("Username","Apikey");}のユーザ名とAPI Keyを書き換えたらArduino IDEを使い、Nefryに書き込んでください。

//emlist{

#include <Nefry.h>
//Nefryクラウドのライブラリ
#include <NefryCloud.h>

NefryCloud nefryCloud;

void onpush(String message);

void setup() {
//登録したUserneme,メールで受け取ったApikeyを入力してください
  nefryCloud.begin("Username","Apikey");
  nefryCloud.on(onpush);
}

void loop() {
  nefryCloud.loop();
}

//Nefryクラウドから通知がとどきます
void onpush(String message) {
  Nefry.print("onpush : ");
  Nefry.println(message);
//Nefryという文字列がきたときシリアルモニタに「Hello」と表示
  if(message.equals("Nefry")){
     Nefry.println("Hello");
  }
}
//}

=== プログラム説明

この@<code>{nefryCloud.begin()}関数で、Nefryクラウドの設定を行います。

ユーザ名とAPI Keyをそれぞれ書き換えましょう。

@<code>{nefryCloud.on(onpush)}関数で、Nefryクラウドからメッセージが届いたときに実行される関数を指定します。

下の@<code>{void onpush(String message) }関数内でNefryクラウドから届いたらメッセージの処理を行う流れになります。

== TwitterからNefryに通知を送る-IFTTTの設定-

NefryとNefryクラウドの準備が終わったところで、IFTTTの設定を進めていきます。

図の赤丸部分を参考にサクサク進めていきましょう。

//image[36NefryCloud_09][Sing Upでアカウントを作成しましょう][scale=0.8]{
//}

まず、IFTTTのアカウントをつくります。
「Sing up」をクリックして設定を進めていきます。

//image[36NefryCloud_10][New　Appletを探して、レシピを作ります][scale=0.8]{
//}

アカウント作成が終わったらログインしてトップ画面から、「New Applet」をクリックし最初に述べたレシピをつくっていきます。

//image[36NefryCloud_11][Thisを押します][scale=0.8]{
//}

「もし○○されたら△△する」というイメージでレシピの作成を進めます。
次に「+this」をクリックします。

//image[36NefryCloud_12][Twitterを探します][scale=0.8]{
//}

「Choose a service」と表示された画面にうつります。今回は「Twitterで自分がツイートしたら、Nefryに通知を送る」といったものをつくります。そのため、「Twitter」をクリックします。※もし、この画面で表示されていないときは「Search services」で検索しましょう。

//image[36NefryCloud_13][「New tweet by you」を選択します][scale=0.8]{
//}

そうすると「Choose trigger」の設定にうつります。「Twitterで自分がツイートしたら～」なので、「New tweet by you」を選択します。

他にも、さまざまなトリガーがありますのでそれを選んでも大丈夫です。

//image[36NefryCloud_14][設定ページ][scale=0.8]{
//}

このような画面にうつりますが今回は特に設定をしないので、「Create trigger」を選択します。

これで「Twitterで自分がツイートしたら△△する」の手前の部分ができました！

//image[36NefryCloud_15][thisを押します][scale=0.8]{
//}

「～したら、Nefryに通知を送る」という部分をつくっていきます。そのために、「+that」をクリックします。



//image[36NefryCloud_16][Webhocksを検索][scale=0.8]{
//}

今回は「Webhocks」を使うのでクリックします。

====[column] Webhocksとは

Webhocksでは次のようなことができます。

 * アプリケーションの更新情報を他のアプリケーションへ提供する仕組み
 * イベント発生時、指定したURLにHTTPリクエストする仕組み

====[/column]

//image[36NefryCloud_17][「Make a web request」をクリック][scale=0.8]{
//}

「Make a web request」をクリックします。

//image[36NefryCloud_18][必要な設定をしよう][scale=0.8]{
//}

「Complete action fields」と表示され、ここで詳細な設定を進めていきます。

次のように入力を進めていきます。この入力をすることで、Nefryクラウドにメッセージを送ることができるようになります。

基本は画像と同じようにMethodをPOSTに選択し進めてください。

//emlist{
※MethodがPOSTの場合
  URL：http://cloud.nefry.studio:1880/nefrysetting/setdata
  Method：POST
  Content Type：application/json
  Body：{"user":"Nefry","key":"123456abcdefg","data":"Nefry"}

  ※Body：{
            "user":"Nefryクラウド登録時のusername",
            "key":"メールで届いたApikey",
            "data":"任意で変更可、Nefryに通知する文章を設定可"
          }


※MethodがGETの場合
  URL：http://cloud.nefry.studio:1880/nefrysetting/setdata?user=nefry&
  Wkey=APIKey&data=testdata

//}

上記が記入できたら「Create action」を押します。

//image[36NefryCloud_19][「Finish」を押しましょう][scale=0.8]{
//}

そして、「Finish」を押して完成です！

== 実際に試してみる


「Nefry」とツイートして、シリアルモニタで「Hello」と表示された成功です！

※シリアルモニタでの表示はネットワーク等の調子により少し時間がかかる可能性もあります。

//image[36NefryCloud_20][ツイートするとメッセージが届きます！][scale=0.8]{
//}

無事にメッセージが届けばこの章は終了です。

他のサービスをIFTTTで連携させてみたり、トリガーに何かを動かしてみたりするよよいでしょう！
