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

let viewStyle =
  Style.[
    alignItems(`Center),
    flexDirection(`Row),
    justifyContent(`Center),
  ];

let buttonTextStyle =
  Style.[
    color(Theme.default.textLight),
    fontSize(Theme.default.fontSize),
    fontFamily(Theme.default.fontFamily),
  ];

let buttonViewStyle =
  Style.[
    padding(4),
    marginLeft(10),
    alignItems(`Center),
    justifyContent(`Center),
    color(Theme.default.textLight),
    height(Theme.default.inputHeight),
    width(Theme.default.inputWidth / 2),
    backgroundColor(Theme.default.orange),
  ];

let component = React.component("SelectEmployee");

let make = (~onSetId, ()) => {
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

    let foundId =
      switch (employee) {
      | None => "0"
      | Some(e) => e.id
      };

    let foundName =
      switch (employee) {
      | None => "No match"
      | Some(e) => e.employeeName
      };

    (
      hooks,
      <View style=viewStyle>
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
        <Clickable onClick={() => onSetId(foundId)}>
          <View style=buttonViewStyle>
            <Text text="Get" style=buttonTextStyle />
          </View>
        </Clickable>
      </View>,
    );
  });
};

let createElement = (~children as _, ~onSetId, ()) => make(~onSetId, ());