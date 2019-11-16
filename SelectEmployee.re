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

    (
      hooks,
      <View>
        <Input
          value=name
          placeholder="Search"
          onChange={e => dispatch(Name(e))}
        />
      </View>,
    );
  });

let createElement = (~children as _, ()) => make();