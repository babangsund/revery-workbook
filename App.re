open Revery;
open Revery.UI;
open Revery.UI.Components;

let main = app => {
  let window =
    App.createWindow(
      app,
      "ReveryWorkbook",
      ~createOptions=WindowCreateOptions.create(~width=1353, ()),
    );

  let root = <Root />;

  let _ = UI.start(window, root);
  ();
};

App.start(main);