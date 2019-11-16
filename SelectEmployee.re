open Revery;
open Revery.UI;
open Revery.UI.Components;

open Types;

type state = {
  name: string,
  employees: list(employee),
};

type action =
  | Name(Input.changeEvent)
  | Employees(list(employee));

let reducer = (action, state) =>
  switch (action) {
  | Name(event) => {...state, name: event.value}
  | Employees(employees) => {...state, employees}
  };

let component = React.component("SelectEmployee");
let make = () =>
  component(hooks => {
    let ({name, employees}, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={name: "", employees: []},
        reducer,
        hooks,
      );

    let setName = n => Name(n) |> dispatch;
    let setEmployees = e => Employees(e) |> dispatch;

    let hooks =
      React.Hooks.effect(
        OnMount,
        () => {
          Workbook.fetchEmployees
          |> Lwt_main.run
          |> Decode.toEmployees
          |> setEmployees
          |> Option.none
        },
        hooks,
      );

    (
      hooks,
      <View>
        <Input value=name onChange=setName placeholder="Search" />
      </View>,
    );
  });

let createElement = (~children as _, ()) => make();