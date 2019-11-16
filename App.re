open Revery;
open Revery.UI;
open Revery.UI.Components;

open Fetch;
open Workbook;
open Decode;

let main = app => {
  let window = App.createWindow(app, "ReveryWorkbook");
  let root = <SelectEmployee onSetId={id => ()} />;

  let _ = UI.start(window, root);
  ();
};

App.start(main);