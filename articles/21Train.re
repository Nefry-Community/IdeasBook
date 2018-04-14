= Nefry BTでﾀﾞｧ ｼｴﾘｲｪｽなIoT

こんにちは、ポキオです。
この章ではハンズオンも行った、Nefry BTを使った電車遅延通知ガジェットを作ってみようと思います。

== ﾀﾞｧ？

「ﾀﾞｧ ｼｴﾘｲｪｽ」とは京浜急行電鉄の「ドア、閉まります」という言葉を文字に起こしたものです。

私は京急が大好き。
3度の飯より京急。@<b>{京急は神。}

//image[top_2000seriese][2018年3月で引退した往年の名車2000形][scale=0.8]{
//}

== 遅延情報にエンターテイメントを

京急が大好き過ぎて、京急関連のIoTガジェットをいくつか作ってきました。
そしてほとんどが遅延情報を伝えるガジェットです。

//image[dala_2go][以前作成したESP8266を使ったﾀﾞｧ2号][scale=0.8]{
//}

（参考記事：@<href>{https://dotstud.io/blog/pokio-esp-keikyu-chien/}）

通勤・通学に電車を使っている方にとって電車遅延は大敵で、天気予報と同じくらい気になる情報の一つです。

もちろん、スマホアプリなどで能動的・受動的に情報を得ることは難しいことではありませんが、敢えてアナログな方法で、ちょっとおもしろく運行情報を伝えるガジェットに魅力を感じています。

実用的なんだけど少し可愛い、遅延を検知すると光るガジェットを作ってみましょう！

== 用意するもの

 * 電車のおもちゃ（ダイソーで売ってる「プチ電車」シリーズ）
 * Nefry BT
 * USB延長ケーブル
 * トレーシングペーパー
 * 両面テープ

===[column] ダイソーの「プチ電車」シリーズを使う理由

//image[nefry_in_train][プチ電車シリーズにピッタリ収まるNefry BT][scale=0.8]{
//}

外装は、電車じゃなくてもいいですが、ダイソーの「プチ電車」シリーズを使うと次のようなよさみがあります！

 * 安い
 * Nefry BTがぴったり入る
 * 窓が開いている（肉抜きされてる）ので、電車の中でLEDを光らせるとキレイに光る

悪い点は、京急がラインナップにないことです。

===[/column]


== プログラムを書き込みます

電車の遅延情報を取得するプログラムを作って、Nefry BTに書き込んでいこうと思います。

まず運行情報ですが、「鉄道遅延情報のjson（@<href>{https://rti-giken.jp/fhc/api/train_tetsudo/}）」というサイトからJSONを取得します。

遅延している路線の一覧をJSON形式で取得できるので、Nefry BTでは@<tt>{HTTPClient}を使って、そのJSONを取得します。

あとは取得したJSONに、監視したい路線名が含まれているかを@<tt>{String#indexOf()}で確認して、それに応じてLEDを光らせるというものです。

//emlist{
#include <Nefry.h>
#include <HTTPClient.h> // HTTP-GETのために必要

void setup() {

}

void loop() {
  String trainDelayJson = getTrainDelayJson();

  //ネットから取得してきた運行状況に指定の文字があるか探します
  if (trainDelayJson.indexOf("京急") > 0) {
    blinkFor30Sec(255, 0, 0); // 赤く光らせる
  } else {
    blinkFor30Sec(0, 0, 255); // 青く光らせる
  }
}

//運行状況をネットから取得し、取得した情報を返す関数
String getTrainDelayJson() {
  String payload = ""; // 運行情報を保存しておく
  HTTPClient http; // HTTP-GETをするために必要な宣言
  int httpCode; // HTTP-GETの結果（int）を保存しておく

  // 運行情報のページにアクセス
  http.begin("http://rti-giken.jp/fhc/api/train_tetsudo/delay.json");

  // その結果を保存
  httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    // 成功だったら、運行情報の文字列を取得して保存
    payload = http.getString();
    Nefry.println("接続成功");
    Nefry.println(payload);
  } else {
    // 失敗だったら、エラーコードをログに出力
    Nefry.println("接続失敗");
    Nefry.println(http.errorToString(httpCode));
  }

  return payload;
}

// 30秒間、500msecおきに点灯と消灯を繰り返します
void blinkFor30Sec(int r, int g, int b) {
  for (int i = 0; i < 30; i++) {
    Nefry.setLed(r, g, b);
    Nefry.ndelay(500);
    Nefry.setLed(0, 0, 0);
    Nefry.ndelay(500);
  }
}
//}

作成したプログラムをNefry BTに書き込みます。

書き込み方法については、同時期に発売予定の「きょうからのNefry」にて詳しく解説されています。

== 組み立てます

Nefry BTにプログラムを書き込みをした後は、電車にNefryを組み込んでいきましょう！

用意するものに「クッキングペーパー」がなぜか含まれていますが、これはちゃんと意味があります。

//image[cooking_paper][クッキングペーパーを貼ると光が拡散する][scale=0.8]{
//}

クッキングペーパーを電車の窓の部分にかかるように内側から貼ることで、Nefty BTのLEDの光をきれいに拡散してくるようになります。

これをするのとしないのとでは見た目が大きく変わってしまうのでクッキングペーパーを貼り付けましょう！

//image[step2][Nefryをテープで止めよう][scale=0.8]{
//}

クッキングペーパーを貼り付けた後は、Nefry BTの裏側に両面テープを取り付けて、Nefry BTを電車の天井に貼り付けましょう。

Nefry BTを電車に取り付けてしまうと、PCとのUSB接続が難しくなってしまうため、
Nefry BTのUSB端子を電車の連結部分から飛び出すように取り付けて、その先にUSB延長ケーブルを接続すると、Nefry BTとの接続が簡単になります。

あと、Nefry BTにディスプレイがついている場合、LEDの光が遮られてしまうため、外してしまいます。

これで組み立ては完了です！

あとはNefry BTを動かして、電車の遅延情報が取得できるのか確認しましょう！

== 使い方はあなた次第

この章のコードは京急線の遅延検知をしていますが、@<code>{if (trainDelayJson.indexOf("京急") > 0)}の部分を書き換えれば、他の路線に対応できます。

また、今回はNefry BTに実装されているLEDだけを使っていますが、GPIOやGrove端子で接続された別のLEDを光らせることも可能ですのでいろいろ試してみてください。
