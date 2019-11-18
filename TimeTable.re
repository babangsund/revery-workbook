open Revery;
open Revery.UI;
open Revery.UI.Components;

open Types;

let rec take = (n, l) =>
  if (n == 0) {
    [];
  } else {
    switch (l) {
    | [h, ...t] => [h, ...take(n - 1, t)]
    | _ => []
    };
  };

let today = CalendarLib.Date.today() |> CalendarLib.Printer.Date.to_string;

let component = React.component("TimeTable");

let make = (~id, ()) =>
  component(hooks => {
    let (rows, setRows, hooks) = React.Hooks.state(React.empty, hooks);

    let fetchAll = () => {
      let entries =
        Workbook.fetchEntries(id, today) |> Lwt_main.run |> Decode.toEntries;

      Workbook.fetchRows(id, today)
      |> Lwt_main.run
      |> Decode.toRows
      |> List.map(r =>
           <View>
             {entries
              |> List.filter((e: entry) => e.taskId == r.taskId)
              |> take(5)
              |> List.map(entry =>
                   <Input
                     cursorColor=Colors.white
                     placeholderColor=Colors.white
                   />
                 )
              |> React.listToElement}
           </View>
         )
      |> React.listToElement
      |> setRows
      |> Option.none;
    };

    let hooks = React.Hooks.effect(OnMount, fetchAll, hooks);
    let hooks = React.Hooks.effect(If((!=), id), fetchAll, hooks);

    (hooks, <View> rows </View>);
  });

let createElement = (~children as _, ~id, ()) => make(~id, ());