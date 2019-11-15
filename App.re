open Revery;
open Revery.UI;
open Revery.UI.Components;

let main = app => {
  let window = App.createWindow(app, "ReveryWorkbook");
  let root = <View style=Style.[] />;

  let _ = UI.start(window, root);
  ();
};

App.start(main);