

Nefry クラウド × IFTTT 連携！


= NefryとWEBサービスをつなげる


NefryはIoTに特化したお手軽なマイコン，というのはみなさんも重々承知だと思います．
なので，WEBサービスとつなげることも方法によっては簡単にできてしまいます．



例えば，IFTTT(イフト：IF This Then That)というサービスの利用です．
これを使うことで，IFTTTで提供されているレシピと呼ばれる既存のサービスを使えば，プログラミング不要で@<strong>{WEBサービス}と@<strong>{WEBサービス}を簡単につなげることができます．様々な条件を自分で設定することもできます．
NefryとIFTTを使った例はDotstudioのHPにもありますので是非参考にしてください．


= そして，ここからが本題...


Nefryには大きな問題があります．
それはネットからNefryにメッセージを送るのが難しいという点です．



AzureIoTHubやMilkcocoa(Nefry BT未対応)といったものがありますが、Nefry BTでは特にMilkcocoaに対応していないため特に難易度が高いです。



しかし，@<strong>{Nefryクラウド}を使えば@<strong>{簡単}です！
ただし，セキュリティが強固ではないので秘匿性の高いデータは扱わないでください。


= Nefryクラウドをつかってみよう！

=== Nefryクラウドにアクセス


まず，下記のURLを入力してNefryクラウドにアクセスしてみましょう．
http://cloud.nefry.studio:1880/nefrysetting/
アクセスできると，このような画面が現れます．



//image[36NefryCloud_01][image.png (699.7 kB)]{
//}



=== 登録してみよう


任意のUsernameと確実に届くメールアドレスを入力して，Sendを押します．



//image[36NefryCloud_02][image.png (714.2 kB)]{
//}




問題がなければ，下記のような画面が現れます．
//image[36NefryCloud_03][image.png (738.9 kB)]{
//}




すると，入力したメールアドレスに@<strong>{APIKey}が届きます.
これは，Nefryに書き込むプログラムに使うので覚えておきましょう．
※メールが届かない場合は，入力したメールアドレスが間違っているか，もしくは迷惑メールのフォルダに入っているのかもしれません．



//image[36NefryCloud_04][image.png (133.4 kB)]{
//}



= 実際につかってみよう


Nefryクラウドの一例として，@<strong>{TwitterからNefryに通知を送る}プログラムを作ってみましょう．



//image[36NefryCloud_05][image.png (141.9 kB)]{
//}



== Nefryクラウドのライブラリをインストール


最初に，Nefryクラウドを使うためにライブラリをインストールしてください．下記のURLからライブラリをダウンロードできます．
https://drive.google.com/file/d/15wHNn3ceyG7f0QEh2PPrnWGt0kIyStfW/view
ダウンロードしたzipファイルからArduino IDEのライブラリに追加していきます．



Arduino IDE上で「スケッチ」→「ライブラリをインクルード」→「ZIP形式のライブラリをインストール」と順にクリックしていきます．
//image[36NefryCloud_06][image.png (267.2 kB)]{
//}




そして別ウィンドウが表示されるので，そこでダウンロードしたzipファイルをクリックします．



//image[36NefryCloud_07][image.png (288.4 kB)]{
//}




すると，Nefryクラウドのライブラリが追加されます．
//image[36NefryCloud_08][image.png (323.7 kB)]{
//}



== TwitterからNefryに通知を送る-Nefryのプログラム-

//emlist[][c++]{

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

== TwitterからNefryに通知を送る-IFTTTの設定-


IFTTTの設定を進めていきます．
赤丸部分を参考にサクサク進めていきましょう．
まず，IFTTTのアカウントをつくります．
「Sing up」をクリックして設定を進めていきます．
//image[36NefryCloud_09][image.png (362.4 kB)]{
//}




設定が終わったらトップ画面から，「New Applet」をクリックし最初に述べたレシピをつくっていきます．
//image[36NefryCloud_10][image.png (196.5 kB)]{
//}




「もし○○されたら△△する」というイメージでレシピの作成を進めます．
次に「+this」をクリックします．
//image[36NefryCloud_11][image.png (165.1 kB)]{
//}




「Choose a service」と表示された画面にうつります．今回は「Twitterで自分がツイートしたら，Nefryに通知を送る」といったものをつくります．そのため，「Twitter」をクリックします．※もし，この画面で表示されていないときは「Search services」で検索しましょう．
//image[36NefryCloud_12][image.png (207.0 kB)]{
//}




そうすると「Choose trigger」の設定にうつります．「Twitterで自分がツイートしたら～」なので，「New tweet by you」を選択します．他にも，様々なトリガーを選択できます．
//image[36NefryCloud_13][image.png (197.0 kB)]{
//}




次に，下記のような画面にうつりますが今回は特に設定をしないので，「Create trigger」を選択します．
//image[36NefryCloud_14][image.png (140.8 kB)]{
//}




「～したら，Nefryに通知を送る」という部分をつくっていきます．そのために，「+that」をクリックします．
//image[36NefryCloud_15][image.png (130.7 kB)]{
//}




今回は「Webhocks」を使います．
Webhocksとは，

 * アプリケーションの更新情報を他のアプリケーションへリアルタイム提供する仕組みや概念
 * イベント発生時、指定したURLにPOSTリクエストする仕組み



のことです．
//image[36NefryCloud_16][image.png (116.4 kB)]{
//}




そして，「Make a web request」をクリックします．
//image[36NefryCloud_17][image.png (130.5 kB)]{
//}




「Complete action fields」と表示され，ここで詳細な設定を進めていきます．下記のように入力を進めていきます．


//hr


URL：http://cloud.nefry.studio:1880/nefrysetting/setdata
Method：POST
Content Type：application/json
Body：{"user":"Nefry","key":"123456abcdefg","data":"Nefry"}



※Body：{"user":"Nefryクラウド登録時のusername","key":"メールで届いたApikey","data":"任意で変更可，Nefryに通知する文章を設定可"}
※MethodがGETの場合 
URL：http://cloud.nefry.studio:1880/nefrysetting/setdata?user=nefry&key=2056f57db84f6c6a2e276119e&data=testdata


//hr


上記が記入出来たら「Create action」を押します．
//image[36NefryCloud_18][image.png (248.2 kB)]{
//}




そして，「Finish」を押して完成です！
//image[36NefryCloud_19][image.png (111.8 kB)]{
//}



= 実際に試してみる


「Nefry」とツイートして，シリアルモニタで「Hello」と表示された成功です！
※シリアルモニタでの表示は少し時間がかかる可能性もありますが，待ちましょう．
//image[36NefryCloud_20][image.png (71.5 kB)]{
//}


