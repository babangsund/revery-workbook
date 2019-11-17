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

let component = React.component("Root");

let make = () =>
  component(hooks => {
    let ({id, entries}, reducer, hooks) =
      React.Hooks.reducer(
        ~initialState={id: "?", entries: []},
        reducer,
        hooks,
      );

    (
      hooks,
      <View>
        <SelectEmployee onSetId={id => ()} onRegister={() => ()} />
        <TimeTable />
      </View>,
    );
  });

let createElement = (~children as _, ()) => make();