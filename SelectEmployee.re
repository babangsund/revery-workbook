open Revery;
open Revery.UI;
open Revery.UI.Components;

open Types;

type state = {
  name: string,
  employee: option(employee),
  employees: list(employee),
};

type action =
  | Name(Input.changeEvent)
  | Employee(option(employee))
  | Employees(list(employee));

let reducer = (action, state) =>
  switch (action) {
  | Name(event) => {...state, name: event.value}
  | Employee(employee) => {...state, employee}
  | Employees(employees) => {...state, employees}
  };

module Search = {
  let string_contains = (s1, s2) => {
    let re = Str.regexp_string(s2);
    switch (Str.search_forward(re, s1, 0)) {
    | _ => true
    | exception Not_found => false
    };
  };

  let match_employeeName = (name, x) => {
    string_contains(
      String.lowercase_ascii(x.employeeName),
      String.lowercase_ascii(name),
    );
  };
};

let component = React.component("SelectEmployee");

let make = () => {
  component(hooks => {
    let ({name, employee, employees}, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={name: "", employee: None, employees: []},
        reducer,
        hooks,
      );

    let setName = n => Name(n) |> dispatch;
    let setEmployee = e => Employee(e) |> dispatch;
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

    let hooks =
      React.Hooks.effect(
        If((!=), name),
        () => {
          employees
          |> List.find_opt(Search.match_employeeName(name))
          |> setEmployee
          |> Option.none
        },
        hooks,
      );

    let foundName =
      switch (employee) {
      | None => "No match"
      | Some(e) => e.employeeName
      };

    (
      hooks,
      <View>
        <Input value=name onChange=setName placeholder="Search" />
        <Text
          text=foundName
          style=Style.[
            color(Theme.default.textDark),
            width(Theme.default.inputWidth),
            fontSize(Theme.default.fontSize),
            fontFamily(Theme.default.fontFamily),
          ]
        />
      </View>,
    );
  });
};

let createElement = (~children as _, ()) => make();