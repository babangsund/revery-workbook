open Revery;
open Revery.UI;
open Revery.UI.Components;

open Types;

type state = {
  id: string,
  entries: list(entry),
};

type action =
  | Id(string)
  | Entry(entry);

let reducer = (action, {id, entries}) =>
  switch (action) {
  | Id(id) => {id, entries: []}
  | Entry(e) => {
      id,
      entries:
        switch (List.find((oe: entry) => oe.id == e.id, entries)) {
        | exception Not_found => entries @ [e]
        | _ => List.map((oe: entry) => oe.id == e.id ? e : oe, entries)
        },
    }
  };

let viewStyle =
  Style.[
    top(0),
    left(0),
    right(0),
    bottom(0),
    padding(0),
    position(`Absolute),
    alignItems(`FlexStart),
    justifyContent(`Center),
    backgroundColor(Theme.default.backgroundColor),
  ];

let component = React.component("Root");

let make = () =>
  component(hooks => {
    let ({id, entries}, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={id: "0", entries: []},
        reducer,
        hooks,
      );

    let setId = n => Id(n) |> dispatch;
    let setEntry = e => Entry(e) |> dispatch;
    let handleRegister = () =>
      entries
      |> Lwt_list.map_s(Workbook.postEntry)
      |> Lwt_main.run
      |> List.map(Yojson.Basic.from_string)
      |> List.map(Yojson.Basic.to_string)
      |> List.iter(print_endline);

    (
      hooks,
      <View style=viewStyle>
        <SelectEmployee onSetId=setId onRegister=handleRegister />
        <TimeTable id onSetEntry=setEntry />
      </View>,
    );
  });

let createElement = (~children as _, ()) => make();