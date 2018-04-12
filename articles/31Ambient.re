
= センサデータを「Ambient」に送り、グラフ化する


NefryにセンサとLCDをつけるとセンサデータを確認できます。しかし遠くにあるセンサのデータを確認したり、何ヶ月もの期間のデータを蓄積して比較したりするには、データをクラウドに送った方が便利です。IoTデータを扱うクラウドサービスはいくつかあります。この章では、IoTデータ可視化サービス「@<href>{https://ambidata.io,Ambient}」でNefryのデータを扱う例を紹介します。


== Ambientの概要


Ambientは簡単に使えるIoTデータ可視化サービスです。マイコンからセンサデータをAmbientに送ると、Ambientはそれを受信して、蓄積し、グラフ化します。


//emlist{
XXX: BLOCK_HTML: YOU SHOULD REWRITE IT
<!-- ![概要図]() -->
//}

== Ambientを使う準備

=== ユーザー登録


Ambientを使うには、まず最初にユーザー登録します。Ambientの基本部分は無料で使えます。@<href>{https://ambidata.io/usr/signup.html,Ambientのユーザー登録ページ}でメールアドレスとパスワードを入力すると、入力したメールアドレスに確認メールが送られます。メール中のURLをクリックするとユーザー登録は完了です。しばらく待ってもメールが送られない場合は、迷惑メールフォルダを確認してください。そこにもなければ、お手数ですが、もう一度ユーザー登録をお願いします。


//emlist{
XXX: BLOCK_HTML: YOU SHOULD REWRITE IT
<!-- ![登録画面]() -->
//}

=== チャネル生成


ユーザー登録してログインすると、チャネル一覧ページが現れます。 Ambientではマイコンから送信するデータを「チャネル」という単位で管理します。 データを送る際は「チャネル」を指定して送ります。 最初はチャネルがないので、「チャネルを作る」ボタンがあるだけです。「チャネルを作る」ボタンを押すとチャネルが生成され、 作られたチャネルの情報が表示されます。


//emlist{
XXX: BLOCK_HTML: YOU SHOULD REWRITE IT
<!-- ![チャネル画面]() -->
//}

== Nefryのプログラム


データをAmbientに送信するには、まずチャネルIDとライトキーを指定してAmbientの初期化をおこないます。



次にセンサから読んだデータをパケットにセットします。データがint型、float型であれば直接ambient.set()でセットできます。データの桁数などを制御したければご自分で文字列形式に変換し、パケットにセットします。データをパケットにセットしたら、ambient.send()で送信します。 データは8種類まで送ることが出来ます。



プログラムは次のようになります。



プログラム



channelIdとwriteKeyにAmbientで先程作ったチャネルのIDとライトキーを設定します。プログラムをビルドしてNefryに書き込むと、温度、湿度が測定され、Ambientに送信され、グラフ化されます。Ambientのチャネルページを見ると、次のようにデータを確認できます。


//emlist{
XXX: BLOCK_HTML: YOU SHOULD REWRITE IT
<!-- ![チャネルページ]() -->
//}
