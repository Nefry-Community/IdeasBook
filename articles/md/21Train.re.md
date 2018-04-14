# Nefry BTでﾀﾞｧ ｼｴﾘｲｪｽなIoT

こんにちは、ポキオです。この章ではNefry BTを使った電車遅延通知ガジェットを作ってみようと思います。


## ﾀﾞｧ？


ﾀﾞｧ ｼｴﾘｲｪｽとは雑に言うと京浜急行のことです。私は京急が大好き。3度の飯より京急。京急は神。


![2018年3月で引退した往年の名車2000形](top_2000seriese)


## 遅延情報にエンターテイメントを

京急が大好き過ぎて、京急関連のIoTガジェットを幾つか作ってきました。そして殆どが遅延情報を伝えるガジェットです。


![以前作成したESP8266を使ったﾀﾞｧ2号](dala_2go)


通勤・通学に電車を使っている方にとって電車遅延は大敵で、天気予報と同じくらい気になる情報の一つです。もちろん、スマホアプリなどで能動的・受動的に情報を得ることは難しいことではありませんが、敢えてアナログな方法で、ちょっとおもしろく運行情報を伝えるガジェットに魅力を感じています。

実用的なんだけど少し可愛い、遅延を検知すると光るガジェットを作ってみましょう！


## 用意するもの
 - 電車のおもちゃ（ダイソーで売ってるプチ電車シリーズ）
 - Nefry BT
 - USB延長ケーブル
 - トレーシングペーパー
 - 両面テープ


![プチ電車シリーズにピッタリ収まるNefry BT](nefry_in_train)


電車のおもちゃは、電車じゃなくてもなんでもいいです。ただ、ダイソーの電車のよさみとして、

 - 安い
 - Nefry BTがぴったり入る
 - 窓が開いている（肉抜きされてる）ので、電車の中でLEDを光らせるとキレイに光る

こんなProsがあります。（Consは、京急がラインナップにないことです）


## 組み立てます


用意するものに「クッキングペーパー」が何故か含まれていますが、これはちゃんと意味があります。


![クッキングペーパーを貼ると光が拡散する](cooking_paper)


クッキングペーパーである必要はありませんが、このような素材を電車の窓の部分に内側から貼ることで、Nefty BTのLEDの光を綺麗に拡散してくれます。


また、Nefry BTはさきほどの写真の通り、電車のおもちゃの中に格納します。Nefry BTの裏側に両面テープを取り付けて、電車の天井に貼り付けるイメージです。Nefry BTを電車のおもちゃの中に取り付けてしまうと、PCとのUSB接続が難しくなってしまうため、Nefry BTのUSB端子を電車のおもちゃの連結部分から飛び出すように取り付けて、その先にUSB延長ケーブルを接続すると、PCとの接続が簡単になります。

Nefry BTのディスプレイがついていると、LEDの光が遮られてしまうため、予め外しておきます。


## プログラムを書き込みます


まず運行情報ですが、鉄道遅延情報のjson（https://rti-giken.jp/fhc/api/train_tetsudo/）から取得します。遅延している路線の一覧をJSON形式で取得できるので、Nefry BTでは`HTTPClient`を使って、そのJSONを取得します。


あとは取得したJSONに、監視したい路線名が含まれているかを`String#indexOf()`で確認して、それに応じてLEDを光らせるというものです。


```
#include <Nefry.h>
#include <HTTPClient.h> // HTTP-GETのために必要

void setup() {

}

void loop() {
  String trainDelayJson = getTrainDelayJson();

  if (trainDelayJson.indexOf("京急") > 0) {
    blinkFor30Sec(255, 0, 0); // 赤く光らせる
  } else {
    blinkFor30Sec(0, 0, 255); // 青く光らせる
  }
}

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
```


## 使い方はあなた次第


先程のコードは京急線の遅延検知をしていますが、`if (trainDelayJson.indexOf("京急") > 0)`の部分を書き換えれば、様々な路線に対応できます。また、今回はNefry BTに実装されているLEDだけを使っていますが、GPIOやGrove端子で接続された別のLEDを光らせることも可能です。
