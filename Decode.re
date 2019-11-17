open Yojson;
open Yojson.Basic;
open Yojson.Basic.Util;

open Types;

let toBool = (key, json) => json |> member(key) |> to_bool;
let toString = (key, json) => json |> member(key) |> to_string;
let toList = (fn, json) => json |> from_string |> to_list |> List.map(fn);

let toEntry = (json): entry => {
  hours: "",
  billable: false,
  description: "",
  id: json |> toString("Id"),
  jobId: json |> toString("JobId"),
  taskId: json |> toString("TaskId"),
  activityId: json |> toString("ActivityId"),
  registrationDate: json |> toString("RegistrationDate"),
};
let toEmployees = json => json |> toList(toEntry);

let toEmployee = (json): employee => {
  id: json |> toString("Id"),
  employeeName: json |> toString("EmployeeName"),
};
let toEmployees = json => json |> toList(toEmployee);