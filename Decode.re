open Yojson;
open Yojson.Basic;
open Yojson.Basic.Util;

open Types;

let toInt = (key, json) => json |> member(key) |> to_int;
let toString = (key, json) => json |> member(key) |> to_string;
let toList = (fn, json) => json |> from_string |> to_list |> List.map(fn);

let toEntry = (json): entry => {
  hours: "",
  billable: "false",
  description: "Description",
  id: json |> toInt("Id") |> string_of_int,
  jobId: json |> toInt("JobId") |> string_of_int,
  taskId: json |> toInt("TaskId") |> string_of_int,
  activityId: json |> toInt("ActivityId") |> string_of_int,
  registrationDate: json |> toString("RegistrationDate"),
};
let toEntries = json => json |> toList(toEntry);

let toRow = (json): row => {
  children: [],
  jobId: json |> toInt("JobId") |> string_of_int,
  taskId: json |> toInt("TaskId") |> string_of_int,
  jobName: json |> toString("JobName"),
  activityId: json |> toInt("ActivityId") |> string_of_int,
  taskDescription: json |> toString("TaskDescription"),
};
let toRows = json => json |> toList(toRow);

let toEmployee = (json): employee => {
  id: json |> toInt("Id") |> string_of_int,
  employeeName: json |> toString("EmployeeName"),
};
let toEmployees = json => json |> toList(toEmployee);