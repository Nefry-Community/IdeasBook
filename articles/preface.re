= はじめに

この度は、Nefryの事例本を手に取っていただきありがとうございます！

この本では、Nefryでどんなことができるのかお伝えします。

本を読んで新しいことにチャレンジしましょう！

== 対象読者

 *  本書と同時販売の「きょうからのNefry」を終えた方
 * Nefryで次に何をしようか悩んでいる方

 上記のような方やハードウェア初心者を対象に説明していきます。

 なるべくわかりやすく書くようにしていますが、変数や関数などコードの詳しい説明はしないのであらかじめご了承ください。

 環境構築等については、「きょうからのNefry」にて説明されているのでそちらをご確認ください。

== 動作確認環境について

筆者で動作確認した環境は次のリストになります。（2018/4/1現在）

 * Windows 10 Home & macOS Sierra 10.12.6（MacBook Air（13-inch, Mid 2013））
 * Arduino IDE 1.8.5
 * NefryLibrary 1.2.1

== わからないときは

Nefryユーザのコミュニティサイトです。
本書でわからないことがあれば、こちらに投稿していただくと反応があると思います。

 * Facebookコミュニティ（@<href>{https://www.facebook.com/groups/nefry}）

===[column] Nefry BTのリビジョンによる違いについて

Nefry BTには3つのリビジョンが存在します。（2018年4月現在）

 * Nefry BT（無印/R1）
 * Nefry BT R2
 * Nefry BT R3

Nefry BT（無印/R1）以降の変更点を説明します。

@<strong>{■ Nefry BT R2}

 * USBの両端についたスイッチを押しやすくなるようにスペースを取りました。
 * アンテナ部分を保護するために基板長を伸ばしました。
 * USB電源を保護するためにICを追加しました。
 * ピンの配置を修正しました。
 ** ディスプレイの制御ピンを変更しました。
 ** 基板の印字でアナログ入力ができないピンがあった件に対応しました。

@<strong>{■ Nefry BT R3}

 * Groveのアナログ入力を追加しました。
 * 書き込み時のエラーが起こりにくいように修正しました。
 * GroveのA0ポートの配線が間違っていた件を修正しました。

===[/column]
