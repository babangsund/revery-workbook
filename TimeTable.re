open Revery;
open Revery.UI;
open Revery.UI.Components;

open Types;

let component = React.component("TimeTable");

let make = (~id, ()) =>
  component(hooks => {
    let today = CalendarLib.Date.today() |> CalendarLib.Printer.Date.to_string;

    let entries =
      Workbook.fetchEntries(id, today) |> Lwt_main.run |> Decode.toEntries;

    let rows = Workbook.fetchRows(id, today) |> Lwt_main.run |> Decode.toRows;

    (hooks, <View />);
  });

let createElement = (~children as _, ~id, ()) => make(~id, ());