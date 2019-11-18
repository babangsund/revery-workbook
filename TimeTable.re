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

let viewStyle =
  Style.[
    flexDirection(`Column),
    borderTop(~color=Theme.default.borderColor, ~width=1),
    borderLeft(~color=Theme.default.borderColor, ~width=1),
  ];

let inputStyle =
  Style.[
    width(150),
    height(20),
    color(Theme.default.textLight),
    marginLeft(- Input.inputTextMargin),
    fontSize(Theme.default.fontSize - 2),
    border(~width=0, ~color=Colors.white),
  ];

let tr = (~children, ()) =>
  <View
    style=Style.[
      flexWrap(`NoWrap),
      alignItems(`Center),
      flexDirection(`Row),
    ]>
    {React.listToElement(children)}
  </View>;

let td = (~children, ~width as w=150, ()) =>
  <View
    style=Style.[
      width(w),
      overflow(`Hidden),
      paddingVertical(4),
      paddingHorizontal(12),
      borderRight(~color=Theme.default.borderColor, ~width=1),
      borderBottom(~color=Theme.default.borderColor, ~width=1),
    ]>
    {React.listToElement(children)}
  </View>;

let text = (~children as _, ~text="", ~color as c=Theme.default.textLight, ()) =>
  <Text
    text
    style=Style.[
      color(c),
      textOverflow(`Ellipsis),
      textWrap(TextWrapping.NoWrap),
      fontFamily(Theme.default.fontFamily),
      fontSize(Theme.default.fontSize - 2),
    ]
  />;

let head = {
  let orange = Theme.default.orange;
  <tr>
    <td width=300> <text text="Job" color=orange /> </td>
    <td width=300> <text text="Task" color=orange /> </td>
    <td> <text text="Mon" color=orange /> </td>
    <td> <text text="Tue" color=orange /> </td>
    <td> <text text="Wed" color=orange /> </td>
    <td> <text text="Thu" color=orange /> </td>
    <td> <text text="Fri" color=orange /> </td>
  </tr>;
};

let component = React.component("TimeTable");

let make = (~id, ~onSetEntry, ()) =>
  component(hooks => {
    let (rows, setRows, hooks) = React.Hooks.state(React.empty, hooks);

    let makeRows = () => {
      let today = CalendarLib.Date.today() |> CalendarLib.Printer.Date.to_string;

      let entries =
        Workbook.fetchEntries(id, today) |> Lwt_main.run |> Decode.toEntries;

      Workbook.fetchRows(id, today)
      |> Lwt_main.run
      |> Decode.toRows
      |> List.map(r =>
           <tr>
             <td width=300> <text text={r.jobName} /> </td>
             <td width=300> <text text={r.taskDescription} /> </td>
             {entries
              |> List.filter((e: entry) => e.taskId == r.taskId)
              |> take(5)
              |> List.map(entry =>
                   <td>
                     <Input
                       style=inputStyle
                       cursorColor={Theme.default.textLight}
                       placeholderColor={Theme.default.textLight}
                       onChange={e => onSetEntry({...entry, hours: e.value})}
                     />
                   </td>
                 )
              |> React.listToElement}
           </tr>
         )
      |> React.listToElement
      |> setRows
      |> Option.none;
    };

    let hooks = React.Hooks.effect(OnMount, makeRows, hooks);
    let hooks = React.Hooks.effect(If((!=), id), makeRows, hooks);

    (hooks, <View style=viewStyle> head rows </View>);
  });

let createElement = (~children as _, ~id, ~onSetEntry, ()) =>
  make(~id, ~onSetEntry, ());