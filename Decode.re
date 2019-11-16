open Yojson;
open Yojson.Basic;
open Yojson.Basic.Util;

open Types;

let toString = (key, json) => json |> member(key) |> to_string;
let toList = (fn, json) => json |> from_string |> to_list |> List.map(fn);

let toEmployee = (json): employee => {
  id: json |> toString("Id"),
  employeeName: json |> toString("EmployeeName"),
};
let toEmployees = json => json |> toList(toEmployee);